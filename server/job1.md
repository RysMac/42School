# Job 1 — Clean up & restructure the base (Oct 7, ~3.5h)

## ▶ Progress (saved Oct 10) — job1 DONE; continue in `job2.md`
Code lives in `coding/webserv/` (not `server/webserv/` as planned below; fine, just be consistent).

**Done**
- Layout: `Makefile`, `src/main.cpp`, `src/net/ListenSocket.*`, `src/core/ServerManager.*`, `conf/default.conf`, `.gitignore` (`webserv`, `obj/`).
- `ListenSocket` is finished: socket → SO_REUSEADDR → O_NONBLOCK → bind → listen (once), `fail()` closes the fd and then throws, and copying is disabled.
- `ServerManager` owns `std::vector<ListenSocket*> _sockets`:
  - The constructor calls `reserve(ports.size())` (so `push_back` can't throw), then `new`s + `push_back`s one socket per port, inside `try { } catch (...) { del_sockets(); throw; }` (**Trap 1 ✔**).
  - `del_sockets()` deletes each socket and then `clear()`s, so calling it twice is safe. The destructor calls it too.
  - The copy constructor and `operator=` are private and never defined (**Trap 2 ✔**).
  - `run()`/`run_sockets()` are removed.
- `main.cpp`: `ServerManager server(ports); pause();` both inside `try`, since the server must live in the same scope where it's used. `catch (const std::exception& e)` prints the error and returns 1.
- Tested: `ss -ltn` shows 8080/8081/8082. With 8081 held by another process: `Error: bind(8081)…`, 0 bytes in use, only the 3 std fds open (the 8080 socket was cleaned up).
- Makefile: `obj/` mirrors `src/`, `-MMD -MP` + `-include $(DEPS)`, `re: fclean` + `$(MAKE) all`. Verified: no relink; touching a header rebuilds only the `.cpp` files that include it.
- `git rm --cached coding/webserv/webserv` (staged).
- Exceptions lab (`server_practice/throw.cc`) is done. Concepts learned:
  - `throw` jumps; unwinding destroys fully built objects in reverse order.
  - When a constructor throws, its destructor does NOT run, but members that were already built ARE destroyed. A raw pointer member does nothing, so the object it points to leaks.
  - `new T` = allocate + construct; if the constructor throws, `new` frees the memory itself.
  - Once `new` succeeds, you own the object → `delete` it while the pointer is still in scope.
  - Swallowing the exception in a constructor makes a half-built object look valid (bad).
  - `catch (...) { cleanup; throw; }` for cleanup; `catch (const std::exception& e)` where the error is handled (`main`).
  - `throw;` rethrows the original object; `throw e;` slices it.
  - `delete NULL` / `free(NULL)` are no-ops; a double delete is UB.
  - Members by value (RAII) → no try/catch needed.
  - vector: `reserve` vs `resize`, `clear()` doesn't delete pointees, `const_iterator` is read-only.

**Done offline Oct 9 evening (uncommitted, reviewed Oct 10)**
- Commit of steps 1–3 + Makefile = `2e71a27`.
- Step 4, items 1–3: `_pfds` + `addPfd()` (listen fds first), `run()` loops on `poll(-1)`, POLLIN on listen → `accept` + O_NONBLOCK + add; POLLIN on client → `recv` once, print, `<= 0` → close + swap-with-last + `pop_back`. Builds with -Werror; tested with curl/nc (request printed; curl times out because nothing is sent yet).

**Done Oct 10**
- Step 4 complete: loop bugs fixed (error check first, client-only; removal always ends the branch), POLLOUT switch + fixed `200 OK` (ostringstream, Content-Length, `Connection: close`), close after send either way, `MSG_NOSIGNAL` on send.
- Step 5: `make re` clean, no relink; curl 200 on 8080/8081/8082; 100 parallel curls → still alive, 6 fds (3 std + 3 listen).
- Leftover binaries untracked; committed.

**Open TODOs (in the code)**
- `delClient()` helper: the close/swap/pop/--i block is repeated 4×.
- Partial send → per-client out-buffer (Oct 16–17).
- Replace `MSG_NOSIGNAL` by `signal(SIGPIPE, SIG_IGN)` in `main` before CGI pipes (Week 3).
- `throw` on `poll() < 0` kills the server; `~ServerManager` doesn't close client fds; `-1` timeout until the timeouts week; `memset` not needed.
- `makeTestConfig()` stub from PLAN Oct 10–11 not written yet.

Goal: replace the blocking tutorial server in `coding/` with a clean, C++98-compliant base for `webserv`.
Steps 1–3 are the must-do; step 4 is a bonus (gets you ahead on Week 1).

## 1. New layout (≈20 min) — [x]
Keep `coding/` as a read-only reference and start fresh next to it:
```
server/
  webserv/
    Makefile
    .gitignore          # *.o, webserv, obj/
    src/
      main.cpp
      net/ListenSocket.hpp/.cpp
      core/ServerManager.hpp/.cpp
    conf/default.conf   # empty for now
```
- [x] Remove tracked `.o` files and binaries.

## 2. Merge the 3 socket classes into one `ListenSocket` (≈60 min) — [x]
`SimpleSocket → BindingSocket → ListeningSocket` is three classes doing one job, and `ConnectingSocket` isn't needed. One class is enough:

```cpp
class ListenSocket {
public:
    ListenSocket(const std::string& host, int port);  // socket, setsockopt, fcntl, bind, listen
    ~ListenSocket();                                   // close(_fd)
    int  getFd() const;
    int  getPort() const;

    class SocketError : public std::runtime_error { /* ... */ };
private:
    ListenSocket(const ListenSocket&);            // fd owner: copying disabled (C++98 way)
    ListenSocket& operator=(const ListenSocket&);
    int _fd;
    int _port;
};
```
Fixes to make while you write it:
- [x] `setsockopt(SO_REUSEADDR)` so a restart doesn't fail with "Address already in use".
- [x] `fcntl(fd, F_SETFL, O_NONBLOCK)`. Use only that flag, because the subject forbids the others.
- [x] Call `listen()` once, not twice.
- [x] Throw an exception instead of `exit()`, and close the fd before throwing.

## 3. Makefile (≈20 min) — [x]
- [x] `NAME = webserv`, rules `all clean fclean re`, flags `-Wall -Wextra -Werror -std=c++98`.
- [x] Objects in `obj/` + `-MMD -MP`, so changing a header triggers a rebuild but nothing relinks without a reason.
- [x] Check: running `make` twice prints "Nothing to be done" the second time.

## 4. First real `poll()` loop (≈70 min, bonus) — [x]
In `ServerManager`, just enough to replace `TestServer`:
- [x] `std::vector<pollfd>`; one `ListenSocket` each for ports 8080 and 8081 (hard-coded, marked `// STUB`).
- [x] Loop on `poll()`. POLLIN on a listen fd → `accept()`, make the client fd non-blocking, add it with POLLIN.
- [x] POLLIN on a client fd → `recv()` once and print it. Result `<= 0` → close the fd and remove it. Don't check `errno`.
- [x] Send only after POLLOUT: when the request has arrived, switch that fd's events to POLLOUT, then `send` a fixed `HTTP/1.1 200 OK` response and close.

## 5. Check & commit (≈20 min) — [x]
```bash
make re && ./webserv
curl -v localhost:8080 ; curl -v localhost:8081
for i in $(seq 100); do curl -s localhost:8080 & done; wait   # must not crash
```
- [x] Commit.
- [x] Tick the Week 0 Makefile/C++98 box in `PLAN.md` (plus the Oct 12–15 boxes if step 4 is done).

---
Write the code yourself (the subject's AI rules: you must be able to explain it at the defense). Afterwards, ask Claude to review it for poll-rule violations and C++98 problems.
