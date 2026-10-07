# Webserv — 5-week plan (team of 2, ~4h/day, working mostly independently)

## Context
Subject: `en.subject.pdf` (Webserv v24.0) — an HTTP/1.x server in C++98, run as `./webserv [config]`.
Starting point: `coding/` — a blocking tutorial server (HDE namespace: `SimpleSocket → BindingSocket → ListeningSocket`, `SimpleServer`, `TestServer`). It proves socket/bind/listen/accept work, but it is **not** compliant yet:

| Problem in current code | Where | Subject rule it breaks |
|---|---|---|
| `accept()` + `read()` blocking, no poll | `Networking/Servers/TestServer.cpp` | single non-blocking poll for ALL I/O → else grade 0 |
| `char buffer[30000] = {0};` in-class init, `char *hello = "..."` | `TestServer.hpp/.cpp` | doesn't compile with `-std=c++98 -Werror` (Servers/Makefile hides it with `#-Werror -std=c++98`) |
| `test_connection()` calls `exit()` on error | `Sockets/SimpleSocket.cpp` | server must never stop; errors must be handled |
| `listen()` called twice, no `SO_REUSEADDR`, no `O_NONBLOCK` | `Sockets/ListeningSocket.cpp` | restart issues / non-blocking requirement |
| `new ListeningSocket` never deleted, no destructor/copy (Orthodox Canonical) | `SimpleServer.cpp` | leaks, 42 C++ style |
| One port hard-coded (8080) | `TestServer.cpp` | multiple `host:port` from config |
| `ConnectingSocket` (client socket) | `Sockets/` | not needed for a server — drop it |

**Keep**: the socket-wrapping idea — refactor into a `ListenSocket` class that does socket → setsockopt(SO_REUSEADDR) → fcntl(O_NONBLOCK) → bind → listen and throws exceptions instead of `exit()`.

## Target architecture
```
main.cpp            parse config → build ServerManager → run()
config/             Lexer, ConfigParser, ServerConfig, LocationConfig
net/                ListenSocket, Client (fd, in-buffer, out-buffer, state, timestamps)
core/               ServerManager  (ONE poll() loop over listen fds + client fds + CGI pipes)
http/               HttpRequest (incremental parser), HttpResponse (builder), StatusCodes, MimeTypes
handlers/           Router (pick server+location), StaticHandler (GET/autoindex), UploadHandler (POST),
                    DeleteHandler, CgiHandler (fork/execve/pipes registered in the same poll)
www/ conf/ tests/   demo sites, configs for every feature, Python test scripts
```
Key rule: every `recv/send/read/write` on a socket or pipe happens **only** after poll reports POLLIN/POLLOUT for that fd; never look at `errno` after them (treat `<=0` as close/error).

## Working independently — how to not get blocked
- **Track A (me)** — networking & HTTP: event loop, client lifecycle, request parser, response, static/GET/DELETE, timeouts.
- **Track B (partner)** — config & features: config parser, routing, error pages, uploads/POST, CGI.
- Day 1: agree only on the **interface headers** (`ServerConfig`, `LocationConfig`, `HttpRequest`, `HttpResponse`). After that, nobody waits for anybody.
- **Stub what you don't own**: if the partner's part isn't ready, write a throwaway stub so you can keep going:
  - no config parser yet → `ServerConfig makeTestConfig()` returning hard-coded ports/roots/locations;
  - no router yet → map URI directly to `root + uri`;
  - no error pages yet → `"<h1>" + code + "</h1>"`;
  - no CGI yet → return 501.
  Mark stubs with `// STUB` and `grep` them away before merging.
- Merge at the end of each week (Sunday). If the partner is behind, the "if alone" column says what you take over.

## Timeline (start Thu 2026-10-08, defense-ready Thu 2026-11-12)

### Week 0 — Oct 8–11: Study & foundation
| Day | Task | Done |
|---|---|---|
| Oct 8 | Read RFC 1945 / 7230-7231 basics (request line, headers, status codes, chunked). Play with `telnet`/`curl -v` against NGINX (`docker run -p 8081:80 nginx`). | [ ] |
| Oct 9 | With partner: agree on interface headers + git flow (branch per track). | [ ] |
| Oct 10–11 | New repo layout + root `Makefile` (NAME=webserv, all/clean/fclean/re, `-Wall -Wextra -Werror -std=c++98`, no relink). Fix the C++98 errors above. Write `makeTestConfig()` stub. | [ ] |

✅ Milestone: `make` builds `webserv` cleanly with C++98 flags.

### Week 1 — Oct 12–18: Event loop (+ config parser on B)
| Days | Me (A) | Partner (B) | If alone / B late | Done |
|---|---|---|---|---|
| Oct 12–13 | Refactor sockets → `ListenSocket` (REUSEADDR, O_NONBLOCK, exceptions, OCF). | Lexer: tokens, `{ } ;`, comments. | keep using stub config | [ ] |
| Oct 14–15 | `ServerManager`: one `poll()` over N listen fds; accept → non-blocking client fd → add to pollfd vector. | Parser: `server{ listen, server_name, error_page, client_max_body_size, location{...} }`. | — | [ ] |
| Oct 16–17 | Client read/write buffers, POLLIN/POLLOUT switching, close on 0/-1, remove from poll. Hard-coded "Hello" response. | `location` directives: `methods`, `return`, `root`, `autoindex`, `index`, `upload_store`, `cgi`. Validation. | — | [ ] |
| Oct 18 | Merge; `main` loads config and opens every `listen` port. | | | [ ] |

✅ Milestone: listens on 2+ ports, browser gets "Hello" on all, 100 parallel `curl`s don't crash it.

### Week 2 — Oct 19–25: HTTP parsing + static site
| Days | Me (A) | Partner (B) | If alone / B late | Done |
|---|---|---|---|---|
| Oct 19–20 | Incremental `HttpRequest` parser (request line → headers → body), handles partial reads. | `Router`: server by port, longest-prefix location, method check → 405. | stub: `root + uri` | [ ] |
| Oct 21–22 | Body: `Content-Length` + **chunked decoding**; `client_max_body_size` → 413; malformed → 400; long URI → 414. | Default error pages + custom `error_page`. | stub: `<h1>code</h1>` | [ ] |
| Oct 23–24 | `HttpResponse` builder: status line, headers (Content-Type, Content-Length, Connection, Date), MIME table. | `StaticHandler`: index file, `autoindex` (opendir/readdir), 404/403, redirects 301/302. | I write a basic GET file handler myself | [ ] |
| Oct 25 | Merge + browse a full static site in Firefox/Chrome. | | | [ ] |

✅ Milestone: static demo site with CSS/images fully browsable; error codes match NGINX.

### Week 3 — Oct 26–Nov 1: POST, DELETE, CGI
| Days | Me (A) | Partner (B) | If alone / B late | Done |
|---|---|---|---|---|
| Oct 26–27 | `DeleteHandler` (204/404/403). Keep-alive vs close. | `UploadHandler`: raw body + `multipart/form-data` → `upload_store`, 201. | raw-body upload only first | [ ] |
| Oct 28–29 | Timeouts: idle client / slow body / CGI → 408/504, no request hangs. | `CgiHandler`: fork + execve, env (REQUEST_METHOD, QUERY_STRING, CONTENT_LENGTH, CONTENT_TYPE, SCRIPT_FILENAME, PATH_INFO, SERVER_PROTOCOL…), chdir to script dir. | CGI returns 501 meanwhile | [ ] |
| Oct 30–31 | Register CGI pipes **in the same poll()** (write body to stdin pipe, read stdout pipe, non-blocking waitpid, kill on timeout). | CGI output parsing: script headers, `Status:`, EOF-terminated body. Python + PHP test scripts. | — | [ ] |
| Nov 1 | Merge. | | | [ ] |

✅ Milestone: GET/POST/DELETE work; upload form works in browser; Python CGI works with GET and chunked POST.

### Week 4 — Nov 2–8: Hardening & testing
| Days | Task | Done |
|---|---|---|
| Nov 2–3 | Python test suite (`tests/`): status codes, chunked, oversized body, bad requests, many ports, DELETE, CGI. Run the 42 tester. | [ ] |
| Nov 4–5 | Stress: `siege -b -c 100 -t 1m`, disconnects mid-request, `valgrind --leak-check=full`, fd leaks (`ls /proc/<pid>/fd`). Fix. | [ ] |
| Nov 6 | Ignore SIGPIPE, never crash on bad config / missing files, clean shutdown on SIGINT. | [ ] |
| Nov 7–8 | Compare headers/behaviour vs NGINX for the same config; fix diffs. | [ ] |

✅ Milestone: siege 100% availability, valgrind clean, all tests green.

### Week 5 — Nov 9–12: Docs, bonus, defense prep
| Day | Task | Done |
|---|---|---|
| Nov 9 | `README.md` (first line italic "This project has been created as part of the 42 curriculum by <login1>, <login2>", Description, Instructions, Resources + AI usage). | [ ] |
| Nov 10 | Demo configs + `www/` for every feature. Remove `.o`/binaries from git. | [ ] |
| Nov 11 | Bonus only if mandatory is perfect: cookies/sessions, second CGI type. | [ ] |
| Nov 12 | Mock defense: explain your partner's code too; practice a "small live modification". | [ ] |

## Verification (run at every milestone)
- `make re` with `-Wall -Wextra -Werror -std=c++98` — no warnings, no relink on second `make`.
- `curl -v`, `telnet localhost 8080`, browser on every configured port.
- `grep -rn "recv\|send\|read(\|write(" src/` — each call reachable only from a poll-ready branch.
- `grep -rn "STUB" src/` — empty before final merge.
- `python3 tests/run_all.py`, 42 tester, `siege`, `valgrind`.

## Risk notes
- Grade-0 risks: socket/pipe I/O outside poll, checking `errno` after read/write, any crash. Check these every Sunday.
- CGI in poll (week 3) is the hardest part — Week 5 bonus time is the buffer if behind.
- Since you work independently: you must still be able to explain the whole codebase at defense — read each merge from your partner.
