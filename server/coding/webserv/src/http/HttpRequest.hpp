#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>

class HttpRequest
{
  public:
	HttpRequest();
	~HttpRequest();

	enum State {
		PARSE_REQUEST_LINE,
		PARSE_HEADERS,
		PARSE_BODY,
		PARSE_COMPLETE,	// full request read, _status == 0
		PARSE_ERROR		// bad request, _status holds the HTTP error code
	};
	
	const std::string&	get_method() const; // reference is it safe??
	int					get_status() const;
	const std::string&	get_path() const;
	const std::string&	get_version() const;
	std::string			get_header(const std::string& name) const;	// "" if missing
	bool				has_header(const std::string& name) const;

	// members for saving client's request data
	void		save_recv(const char* in, size_t n_bytes);
	bool		get_recv_done() const;
	void		print_members() const;
  
  private:
	HttpRequest(const HttpRequest&); // safe but not needed
	HttpRequest& operator=(const HttpRequest&); // safe but not needed

	bool	parse_request_line(const std::string& line);
	bool	parse_header_line(const std::string& line);
	bool	check_limits(size_t len);
	bool	set_error(int status);

	State       _state;      // parser state first line || headers etc
	int			_status;	// 0 = no error so far, otherwise the HTTP error code (400, 501...)
	std::string	_method;
	std::string	_path;
	std::string	_version;	// eg. http/1.1

	// saving received data
	std::string	_in;     		// bytes received so far
	// bool		_recv_done;  	// have we received the whole data? -> replaced by PARSE_COMPLETE

	size_t		_header_bytes;	// bytes of header lines consumed so far (8 KB limit)

	std::map<std::string, std::string>	_headers;	// names lowercase
};

#endif // HTTP_REQUEST_HPP
