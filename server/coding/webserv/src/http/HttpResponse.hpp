#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <map>

class HttpResponse
{
  public:
	HttpResponse();
	HttpResponse(const HttpResponse& other);
	HttpResponse& operator=(const HttpResponse& other);
	~HttpResponse();

	void set_status(int code);
	void set_header(const std::string& name, const std::string& value);
	void set_body(const std::string& body, const std::string& content_type);

	std::string	to_string() const;		// bytes to send

	static HttpResponse		make_error(int code); // error response STUB: error_page later

  private:
	int										_status;
	std::map<std::string, std::string>		_headers;
	std::string								_body;

	static	std::string		reason_phrase(int code);
};

#endif // HTTP_RESPONSE_HPP
