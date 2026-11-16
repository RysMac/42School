#include "HttpRequest.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
// feed `req` in pieces of size `chunk` (0 = all at once)
static void run(const char* name, std::string req, size_t chunk){
  HttpRequest r; size_t i=0; if(!chunk) chunk=req.size();
  while(i<req.size() && !r.get_recv_done()){ size_t n=std::min(chunk,req.size()-i); r.save_recv(req.data()+i,n); i+=n; }
  std::cerr<<name<<": done="<<r.get_recv_done()<<" status="<<r.get_status()<<" method="<<r.get_method()<<"\n";
}
int main(){
  std::string ok="GET / HTTP/1.1\r\nHost: x\r\n\r\n";
  run("ok whole, CRLF", ok, 0);
  run("ok 1 byte/call", ok, 1);
  run("ok bare LF", "GET / HTTP/1.1\nHost: x\n\n", 0);
  run("no Host (want 400)", "GET / HTTP/1.1\r\n\r\n", 0);
  run("unfinished (want done=0)", "GET / HTTP/1.1\r\nHost: x\r\n", 0);
  run("no colon (want 400)", "GET / HTTP/1.1\r\nHost x\r\n\r\n", 0);
  run("BREW (want 501)", "BREW / HTTP/1.1\r\nHost: x\r\n\r\n", 0);
  run("10KB no newline (want 414)", "GET /"+std::string(10000,'a'), 0);
  run("Host in 2nd recv (want 0)", ok, 20);
  run("two Hosts (want 400)", "GET / HTTP/1.1\r\nHost: a\r\nHost: b\r\n\r\n", 0);
  run("space before colon (want 400)", "GET / HTTP/1.1\r\nHost : a\r\n\r\n", 0);
  run("empty header name (want 400)", "GET / HTTP/1.1\r\nHost: a\r\n: v\r\n\r\n", 0);
  run("folded line (want 400)", "GET / HTTP/1.1\r\nHost: a\r\n  more\r\n\r\n", 0);
  run("HTTP/1.0 no Host (want 0)", "GET / HTTP/1.0\r\n\r\n", 0);
  std::string many="GET / HTTP/1.1\r\nHost: x\r\n";
  for(int k=0;k<10;k++) many+="X-"+std::string(1,'a'+k)+": "+std::string(1000,'v')+"\r\n";
  run("10 x 1KB headers = 10KB total (want 431)", many+"\r\n", 0);
  run("10KB headers, 100 bytes/call (want 431)", many+"\r\n", 100);
}
