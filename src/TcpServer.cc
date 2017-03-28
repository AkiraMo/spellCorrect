 ///
 /// @file    TcpServer.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 22:17:17
 ///

#include "../inc/TcpServer.h"
#include "../inc/Mylog.h"

#include <iostream>
using std::cout;
using std::endl;

int createSocketFd()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                                 
	if(-1 == fd)
	{   
		logError("socket");
		exit(0);
	}
	return fd;
}

TcpServer::TcpServer(const string &ip, unsigned short port)
:_addr(ip, port), _sockfd(createSocketFd()), _poller(_sockfd.fd())
{
	_sockfd.setReusePort(true);
	_sockfd.setReuseAddress(true);
	_sockfd.setTcpDelay(false);
	_sockfd.setKeepAlive(false);

	_sockfd.bind(_addr);
	_sockfd.listen();
}
