#include "HttpRequest.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <cctype>

static std::string trim(const std::string& s);
static std::string toLower(const std::string& s);
static bool isUpperWord(const std::string& s);

// constructor
HttpRequest::HttpRequest() : _state(PARSE_REQUEST_LINE), _status(0) {}
HttpRequest::~HttpRequest() {}

void HttpRequest::parsing()
{
	std::istringstream	stream(_in);
	std::string			line;

	_status = 0;
	_headers.clear();

	std::getline(stream, line);
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);

	if (parse_request_line(line))
	{
		while (std::getline(stream, line))
		{
			// strip '\r' first, only then can we see the empty line
			if (!line.empty() && line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);
			if (line.empty())
				break;					// end of headers, the next is body

			size_t colon = line.find(':');
			if (colon == std::string::npos)
			{
				_status = 400;
				break;
			}

			std::string name	= toLower(trim(line.substr(0, colon)));
			std::string value	= trim(line.substr(colon + 1));
			_headers[name] = value;
		}
	}
}

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
	if (_state == PARSE_COMPLETE) { return true; }
	return false;
}

void HttpRequest::save_recv(const char* in, size_t n_bytes)
{
	const size_t MAX_LINE_SIZE = 2048;

	_in.append(in, n_bytes);
	
	while (_state == PARSE_REQUEST_LINE || _state == PARSE_HEADERS)
	{
		size_t newlinePos = _in.find('\n');

		if (newlinePos == std::string::npos)
		{
			if (_in.length() > MAX_LINE_SIZE)
			{
				if (_state == PARSE_REQUEST_LINE)
				{
					_status = 414;
				}
				else
				{
					_status = 400;  // or 431 only for headers
				}
				_state = PARSE_COMPLETE;
				return;
			}
			break;
		} // line not "closed" keep going
		else
		{
			if (newlinePos > MAX_LINE_SIZE)
			{
				if (_state == PARSE_REQUEST_LINE)
				{
					_status = 414;
				}
				else
				{
					_status = 400;  // or 431 only for headers
				}
				_state = PARSE_COMPLETE;
				return;
			}
		}
		

		// if we have full line take it and parse it
		std::string line = _in.substr(0, newlinePos);
		// strip '\r' first, only then can we see the empty line
		if (!line.empty() && line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);
		_in.erase(0, newlinePos + 1);
	
		if (_state == PARSE_REQUEST_LINE) {
			if (!parse_request_line(line)) {
				// first line error
				_state = PARSE_COMPLETE;
				return; // return is proper??
			}
			_state = PARSE_HEADERS;   // first line done so go to headers
		}
		else if (_state == PARSE_HEADERS) {
			// strip '\r' first, only then can we see the empty line
			// if (!line.empty() && line[line.size() - 1] == '\r')
			// 	line.erase(line.size() - 1);
			if (line.empty())
			{
				_state = PARSE_COMPLETE;
				break;					// end of headers, the next is body later
			}

			size_t colon = line.find(':');
			if (colon == std::string::npos)
			{
				_status = 400;
				_state = PARSE_COMPLETE;
				break;
			}

			std::string name	= toLower(trim(line.substr(0, colon)));
			std::string value	= trim(line.substr(colon + 1));
			_headers[name] = value;
		}
	}
}