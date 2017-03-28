 ///
 /// @file    Socket.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 10:09:15
 ///

#include "../inc/Socket.h"
#include "../inc/Inetaddress.h"
#include "../inc/Mylog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h> 

#include <iostream>
using std::cout;
using std::endl;

Socket::Socket(int socketfd):_socketFd(socketfd){}
	
Socket::Socket()
{
	_socketFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == _socketFd)
	{
		logError("socket");
		exit(0);
	}
}

Socket::~Socket()
{
	::close(_socketFd);
}

void Socket::ready(const Inetaddress &inetaddress)
{
	setReuseAddress(true);
	setReusePort(true);
	bind(inetaddress);
	listen();
}

int Socket::fd()
{
	return _socketFd;
}
void Socket::bind(const Inetaddress &add)
{
	int ret;
	ret = ::bind(_socketFd, (struct sockaddr*)add.getSockAddrInet(), sizeof(add));
	if(-1 == ret)
	{
		logError("bind");
	}
}
void Socket::listen()
{
	int ret;
	ret = ::listen(_socketFd, SOMAXCONN);
	if(-1 == ret)
	{
		logError("listen");
		exit(0);
	}
}
void Socket::accept()
{
	int fd = ::accept(_socketFd, NULL, NULL);
	if(-1 == fd)
	{
		logError("accept");
		exit(0);
	}
}
						    
void Socket::shutdownWrite()
{
	int ret;
	ret = ::shutdown(_socketFd, SHUT_WR);
	if(-1 == ret)
	{
		logError("shutdownWrite");
	}
}

void Socket::setReuseAddress(bool on)
{
	int ret;
	int optval = on ? 1 : 0;
	ret = ::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
	if(-1 == ret)
	{
		logError("setReuseAddress");
		exit(0);
	}
}
void Socket::setReusePort(bool on)
{
#ifdef SO_REUSEPORT
	int ret;
	int optval = on ? 1 : 0;
	ret = ::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));
	if(-1 == ret)
	{
		logError("setReusePort");
		exit(0);
	}
#else
	if(on)
	{
		logError("SO_REUSEPORT");
		exit(0);
	}
#endif
}

Inetaddress Socket::getLocalAdd(int localfd)
{
	struct sockaddr_in add;
	socklen_t len = sizeof(add);
	int ret;
	ret = ::getsockname(localfd, (struct sockaddr*)&add, &len);
	if(-1 == ret)
	{
		logError("getLocalAdd");
		exit(0);
	}
	return Inetaddress(add);
}
Inetaddress Socket::getPeerAdd(int peerfd)
{
	struct sockaddr_in add;
	socklen_t len = sizeof(add);
	int ret;
	ret = ::getsockname(peerfd, (struct sockaddr*)&add, &len);
	if(-1 == ret)
	{
		logError("getLocalAdd");
		exit(0);
	}
	return Inetaddress(add);
}

void Socket::setTcpDelay(bool on)
{
	int ret;
	int optval = on ? 1 : 0;
	ret = ::setsockopt(_socketFd, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof(optval)));
	if(-1 == ret)
	{
		logError("setTcpDelay");
		exit(0);
	}
}

void Socket::setKeepAlive(bool on)
{
	int ret;
	int optval = on ? 1 : 0;
	ret = ::setsockopt(_socketFd, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof(optval)));
	if(-1 == ret)
	{
		logError("setKeepAlive");
		exit(0);
	}
}
