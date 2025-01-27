#pragma once

#include <iostream>
#include <map>
#include <ctype.h>
#include <utility>

class Request
{
	// Request line components and headers.
	private :
		std::string _method;
		std::string _uri;
		std::string _version;
		std::string _queryStr;
		std::map< std::string, std::string > _headers;

	// Default constructor, copy constructor, copy assignment operator overload, destructor.
	public :
		Request( void );
		Request( const Request &rhs );
		Request &operator=( const Request &rhs );
		~Request( void );

	// Setters
		void setMethod( const std::string &meth );
		void setUri( const std::string &uri );
		void setVersion( const std::string &version );
		void setQueryString( const std::string &qStr );
		void insertHeader( const std::pair< std::string, std::string > &pair );

	// Getters
		const std::string &getMethod( void ) const;
		const std::string &getUri( void ) const;
		const std::string &getVersion( void ) const;
		const std::string &getQueryString( void ) const;
		const std::string &getValueFromMap( const std::string &key );

	// Member functions that check for the validity of the request's components.
		bool isSupported( void ) const;
		bool hasGoodSize( void ) const;
		bool hasAllowedChars( void ) const;
		bool isGoodVersion( void ) const;
		bool isRequestLineParsed( void ) const;
};