 ///
 /// @file    SocketIO.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 13:49:20
 ///

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <sys/types.h>

class SocketIO
{
public:
	explicit SocketIO(int socketfd);
	
	ssize_t readn(char* buf, size_t cnt);
	ssize_t writen(const char* buf, size_t cnt);
	ssize_t readline(char* usrbuf, size_t maxlen);

private:
	ssize_t recvpeek(char* buf, size_t len);

	const int _socketFd;

};

#endif
