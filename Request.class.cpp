#include "Request.class.hpp"

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

void Request::insertHeader( const std::pair< std::string, std::string > &pair)
{
	this->_headers.insert(pair);
}

void Request::setBody( const std::string &body )
{
	this->_body = body;
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

	for (int i = 0; i < this->_uri.size(); i++)
		if (!isascii(ur[i]))
			return (false);
	return (true);
}

bool Request::isGoodVersion( void ) const
{
	return (this->_version == "HTTP/1.1");
}