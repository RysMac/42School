# Job 3: Understand the request, answer it precisely (PLAN Week 2, this week Oct 28 – Nov 3, ~4h/day)

## ▶ Progress (Nov 16, checked against the code). Next: step 3 (`HttpResponse` uses the parser), then step 0 leftovers.
- **Pushed** for the partner (branch `server`): Nov 12 `d453b32` (steps 1, 2a), Nov 16 `95e6db1` (step 2 done). See also the "Current status" block at the top of `PLAN.md`.
- Step 1 done: `ServerConfig` + `makeTestConfig()` (marked `// STAB` → fix to `// STUB`, or the final `grep STUB` misses it), `www/` site.
- Step 2 done (Nov 16): `src/http/HttpRequest.*`, by-value member of `Client`, `_in` lives in the parser. `save_recv` loop: find `\n`, strip `\r`, erase the consumed line (bare `\n` accepted).
  - Request line: 400 / 501 / 505 (`parse_request_line`).
  - Headers (`parse_header_line`): name checked **raw, before trim**: empty, or space/tab in it (`Host : a`, folded lines) → 400; then lowercased; value trimmed; no `:` → 400. Duplicates: two `Host` → 400, any other header → last one wins.
  - Host: checked at the empty line (when all headers are known), HTTP/1.1 without Host → 400, HTTP/1.0 may omit it.
  - Limits (`check_limits`): request line > 2 KB → 414; header line > 2 KB or all headers > 8 KB (`_header_bytes`) → 431. Also checked on data that has no `\n` yet.
  - States: `PARSE_ERROR` + `set_error(code)` (always returns false); `get_recv_done()` is true on `PARSE_COMPLETE` or `PARSE_ERROR`. The empty line → `PARSE_COMPLETE` (no BODY yet: step 5).
  - Getters for step 3: `get_method`, `get_status`, `get_path`, `get_version`, `get_header(name)` ("" if missing), `has_header(name)`.
  - The Host check and duplicate-Host were written by you; the rest of step 2 (header-name rules, ERROR state, limits/helper, getters) was written by Claude on your request on Nov 16 → **read `parse_header_line` and `check_limits` before the defense**.
  - Still open (your choice, later): remove `print_members()` from `get_recv_done()` (it prints on every recv, and it's a side effect in a `const` getter).
- Tests: `coding/webserv/tests/` (4 standalone programs, README). Nov 16 run: request_line 20/20, split 16/16 (8 new: Host in a later recv, two Hosts, `Host :`, empty name, folded line, HTTP/1.0 without Host, 10 KB of headers → 431 at once and in 100-byte pieces), both limit tests ok.
- Learned (Nov 16): a check placed after the `while` runs on **every** `recv`, not when the headers end → a request split across recvs got 400 ("1 byte/call" test broke). `map[key]` inserts a missing key; use `find` to only read. Same expression (`find != end`) means "found": copy-pasting it into the opposite check inverted it.
- **Not wired yet:** the answer ignores the parser. Every request, even a 400/501, gets `200 ok` + `www/img/logo.png` from the `Client` constructor (checked Nov 12: `BREW / HTTP/1.1` → `HTTP/1.1 200 ok`). Step 3 fixes that.
- Step 0 still open: 5 MB SIGPIPE proof; comment at `ServerManager.cpp:149`; empty line after `{` in `main`; `client d` typo (`ServerManager.hpp:32`); review notes from Oct 29 (`const ServerConfig&` in the `ServerManager` constructor, `ServerConfig c = makeTestConfig();` in one line).
- Learned (Oct 29): `sizeof(std::string)` is the object size (32), not the content (`.size()`); wrong `Content-Type` → garbage in the browser; one fixed file for every URL → no CSS/image, which is why the path must be parsed.
- Reference server: `python3 -m http.server -d www 9100`.

Code lives in `coding/webserv/`. Starting point was commit `37dcc59`; `d453b32` (Nov 12) holds steps 1 and 2a, `95e6db1` (Nov 16) finishes step 2.

Goal: right now every client gets the same hardcoded 404, whatever it asked for. By the end of this job the server **reads what was asked** (method, path, headers, body), and answers with the **right status code and the right content**: files from a `www/` folder, and a proper error page when something is wrong. At the end, a small static site (HTML + CSS + an image) must work in a browser.

**Scope decisions (Oct 28):**
- **No config parser this week.** Ports, root, index and the body limit come from a hardcoded `makeTestConfig()` stub (step 1). The `.conf` parser, routing by `location`, `error_page`, redirects (301/302 need the `return` directive) and `autoindex` per location all wait for the config job.
- You are working alone, so PLAN's "Partner (B)" column for Week 2 is yours too, but only in its stub form: one server, one location `/`, default error pages.
- Steps 0–4 are the must-do. Step 5 (bodies) is must-do for `Content-Length`, a stretch goal for chunked. Step 6 closes the week.

---

## 0. Leftovers from job2 (≈30 min) — [ ]
- [ ] **Prove the SIGPIPE fix.** The tests so far don't prove it: the 41-byte response always fits in one `send`, so the old code would have passed them too. Temporarily make the body 5 MB, then:
  1. comment out the `signal` line → `curl -s localhost:8080 | head -c 10` → the server **must die** (exit code 141). If it doesn't die, the test proves nothing; try a few times.
  2. put the line back → same command → the server survives, and the next `curl localhost:8081` still answers.
- [ ] Rewrite the comment at `ServerManager.cpp:149` so it says what's true ("SIGPIPE is ignored in main, so send returns -1 on a dead peer").
- [ ] Remove the empty line right after `{` in `main`. Fix the `client d` → `client fd` typo in `ServerManager.hpp:22`.
- [ ] Optional: rename `delClient(i)` (it removes by pfd **index**) and `get_recv_done`/`get_send_done` to question-style names (`isRequestComplete()`…).
- [ ] Defense question to prepare: the subject says "poll() must monitor both reading and writing simultaneously". When a request is complete you set `events = POLLOUT` (POLLIN is gone). Is that still OK? What would you answer an evaluator who asks? (No change needed, just have an answer.)
- [ ] Commit ("job2 done"). Tick the Oct 16–17 row in `PLAN.md`.

Already checked Oct 28 (no need to redo): curl on 8080–8082, 100 parallel curls, fds `0 1 2 3 4 5` afterwards, 200 clients that reset right after sending, browser on 8080.

## 1. Opening questions + the config stub (≈40 min) — [x]
**Look at real requests first (no code).** Run `nc -l 9000` and open `http://localhost:9000/some/page?x=1` in Firefox. `nc` prints exactly what the browser sent. Also try `curl -v localhost:9000/a`, and a `curl -d 'hello' localhost:9000/up` (a POST). Copy one browser request into this file and answer:
Copied response from browser:
GET /some/page?x=1 HTTP/1.1
Host: localhost:9000
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:158.0) Gecko/20100101 Firefox/158.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.9
Accept-Encoding: gzip, deflate, br, zstd
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: none
Sec-Fetch-User: ?1
Priority: u=0, i

Copied from curl:
nc -l 9000 gives:
GET /a HTTP/1.1
Host: localhost:9000
User-Agent: curl/8.5.0
Accept: */*

nc -l 9000 gives:
POST /up HTTP/1.1
Host: localhost:9000
User-Agent: curl/8.5.0
Accept: */*
Content-Length: 5
Content-Type: application/x-www-form-urlencoded

- What are the three parts of the first line? What separates them?
-> they are separated by " " SPACE!!! . 1st is method 2nd request target 3rd is the version.
- What separates a header name from its value? Is `host:` the same header as `Host:`?
-> separeted by ":", but only first colon matters!. lower/upper case-insensitive
- Where does the body start? How does the server know how long the POST body is?
-> The body is in the end and how long it is - it is defined by Content-Length.
- What does the browser ask for right after `/`, without you clicking anything? (Hint: a small icon.) What should your server answer?
-> I dont know this, but I can imagine that browser asks for communication and new socket maybe? Server should answer ok 200 if everything is ok and eg 401 when data are not found.


**The stub.** Write `makeTestConfig()` (mark it `// STUB`). It returns hardcoded values: the ports, `root = "www"`, `index = "index.html"`, `client_max_body_size` (e.g. 1 MB). `main` takes the ports from it instead of the `push_back`s.
- [x] Decide what it returns: a small struct now, which becomes the real `ServerConfig` later. Choose field names you'd keep when the parser arrives, so that replacing the stub changes only one function.
- [x] Who needs this config? `ServerManager` creates the sockets, but the code that answers a request needs the root. How does it get there? (Store it in `ServerManager`, pass it down?) Pick one and be able to say why.
- [x] Create `www/` with `index.html`, `style.css` (linked from the HTML), an image, and a subfolder with its own `index.html`.

## 2. `HttpRequest`: an incremental parser (≈2 sessions) — [x] done Nov 16 (body = step 5, sending the error = step 3)
New files: `src/http/HttpRequest.hpp/.cpp`. It replaces the `\r\n\r\n` search in `Client::save_recv`: **the parser** decides when a request is complete, not `Client`.

What it must end up knowing (a minimal version):
```cpp
// state: REQUEST_LINE -> HEADERS -> BODY -> DONE   (or ERROR, with a status code)
std::string method, target (path + ?query), version;
std::map<std::string, std::string> headers;   // name stored in lowercase
std::string body;
int         error_status;                      // 0 = ok, else 400 / 414 / 501 / 505 ...
```

**The central design decision (write your answer here before coding):** data arrives in pieces, split anywhere (`"GE" | "T /ind" | "ex.html HTTP/1.1\r" | "\n..."`). Two options:
- (a) Every time new bytes arrive, parse `_in` again from the start.
- (b) Keep a **state** and a position. Consume complete lines, remember where you stopped, and continue from there next time.

PLAN.md says "incremental", which is (b). Why is (a) a problem? (Think: a 1 MB body arriving in 64 KB pieces → how many times do you re-read the headers?) Also: where do the not-yet-complete bytes wait: in `Client::_in`, or inside the parser?

- [x] **Request line:** exactly `METHOD SP target SP version`. What's a 400? (Missing parts, extra spaces, lowercase `get`.) Method you don't know at all (`BREW`) → 501. Version not `HTTP/1.0` or `HTTP/1.1` → 505. Target longer than your limit (e.g. 8 KB) → 414.
- [x] **Headers:** one per line until the empty line. `name:value` with optional spaces around the value (trim them). Store the name in lowercase. No `:` → 400. Decide: what if the same header comes twice?
  -> two `Host` → 400 (RFC 9112 §3.2); any other duplicate: the last one wins. Empty name or space/tab in the name → 400.
- [x] **HTTP/1.1 requires `Host`.** Missing → 400. HTTP/1.0 may omit it. (Checked at the empty line, not after every recv.)
- [x] **Limit:** headers without an end (a client that never sends the empty line) must not fill your memory. Choose a limit (e.g. 8 KB of headers) → 431 or 400. Your choice, but write it down.
  -> one line ≤ 2 KB (request line → 414, header line → 431); all header lines together ≤ 8 KB → 431.
- [x] **Trap 1 (line endings):** HTTP says `\r\n`. Some tools send only `\n`. Decide whether you accept a bare `\n` (RFC 7230 §3.5 allows it, and nginx accepts it). Either answer is fine if you can defend it.
- [x] **Trap 2 (the split `\r` | `\n`):** a piece ending in `\r` is **not** a complete line yet. Your job2 test already sends exactly this split; keep it.
- [~] **Trap 3 (an error in the middle):** once the state is ERROR, what happens to the bytes that are still arriving? You answer with the error and close (`Connection: close`). Don't keep parsing.
  -> parser side done: `PARSE_ERROR` stops the loop and `get_recv_done()` is true, so `Client` stops reading. Answering with the error + `Connection: close` is step 3.
- [x] Keep the parser **free of sockets**: it gets bytes, it never calls `recv`. Then you can test it without the server.

Tests (each must give the right code, and the server must survive):
```bash
printf 'GET / HTTP/1.1\r\nHost: x\r\n\r\n'            | nc -q1 localhost 8080   # ok
printf 'get / HTTP/1.1\r\nHost: x\r\n\r\n'            | nc -q1 localhost 8080   # 400 (or 501, defend it)
printf 'GET / HTTP/1.1\r\n\r\n'                       | nc -q1 localhost 8080   # 400: no Host
printf 'GET / HTTP/2.0\r\nHost: x\r\n\r\n'            | nc -q1 localhost 8080   # 505
printf 'BREW / HTTP/1.1\r\nHost: x\r\n\r\n'           | nc -q1 localhost 8080   # 501
printf 'GET / HTTP/1.1\r\nHost x\r\n\r\n'             | nc -q1 localhost 8080   # 400: no ':'
curl -s -o /dev/null -w '%{http_code}\n' "localhost:8080/$(head -c 10000 /dev/zero | tr '\0' a)"  # 414
```
Plus the job2 test: one request in 3 pieces, split at `\r` | `\n`. The answer comes only after the last piece.

## 3. `HttpResponse`: building the answer (≈1 session) — [ ]
New files: `src/http/HttpResponse.hpp/.cpp`. It holds a status code, headers and a body, and turns them into the bytes for `_out`.
- [ ] Status code → reason phrase table (200 OK, 400 Bad Request, 403, 404, 405, 413, 414, 500, 501, 505…). One place, not strings scattered through the code.
- [ ] Always send `Content-Length` and `Connection: close` (keep-alive comes later). `Content-Type` from step 4. `Date` is optional (nginx sends it).
- [ ] **Default error pages** (the subject requires them): a helper that makes a complete response for any error code, with a small HTML body like `<h1>404 Not Found</h1>`. Mark it `// STUB` where `error_page` from the config will plug in later.
- [ ] **Move `_out` out of the `Client` constructor.** Your own comment says it's not Client's job. New flow: request is DONE → *something* builds the response → `Client` receives the finished bytes and sends them. Who is that "something", and who calls it? (`ServerManager` in the POLLIN branch, or a separate function/class?) Draw the arrows before writing it.
- [ ] Check: the 400/414/501/505 tests from step 2 now answer with the right status line **and** an HTML body you can see in the browser.

## 4. Static GET: serving files (≈2 sessions) — [ ]
New files: `src/handlers/StaticHandler.*` (or one function to start with). Path = `root + target` (without the `?query` part).
- [ ] Only GET for now. Any other known method → 405 (with an `Allow: GET` header; check what nginx sends). POST/DELETE come with the config job and Week 3.
- [ ] Use `stat()` on the path: does not exist → 404; a directory → `index.html` inside it, or 403 if there's none (autoindex comes later); a regular file → read it and send it with 200; no permission → 403.
- [ ] **Directory without a trailing `/`** (`/sub` instead of `/sub/`): nginx answers 301 to `/sub/`. Why? (Think about relative links inside that page, like `style.css`.) Implement it, or note it as a TODO. Your choice.
- [ ] **Reading the file:** the subject says regular disk files don't need `poll()` (only sockets and pipes do). So reading the whole file at once (e.g. `std::ifstream` in binary mode) is allowed. Make sure it's binary-safe: an image must arrive byte for byte.
- [ ] **MIME table:** extension → `Content-Type` (`.html`, `.css`, `.js`, `.png`, `.jpg`, `.gif`, `.ico`, `.txt`; unknown → `application/octet-stream`). Without the right type, the browser won't apply your CSS.
- [ ] **Trap 4 (path traversal):** `curl --path-as-is localhost:8080/../../etc/passwd`. What does your server send? It must **never** serve a file outside `root`. Decide how you prevent it (reject `..` segments, or resolve the path and check the prefix) and write down why.
- [ ] **Trap 5 (a file that's too big):** a 1 GB file read into one `std::string`… Fine for now; note the limit as a TODO.

Tests:
```bash
curl -v localhost:8080/                  # 200, index.html, Content-Type text/html
curl -v localhost:8080/style.css         # 200, text/css
curl -s localhost:8080/img.png | cmp - www/img.png && echo SAME   # binary-exact
curl -v localhost:8080/nope              # 404 + your error page
curl -v localhost:8080/sub/              # the subfolder's index.html
curl -v -X DELETE localhost:8080/        # 405
curl -v --path-as-is localhost:8080/../../etc/passwd   # NOT the passwd file
```
And in Firefox: the page with its CSS and image, the favicon request in the Network tab (404 is fine), no errors in the terminal.

## 5. Request bodies (≈1–2 sessions) — [ ]
The BODY state from step 2. Nothing uses the body yet (uploads are Week 3), but the parser must read it **correctly**, or the next request on the connection gets corrupted, and the 413 must work.
- [ ] **`Content-Length: N`:** the request is DONE after exactly N body bytes, not before. Not a number / negative → 400.
- [ ] **413:** if `Content-Length` > `client_max_body_size`, answer 413 **as soon as you've seen the header**, without receiving the body first. Why is it worth refusing early?
- [ ] Both `Content-Length` and `Transfer-Encoding` → 400 (RFC 7230 §3.3.3: this is how request-smuggling attacks work).
- [ ] What does a POST to a static file answer for now? (405, as in step 4.) Check that the body is still read (or the connection closed) cleanly.
- [ ] **Stretch, chunked decoding** (`Transfer-Encoding: chunked`): `size-in-hex\r\n data\r\n` … `0\r\n\r\n`. The subject says the server must un-chunk before CGI, so this is needed by Week 3. It's a second small state machine inside BODY. Same rule: chunks are split anywhere across `recv`s.

Tests:
```bash
curl -v -d 'hello' localhost:8080/            # body of 5 bytes, then 405
head -c 2000000 /dev/zero | curl -v --data-binary @- localhost:8080/   # 413 (limit 1 MB)
printf 'POST / HTTP/1.1\r\nHost: x\r\nContent-Length: 5\r\n\r\nhel' | nc -q3 localhost 8080   # waits: only 3 of 5 bytes
curl -v -H 'Transfer-Encoding: chunked' -d 'hello' localhost:8080/  # stretch: chunked
```

## 6. Close the week (≈30 min) — [ ]
- [ ] The job2 checks still pass: 3 ports, 100 parallel curls (`for i in $(seq 100); do curl -s localhost:8080 >/dev/null & done; wait`), fds `0 1 2` + 3 listen sockets afterwards, 5 MB partial send, SIGPIPE survival.
- [ ] Browse the `www/` site in Firefox: page, CSS, image, subfolder, a 404.
- [ ] Optional: compare with nginx on the same files (`docker run --rm -p 8090:80 -v $PWD/www:/usr/share/nginx/html:ro nginx`). Compare `curl -v` output for `/`, `/nope`, `/sub` and a 405. Note the differences here; don't fix them all.
- [ ] `grep -rn STUB src/` lists only what's waiting for the config job.
- [ ] Commit. Tick the Week 2 rows in `PLAN.md` (A column; B column = stub only), and re-date the later weeks if you want to keep PLAN.md honest.

---
Write the code yourself (the subject's AI rules: you must be able to explain it at the defense). Afterwards, ask Claude to review it for poll-rule violations, fd/memory leaks, wrong status codes and C++98 problems.
