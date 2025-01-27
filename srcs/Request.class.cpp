#include "../includes/Request.class.hpp"

Request::Request( void ) { }

Request::Request( const Request &rhs )
{
	*this = rhs;
}

Request &Request::operator=( const Request &rhs )
{
	if (this != &rhs)
	{
		this->_method = rhs._method;
		this->_uri = rhs._uri;
		this->_version = rhs._version;
		this->_queryStr = rhs._queryStr;
		this->_headers = rhs._headers;
	}
	return (*this);
}

Request::~Request( void ) { }

void Request::setMethod( const std::string &meth )
{
	this->_method = meth;
}

void Request::setUri( const std::string &uri )
{
	this->_uri = uri;
}

void Request::setVersion( const std::string &version )
{
	this->_version = version;
}

void Request::setQueryString( const std::string &qString )
{
	this->_queryStr = qString;
}

void Request::insertHeader( const std::pair< std::string, std::string > &pair)
{
	this->_headers.insert(pair);
}

const std::string &Request::getMethod( void ) const
{
	return (this->_method);
}

const std::string &Request::getUri( void ) const
{
	return (this->_uri);
}

const std::string &Request::getVersion( void ) const
{
	return (this->_version);
}

const std::string &Request::getQueryString( void ) const
{
	return (this->_queryStr);
}

const std::string &Request::getValueFromMap( const std::string &key )
{
	return (this->_headers[key]);
}

bool Request::isSupported( void ) const
{
	return (this->_method == "GET" || this->_method == "POST" || this->_method == "DELETE");
}

bool Request::hasGoodSize( void ) const
{
	return (this->_uri.size() <= 2048);
}

bool Request::hasAllowedChars( void ) const
{
	const char *ur = this->_uri.c_str();
	size_t i;

	for (i = 0; i < this->_uri.size(); i++)
		if (!isascii(ur[i]))
			return (false);
	return (true);
}

bool Request::isGoodVersion( void ) const
{
	return (this->_version == "HTTP/1.1");
}

bool Request::isRequestLineParsed( void ) const
{
	return (isSupported() && hasGoodSize() && hasAllowedChars() && isGoodVersion());
}