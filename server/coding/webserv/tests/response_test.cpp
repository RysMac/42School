#include "HttpResponse.hpp"
#include <iostream>
#include <string>
// prints each response with \r\n shown, so line endings are visible
static void show(const char* name, const HttpResponse& r){
  std::string s=r.to_string(), v;
  for(size_t i=0;i<s.size();i++){ if(s[i]=='\r') v+="\\r"; else v+=s[i]; }
  std::cerr<<"=== "<<name<<" ("<<s.size()<<" bytes)\n"<<v<<"\n";
}
int main(){
  HttpResponse ok; ok.set_body("hello", "text/plain"); show("200 text/plain", ok);
  show("404 error page", HttpResponse::make_error(404));
  show("431 error page", HttpResponse::make_error(431));
  HttpResponse bin; bin.set_body(std::string("a\0b",3), "application/octet-stream");
  bin.set_header("Content-Length","999"); show("binary body with \\0, fake Content-Length ignored (want 3)", bin);
  HttpResponse copy(ok), assigned; assigned=ok; assigned=assigned;
  std::cerr<<"copy == original: "<<(copy.to_string()==ok.to_string())<<", assigned == original: "<<(assigned.to_string()==ok.to_string())<<"\n";
  show("unknown code 299", HttpResponse::make_error(299));
}
