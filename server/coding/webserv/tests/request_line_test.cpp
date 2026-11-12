#include "HttpRequest.hpp"
#include <iostream>
#include <cstdlib>
int main(){
 const char* v[][2]={{"GET / HTTP/1.1","0"},{"GET / HTTP/1.0","0"},{"POST /a?x=1 HTTP/1.1","0"},
 {"get / HTTP/1.1","400"},{"G3T / HTTP/1.1","400"},{"BREW / HTTP/1.1","501"},{"GET index.html HTTP/1.1","400"},
 {"GET / HTTP/2.0","505"},{"GET / HTTP/9.9","505"},{"GET / FOO","400"},{"GET / HTTP/","400"},{"GET / HTTP/abc","400"},
 {"GET / HTTP/1.1x","400"},{"GET / HTTP/11","400"},{"GET / HTTP/a.b","400"},{"GET /  HTTP/1.1","400"},
 {" GET / HTTP/1.1","400"},{"GET / HTTP/1.1 ","400"},{"GET /","400"},{"","400"}};
 int bad=0;
 for(unsigned i=0;i<sizeof v/sizeof*v;i++){HttpRequest r; std::string q=std::string(v[i][0])+"\r\nHost: x\r\n\r\n"; r.save_recv(q.data(),q.size());
  int want=std::atoi(v[i][1]); if(r.get_status()!=want){bad++; std::cerr<<"FAIL ["<<v[i][0]<<"] got "<<r.get_status()<<" want "<<want<<"\n";}}
 std::cerr<<(sizeof v/sizeof*v)-bad<<"/"<<sizeof v/sizeof*v<<" pass\n";}
