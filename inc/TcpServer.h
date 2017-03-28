 ///
 /// @file    TcpServer.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 22:12:03
 ///

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Noncopyable.h"
#include "EpollPoller.h"
#include "Socket.h"
#include "Inetaddress.h"

#include <string>

using std::string;

typedef EpollCallback TcpServerCallback;

class TcpServer:private Noncopyable
{
public:
	TcpServer(const string &ip, unsigned short port);

	void start();

	void setConnectCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	Inetaddress _addr;
	Socket _sockfd;
	EpollPoller _poller;
};

#endif
