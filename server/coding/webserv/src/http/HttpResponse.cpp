#include "HttpResponse.hpp"

#include <sstream>

// defaults: 200, and we close after every response (no keep-alive yet)
HttpResponse::HttpResponse() : _status(200)
{
	_headers["Connection"] = "close";
}

// copy constructor: copy every member (map and string copy themselves)
HttpResponse::HttpResponse(const HttpResponse& other)
	: _status(other._status), _headers(other._headers), _body(other._body)
{
}

// copy assignment: skip self-assignment (r = r), copy, return *this for a = b = c
HttpResponse& HttpResponse::operator=(const HttpResponse& other)
{
	if (this != &other)
	{
		_status		= other._status;
		_headers	= other._headers;
		_body		= other._body;
	}
	return *this;
}

HttpResponse::~HttpResponse() {}

void HttpResponse::set_status(int code)
{
	_status = code;
}

// Content-Length is ignored here: to_string() always computes it from the body,
// so it can never be out of date
void HttpResponse::set_header(const std::string& name, const std::string& value)
{
	if (name == "Content-Length")
		return;
	_headers[name] = value;
}

// a body and its type always go together
void HttpResponse::set_body(const std::string& body, const std::string& content_type)
{
	_body = body;
	_headers["Content-Type"] = content_type;
}

// status line, headers, Content-Length, empty line, body. Every line ends in \r\n.
std::string HttpResponse::to_string() const
{
	std::ostringstream out;

	out << "HTTP/1.1 " << _status << " " << reason_phrase(_status) << "\r\n";
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin();
		it != _headers.end(); ++it)
	{
		out << it->first << ": " << it->second << "\r\n";
	}
	out << "Content-Length: " << _body.size() << "\r\n";
	out << "\r\n";
	out << _body;	// operator<< on std::string writes all bytes, '\0' included
	return out.str();
}

// a complete error response with a small default page
// STUB: error_page from the config will replace the default body later
HttpResponse HttpResponse::make_error(int code)
{
	std::ostringstream	page;
	std::string			phrase = reason_phrase(code);

	page << "<!DOCTYPE html>\n"
		 << "<html><head><title>" << code << " " << phrase << "</title></head>\n"
		 << "<body><h1>" << code << " " << phrase << "</h1></body></html>\n";

	HttpResponse r;
	r._status = code;
	r.set_body(page.str(), "text/html");
	return r;
}

// the one code -> phrase table. Must cover every code HttpRequest can produce.
std::string HttpResponse::reason_phrase(int code)
{
	switch (code)
	{
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 408: return "Request Timeout";
		case 413: return "Content Too Large";
		case 414: return "URI Too Long";
		case 431: return "Request Header Fields Too Large";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 505: return "HTTP Version Not Supported";
	}
	return "Unknown";	// a code missing above is a bug, but the status line stays valid
}
