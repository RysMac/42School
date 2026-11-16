#include "HttpRequest.hpp"

#include <string>
#include <iostream>
#include <cctype>

static std::string trim(const std::string& s);
static std::string toLower(const std::string& s);
static bool isUpperWord(const std::string& s);

// constructor
HttpRequest::HttpRequest() : _state(PARSE_REQUEST_LINE), _status(0), _header_bytes(0) {}
HttpRequest::~HttpRequest() {}

void HttpRequest::print_members() const
{
	// Checking :
	std::cout << " ------------------------ \n"
			<< "Status: "  << _status  << "\n"
			<< "Metoda: "  << _method  << "\n"
			<< "Sciezka: " << _path    << "\n"
			<< "Wersja: "  << _version << "\n";

	for (std::map<std::string, std::string>::const_iterator it = _headers.begin();
		it != _headers.end(); ++it)
	{
		std::cout << it->first << " => " << it->second << "\n";
	}
	std::cout << " -------------------------- \n";
}

// METHOD SP TARGET SP VERSION : exactly 3 parts, exactly 2 single spaces
// returns false and sets _status on error
bool HttpRequest::parse_request_line(const std::string& line)
{
	size_t sp1 = line.find(' ');
	if (sp1 == std::string::npos) { _status = 400; return false; }

	size_t sp2 = line.find(' ', sp1 + 1);
	if (sp2 == std::string::npos) { _status = 400; return false; }	// only 2 parts

	if (line.find(' ', sp2 + 1) != std::string::npos)
		{ _status = 400; return false; }								// 4th part or trailing space

	_method		= line.substr(0, sp1);
	_path		= line.substr(sp1 + 1, sp2 - sp1 - 1);
	_version	= line.substr(sp2 + 1);

	// empty part = leading / double / trailing space
	if (_method.empty() || _path.empty() || _version.empty())
		{ _status = 400; return false; }

	if (!isUpperWord(_method))
		{ _status = 400; return false; }								// "get", "G3T"
	if (_method != "GET" && _method != "POST" && _method != "DELETE")
		{ _status = 501; return false; }								// valid but unknown: PUT, PATCH
	// target must start with '/' (400)
	if (_path[0] != '/' )
		{ _status = 400; return false; }
	
	if (_version.length() != 8 || 
		_version.substr(0, 5) != "HTTP/" || 
		_version[6] != '.' ||
		!std::isdigit(static_cast<unsigned char>(_version[5])) || 
		!std::isdigit(static_cast<unsigned char>(_version[7])))
		{ _status = 400; return false; } // even not HTTP/... (400)

	if (_version != "HTTP/1.0" && _version != "HTTP/1.1")
		{ _status = 505; return false; } // wrong version (505)
	

	return true;
}

const std::string& HttpRequest::get_method() const
{
	return _method;
}

int HttpRequest::get_status() const
{
	return _status;
}

static bool isUpperWord(const std::string& s)
{
	for (std::string::size_type i = 0; i < s.size(); ++i)
		if (s[i] < 'A' || s[i] > 'Z')
			return false;
	return true;
}

static std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

static std::string toLower(const std::string& s)
{
	std::string result = s;
	for (std::string::size_type i = 0; i < result.size(); ++i)
		result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
	return result;
}

bool HttpRequest::get_recv_done() const
{
	print_members();
	// done = nothing more to read: either a full request or an error
	return _state == PARSE_COMPLETE || _state == PARSE_ERROR;
}

void HttpRequest::save_recv(const char* in, size_t n_bytes)
{
	_in.append(in, n_bytes);

	while (_state == PARSE_REQUEST_LINE || _state == PARSE_HEADERS)
	{
		size_t newlinePos = _in.find('\n');

		// line not "closed" yet: only check that it is not already too long
		if (newlinePos == std::string::npos)
		{
			check_limits(_in.length());
			return;
		}
		if (!check_limits(newlinePos))
			return;

		// if we have full line take it and parse it
		std::string line = _in.substr(0, newlinePos);
		if (_state == PARSE_HEADERS)
			_header_bytes += newlinePos + 1;
		_in.erase(0, newlinePos + 1);
		// strip '\r' first, only then can we see the empty line
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (_state == PARSE_REQUEST_LINE)
		{
			if (!parse_request_line(line))
			{
				set_error(_status);		// parse_request_line already chose the code
				return;
			}
			_state = PARSE_HEADERS;		// first line done so go to headers
		}
		else if (line.empty())			// end of headers, the body comes later (step 5)
		{
			// Host is required only in HTTP/1.1
			if (_version == "HTTP/1.1" && _headers.find("host") == _headers.end())
			{
				set_error(400);
				return;
			}
			_state = PARSE_COMPLETE;
		}
		else if (!parse_header_line(line))
			return;
	}
}

// "name: value". Returns false (and goes to PARSE_ERROR) on a bad line.
bool HttpRequest::parse_header_line(const std::string& line)
{
	size_t colon = line.find(':');
	if (colon == std::string::npos)
		return set_error(400);

	// raw name, before any trim: empty, or any space/tab in it
	// ("Host : x", " Host: x" = obsolete line folding) -> 400 (RFC 9112 5.1)
	std::string rawName = line.substr(0, colon);
	if (rawName.empty() || rawName.find_first_of(" \t") != std::string::npos)
		return set_error(400);

	std::string name	= toLower(rawName);
	std::string value	= trim(line.substr(colon + 1));

	// more than one Host -> 400 (RFC 9112 3.2). Other duplicates: last one wins.
	if (name == "host" && _headers.find("host") != _headers.end())
		return set_error(400);

	_headers[name] = value;
	return true;
}

// len = length of the current line (or of the unfinished data).
// Request line > 2 KB -> 414; header line > 2 KB or all headers > 8 KB -> 431.
bool HttpRequest::check_limits(size_t len)
{
	const size_t MAX_LINE_SIZE		= 2048;
	const size_t MAX_HEADERS_SIZE	= 8192;

	if (_state == PARSE_REQUEST_LINE)
	{
		if (len > MAX_LINE_SIZE)
			return set_error(414);
	}
	else if (len > MAX_LINE_SIZE || _header_bytes + len > MAX_HEADERS_SIZE)
		return set_error(431);
	return true;
}

// always returns false, so callers can write: return set_error(400);
bool HttpRequest::set_error(int status)
{
	_status = status;
	_state = PARSE_ERROR;
	return false;
}

const std::string& HttpRequest::get_path() const
{
	return _path;
}

const std::string& HttpRequest::get_version() const
{
	return _version;
}

// header names are stored lowercase; returns "" when the header is missing
std::string HttpRequest::get_header(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator it = _headers.find(toLower(name));
	if (it == _headers.end())
		return "";
	return it->second;
}

bool HttpRequest::has_header(const std::string& name) const
{
	return _headers.find(toLower(name)) != _headers.end();
}
