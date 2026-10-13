# Job 2 — Client buffers & partial I/O (PLAN: Week 1, Oct 16–18, ~4h)

## ▶ Progress (Oct 13, end of session): steps 1–5 coded, reviewed and tested. Resume with the clean-up below, commit, then step 6.
- Done (Oct 13): all 6 open fixes from Oct 12. The setters are replaced by behaviour methods: `save_recv(const char*, size_t)` (appends; sets `_recv_done` when `_in` contains `\r\n\r\n`), `add_sent_bytes(n)`, and the `const` questions `data_to_send()`, `bytes_to_send()`, `get_recv_done()`, `get_send_done()` (computed as `_sent == _out.size()`, no flag). POLLIN sets POLLOUT only when the request is complete. POLLOUT sends from `_sent` and removes the client only when everything is sent.
- Exception safety: accept does `addClient` first, then `addPfd`. `addClient`'s contract: if it throws, it has already cleaned up (fd closed, no Client in the map), so the caller only logs and `continue`s. If `addPfd` throws, the caller removes the Client **by fd** (not `delClient(i)`: there `i` is the listen socket). `delClient` closes the fd itself if no Client is found. Invariant: every client fd in `_pfds` has exactly one Client in `_clients`, so POLLIN/POLLOUT use `find` without an `end()` check.
- Tests passed: curl 200 on 8080–8082; 100 parallel curls, 6 fds left; a request split into 3 pieces (even `\r` | `\n`) is answered only after the last byte; 5 MB body is sent in 2–3 partial sends with exact size, and a curl on 8081 answers in 0.05 s meanwhile; `bad_alloc` injected before `new`, after `new` and in `addPfd`: only that connection is dropped, same port still answers, no fd leak. (Logging to a file: use `stdbuf -oL ./webserv > log`.)
- **Clean-up (≈5 min, before the commit):** move/delete the "hardcoded in constructor" comment in POLLOUT; `// send failed: close -> replace` → "send failed"; constructor comment typo ("latet"); add the invariant comment next to `_clients` in `ServerManager.hpp`; trailing/mixed whitespace (Client.hpp:16,18, ServerManager.hpp:24, ServerManager.cpp:56,128,138,152,164). Optional: rename `delClient` (it removes by pfd index) and `get_recv_done`/`get_send_done` to question-style names.
- Still temporary: `_out` is built in the `Client` constructor. It should be built once the request is complete (by the request handler later, not by Client).
- Defense notes from today: why getters/setters are a problem (invariants live in every caller; "tell, don't ask"); `map::find` → `end()` is not an element; the `new`/`insert` leak window (a raw `new` is yours until it's stored); "only the owner closes the fd" (double close can kill a reused fd); `const char*` = pointer to const chars, right-side `const` = method doesn't change the object; `recv` never says "request complete", HTTP does (`\r\n\r\n`), and the poll loop is the read loop (one `recv` per POLLIN).
- **Next: step 6** (SIGPIPE via `signal`, `poll() < 0` decision, `makeTestConfig()` stub), then the Week 1 check and commit.
- Big picture (discussed): later `_out` comes from parse `_in` → route via config (server block, longest-prefix location) → handle (file / autoindex / upload / DELETE / redirect / CGI / error page) → serialize. That is not Client's job. Order after job2: request parser → static GET → config → POST/DELETE → CGI.
Code lives in `coding/webserv/`. Starting point: commit `493ba36` (job1 done). Open TODOs carried over from job1: `delClient()` helper, partial send, SIGPIPE via `signal()`, `makeTestConfig()` stub.

Goal: right now one `recv` = one request and one `send` = one response. Real clients don't work like that. A request can arrive in many small pieces, and a large response won't fit in one `send`. Give every client its own state (an in-buffer, an out-buffer and a send offset) so the loop can handle **any** split of the data, and still never block.
Steps 1–5 are the must-do; step 6 closes Week 1 (the Oct 18 row in PLAN.md).

## 0. Opening questions (≈10 min, no code)
Answer these in your own words before coding (write them here):
- `recv` returned 300 bytes. Is that the whole request? How can you tell when the **headers** have ended? (Look at your 200 OK response: the same rule applies to requests.)
- `send` was asked to write 100 000 bytes and returned 65 536. What happened to the rest, and what should you do on the next POLLOUT?
- What has to be remembered about a client **between two passes** of the poll loop? List it. That list is your `Client` class.

## 1. Warm-up: one removal helper (≈20 min) — [x]
The block "close → swap with last → `pop_back` → `--current_size` → `--i`" appears 4 times in `run()`.
- [ ] Make it one private function, e.g. `void removeClient(size_t i)`.
- Think about this first: the helper can close and remove, but `i` and `current_size` live in `run()`. Who adjusts them? Options: the helper returns something, or the caller does it, or you iterate **backwards** (from the end to `_sockets.size()`). With backwards iteration, does swap-with-last still need `--i`? Pick one and be able to defend it.
- [ ] Test: same results as job1 step 5 (curl 200 on the 3 ports, 100 curls, 6 fds).

## 2. The `Client` class (≈45 min) — [x]
New files: `src/net/Client.hpp/.cpp`. Its contents come from your answer to the third question in step 0. A minimal version:
```cpp
class Client {
public:
    explicit Client(int fd);
    ~Client();
    int  getFd() const;
    // reading side: append received bytes, ask "is the request complete?"
    // writing side: set the response, "what's left to send?", "advance by n"
private:
    int         _fd;
    std::string _in;     // bytes received so far
    std::string _out;    // full response to send
    size_t      _sent;   // how much of _out is already sent
    // later: state enum, last-activity time (timeouts, Week 3), parsed HttpRequest (Week 2)
};
```
- [ ] Decide **who closes the fd**: `~Client`, or `ServerManager`? Only one of them may. Write down why.
- [ ] **Trap 3 (copying):** if `~Client` closes the fd and a `Client` gets copied (e.g. stored **by value** in a container, which copies it), the copy's destructor closes the same fd → double close. A double close can even close a *new* client that got the same fd number. Same fix as Trap 2 in job1: disable copying and store pointers, **or** make sure `~Client` doesn't own the fd. Choose one.
- [ ] Add `Client.cpp` to the Makefile. Check that touching `Client.hpp` rebuilds only what includes it.

## 3. Where clients live (≈30 min) — [x]
You need to find "the `Client` for this fd" every time `poll()` reports an fd.
- [ ] Add `std::map<int, Client*> _clients` (key = fd) to `ServerManager`. Ask yourself: why a map and not a second vector kept parallel to `_pfds`? (Hint: swap-with-last.)
- [ ] accept → `new Client(fd)` + insert + `addPfd`. Remove → delete + `erase` + remove the pfd. Keep the three in sync **in one place** (the helper from step 1).
- [ ] Listen fd vs client fd: you can now ask "is this fd in `_clients`?" instead of relying on the index order. Do you still need the order trick? Keep whichever you can explain better.
- [ ] `~ServerManager` must delete every remaining `Client` (and close its fd). That closes another job1 TODO.
- [ ] **Trap 4 (exception safety again):** `new Client` succeeds but the `insert` throws (`bad_alloc`) → leak + an open fd. How likely is it? It's enough to know the answer and say it at the defense; a `try/catch` around the insert is the strict fix.

## 4. Reading: accumulate until the request is complete (≈45 min) — [x]
- [ ] On POLLIN: `recv` into the stack buffer, then **append** the bytes to the client's `_in`.
- [ ] **Trap 5 (binary data):** `_in += buffer` stops at the first `'\0'` and relies on your manual terminator. Use the version of `append` that takes a pointer **and a length**. Then you don't need the `memset` or the `'\0'` at all.
- [ ] "Complete" for now = `_in` contains the end of the headers (`\r\n\r\n`). Bodies (`Content-Length`, chunked) are Week 2; leave a `// TODO`.
- [ ] Complete → build the response into `_out` (move your 200 OK code here or into a small function), then set `events = POLLOUT`. Not complete → do nothing and wait for the next POLLIN.
- [ ] `recv <= 0` → remove (same as now).
- [ ] Test with a slow, hand-typed request. The reply must come **only** after the empty line:
```bash
nc -C localhost 8080        # -C sends \r\n; type each line and press Enter:
GET / HTTP/1.1
Host: x
                            # ← an empty line: the response should appear now
```
- [ ] Optional: what stops a client from sending headers forever and filling your memory? Write down a limit (e.g. 8 KB of headers → 431 later). Don't implement it yet.

## 5. Writing: partial `send` (≈45 min) — [x]
- [ ] On POLLOUT: send from `_out` **starting at `_sent`**, at most `size - _sent` bytes. Where does the pointer start?
- [ ] `n > 0` → `_sent += n`. Everything sent → remove the client (we still send `Connection: close`). Not everything → do nothing; poll will report POLLOUT again.
- [ ] `n <= 0` → remove. Still no `errno`.
- [ ] Remove the job1 `// TODO partial send` and the duplicated `if/else`.
- [ ] Test it for real: a 60-byte reply never splits, so temporarily make the body big (e.g. 1–5 MB of `'a'`, `std::string(5000000, 'a')`) and print `n` after every send:
```bash
curl -s localhost:8080 | wc -c      # must equal the header size + body size
curl -s --limit-rate 100k localhost:8080 -o /dev/null   # a slow reader → many partial sends
```
While the slow curl runs, a second `curl localhost:8081` must answer immediately (proof that nothing blocks).

## 6. Close Week 1 (≈30 min) — [ ]
- [ ] SIGPIPE: replace `MSG_NOSIGNAL` with `signal(SIGPIPE, SIG_IGN)` in `main`, before `run()` (it also covers the CGI pipes later).
- [ ] `poll() < 0` currently throws and stops the server. Decide what should happen instead (log and continue?). Hint: `poll` is not `read/write`, so the errno rule is different. Check what the subject says exactly.
- [ ] `makeTestConfig()` stub (PLAN Oct 10–11 + Oct 18): a function returning hard-coded ports (later: `ServerConfig`s). `main` takes the ports from it instead of the `push_back`s. Mark it `// STUB`.
- [ ] Check (the Week 1 milestone):
```bash
make re && ./webserv
curl -v localhost:8080 ; curl -v localhost:8081 ; curl -v localhost:8082
for i in $(seq 100); do curl -s localhost:8080 & done; wait     # must not crash
ls /proc/$(pgrep webserv)/fd                                     # afterwards: 0,1,2 + 3 listen fds
```
Also open `http://localhost:8080` in a browser. Browsers open extra connections and sometimes send nothing; the server must survive that.
- [ ] Commit. Tick the Oct 16–17 and Oct 18 rows in `PLAN.md`.

---
Write the code yourself (the subject's AI rules: you must be able to explain it at the defense). Afterwards, ask Claude to review it for poll-rule violations, fd/memory leaks and C++98 problems.
