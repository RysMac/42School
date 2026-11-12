# Parser tests (no server, no sockets)

Each file is a standalone program that feeds bytes to `HttpRequest`. Results are printed to stderr.
Build and run one from `coding/webserv/`:

    c++ -std=c++98 -Isrc/http tests/split_test.cpp src/http/HttpRequest.cpp -o /tmp/t && /tmp/t >/dev/null

- `request_line_test.cpp`: 20 request lines and the expected status for each (prints FAIL lines + a pass count)
- `split_test.cpp`: the same request in different splits (all at once, 1 byte per call, bare `\n`), plus missing Host, no `:`, BREW, and 10 KB without a newline
- `limit_short_lines_test.cpp`: many short lines in one recv must NOT hit the line limit (want status 0)
- `limit_long_lines_test.cpp`: one long line that arrives complete MUST hit the limit (414 / 400-431)
