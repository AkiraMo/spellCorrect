 ///
 /// @file    Socket.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 09:59:17
 ///

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "../inc/Noncopyable.h"

class Inetaddress;

class Socket:private Noncopyable
{
public:
	explicit Socket(int socketfd);
	Socket();
	~Socket();

	void ready(const Inetaddress &inetaddress);

	int fd();
	void bind(const Inetaddress &add);
	void listen();
	void accept();
	
	void shutdownWrite();

	void setReuseAddress(bool on);
	void setReusePort(bool on);
	void setTcpDelay(bool on);
	void setKeepAlive(bool on);

	static Inetaddress getLocalAdd(int localfd);
	static Inetaddress getPeerAdd(int peerfd);

private:
	int _socketFd;
};
#endif
