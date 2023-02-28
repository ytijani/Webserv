#include "Webserver.class.hpp"

Webserver::Webserver( void ) : _serverBlocks(), _pendingClients(), _listeningSockets(),\
	_fds(NULL) { }

Webserver::Webserver( std::list < Blocks > &rhs ) : _serverBlocks(rhs), _pendingClients(),\
	_listeningSockets(), _fds(NULL) { }

Webserver::Webserver( const Webserver &rhs ) : _serverBlocks(rhs._serverBlocks), \
	_pendingClients(rhs._pendingClients), _listeningSockets(rhs._listeningSockets), \
	_fds(rhs._fds) { }

Webserver::~Webserver( void ) { }

void Webserver::setServerBlocks( std::list < Blocks > list )
{
	this->_serverBlocks = list;
}

void Webserver::createSockets( void )
{
	std::list< Blocks >::iterator b;
	sockaddr_in *socketNeeds;
	int sock;
	int tmp;

	sock = 0;
	tmp = 1;
	// Need to delete socketNeeds in case of a fail + Change the exceptions
	for (b = this->_serverBlocks.begin(); b != this->_serverBlocks.end(); b++)
	{
		socketNeeds = new sockaddr_in;
		memset(socketNeeds, 0, sizeof(sockaddr_in)); // Should not forget to change memset (not allowed)
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock == -1)
			throw "Socket function failed";
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) == -1)
			throw "Setsockopt function failed";
		socketNeeds->sin_port = htons(b->port);
		socketNeeds->sin_family = PF_INET;
		socketNeeds->sin_addr.s_addr = b->ip;
		if (bind(sock, (struct sockaddr *)socketNeeds, sizeof(sockaddr_in)) == -1)
			throw "Bind function failed";
		if (listen(sock, 0) == -1)
			throw "Listen function failed";
		this->_listeningSockets.push_back(sock);
		delete socketNeeds;
	}
}

// bool Webserver::_parseRequest( std::list< clients * >::iterator client )
// {
// 	std::string req((*client)->request);
// 	int index1, index2;

// 	index1 = 0;
// 	if (!(*client)->parsedRequest.isRequestLineParsed() && req.find("\r\n") >= 0)
// 	{
// 		index1 = req.find(" ", 0);
// 		(*client)->parsedRequest.setMethod(req.substr(0, index1));
// 		if (!(*client)->parsedRequest.isSupported())
// 		{
// 			// send405(client);
// 			return (false);
// 		}
// 		index2 = req.find(" ", index1 + 1);
// 		(*client)->parsedRequest.setUri(req.substr(index1 + 1, index2 - index1 - 1));
// 		if (!(*client)->parsedRequest.hasGoodSize())
// 		{
// 			// send414(client);
// 			return (false);
// 		}
// 		else if (!(*client)->parsedRequest.hasAllowedChars())
// 		{
// 			// send400((*client));
// 			return (false);
// 		}
// 		index1 = req.find("\r\n", index2 + 1);
// 		(*client)->parsedRequest.setVersion(req.substr(index2 + 1, index1 - index2 - 1));
// 		if (!(*client)->parsedRequest.isGoodVersion())
// 		{
// 			// send505(client);
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// void Webserver::send405( std::list< clients >::iterator client )
// {
// 	send(client->fd, "HTTP/1.1 405 Method Not Allowed\r\n\r\n<h1>This method is not allowed !</h1>", 73, 0);
// 	close(client->fd);
// 	this->_pendingClients.erase(client);
// }

// void Webserver::send414( std::list< clients >::iterator client )
// {
// 	send(client->fd, "HTTP/1.1 414 Request-URI too long\r\n\r\n<h1>The request uri is too long !</h1>", 76, 0);
// 	close(client->fd);
// 	this->_pendingClients.erase(client);
// }

// void Webserver::send400( std::list< clients >::iterator client )
// {
// 	send(client->fd, "HTTP/1.1 400 Bad Request\r\n\r\n<h1>Bad Request !</h1>", 51, 0);
// 	close(client->fd);
// 	this->_pendingClients.erase(client);
// }

// void Webserver::send505( std::list< clients >::iterator client )
// {
// 	send(client->fd, "HTTP/1.1 501 Http Version Not Supported\r\n\r\n<h1>Http Version Not Supported !</h1>", 81, 0);
// 	close(client->fd);
// 	this->_pendingClients.erase(client);
// }