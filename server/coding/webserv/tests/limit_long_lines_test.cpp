#include "HttpRequest.hpp"
#include <iostream>
static void run(const char* name, const std::string& req){
  HttpRequest r; r.save_recv(req.data(), req.size());
  std::cerr<<name<<": done="<<r.get_recv_done()<<" status="<<r.get_status()<<"\n";
}
int main(){
  run("5KB target, complete request in one recv (want 414)", "GET /"+std::string(5000,'a')+" HTTP/1.1\r\nHost: x\r\n\r\n");
  run("5KB header line, complete in one recv (want 400/431)", "GET / HTTP/1.1\r\nHost: x\r\nX-Big: "+std::string(5000,'c')+"\r\n\r\n");
}
