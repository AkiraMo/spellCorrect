 ///
 /// @file    Inetaddress.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 09:38:32
 ///

#include "../inc/Inetaddress.h"
#include "../inc/Mylog.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Inetaddress::Inetaddress(uint16_t port)
{
	::memset(&_add,0,sizeof(_add));
	_add.sin_family = AF_INET;
	_add.sin_addr.s_addr = INADDR_ANY;
	_add.sin_port = htons(port);
}

Inetaddress::Inetaddress(const std::string &ip, uint16_t port)
{
	::memset(&_add,0,sizeof(_add));
	_add.sin_family = AF_INET;
	_add.sin_port = htons(port);
	int ret;
	ret = inet_aton(ip.c_str(), &_add.sin_addr);
	if(ret ==  0)
	{
		logError("ip");
		exit(0);
	}
}

Inetaddress::Inetaddress(const struct sockaddr_in &add):_add(add){}
		                                                                                             
void Inetaddress::setSockAddrInet(const struct sockaddr_in &add)
{
	_add = add;
}

const struct sockaddr_in* Inetaddress::getSockAddrInet() const
{
	return &_add;
}

std::string Inetaddress::toIp() const
{
	return inet_ntoa(_add.sin_addr);
}
uint16_t Inetaddress::toPort() const
{
	return ntohs(_add.sin_port);
}


