#include "HttpRequest.hpp"
#include <iostream>
#include <sstream>
static void run(const char* name, const std::string& req){
  HttpRequest r; r.save_recv(req.data(), req.size());
  std::cerr<<name<<": done="<<r.get_recv_done()<<" status="<<r.get_status()<<"\n";
}
int main(){
  std::ostringstream h; h<<"GET / HTTP/1.1\r\nHost: x\r\n";
  for(int i=0;i<40;i++) h<<"X-Hdr-"<<i<<": "<<std::string(60,'v')<<"\r\n";
  h<<"\r\n";
  run("40 short headers in one recv, ~2.8KB total (each line ok)", h.str());
  run("short POST with 3KB body in same recv", "POST / HTTP/1.1\r\nHost: x\r\nContent-Length: 3000\r\n\r\n"+std::string(3000,'b'));
}
