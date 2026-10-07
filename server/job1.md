# Job 1 — Clean up & restructure the base (Oct 7, ~3.5h)

Goal: replace the blocking tutorial server in `coding/` with a clean, C++98-compliant base for `webserv`.
Steps 1–3 are the must-do; step 4 is a bonus (gets you ahead on Week 1).

## 1. New layout (≈20 min) — [ ]
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
- [ ] Remove tracked `.o` files and binaries (`hdelibc_test`, `Servers/test`).

## 2. Merge the 3 socket classes into one `ListenSocket` (≈60 min) — [ ]
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
- [ ] `setsockopt(SO_REUSEADDR)` so a restart doesn't fail with "Address already in use".
- [ ] `fcntl(fd, F_SETFL, O_NONBLOCK)`. Use only that flag, because the subject forbids the others.
- [ ] Call `listen()` once, not twice.
- [ ] Throw an exception instead of `exit()`, and close the fd before throwing.

## 3. Makefile (≈20 min) — [ ]
- [ ] `NAME = webserv`, rules `all clean fclean re`, flags `-Wall -Wextra -Werror -std=c++98`.
- [ ] Objects in `obj/` + `-MMD -MP`, so changing a header triggers a rebuild but nothing relinks without a reason.
- [ ] Check: running `make` twice prints "Nothing to be done" the second time.

## 4. First real `poll()` loop (≈70 min, bonus) — [ ]
In `ServerManager`, just enough to replace `TestServer`:
- [ ] `std::vector<pollfd>`; one `ListenSocket` each for ports 8080 and 8081 (hard-coded, marked `// STUB`).
- [ ] Loop on `poll()`. POLLIN on a listen fd → `accept()`, make the client fd non-blocking, add it with POLLIN.
- [ ] POLLIN on a client fd → `recv()` once and print it. Result `<= 0` → close the fd and remove it. Don't check `errno`.
- [ ] Send only after POLLOUT: when the request has arrived, switch that fd's events to POLLOUT, then `send` a fixed `HTTP/1.1 200 OK` response and close.

## 5. Check & commit (≈20 min) — [ ]
```bash
make re && ./webserv
curl -v localhost:8080 ; curl -v localhost:8081
for i in $(seq 100); do curl -s localhost:8080 & done; wait   # must not crash
```
- [ ] Commit.
- [ ] Tick the Week 0 Makefile/C++98 box in `PLAN.md` (plus the Oct 12–15 boxes if step 4 is done).

---
Write the code yourself (the subject's AI rules: you must be able to explain it at the defense). Afterwards, ask Claude to review it for poll-rule violations and C++98 problems.
