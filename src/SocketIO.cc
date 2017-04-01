 ///
 /// @file    SocketIO.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 14:44:56
 ///

#include "../inc/SocketIO.h"
#include "../inc/Mylog.h"

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#include <iostream>
using std::cout;
using std::endl;

SocketIO::SocketIO(int socketfd):_socketFd(socketfd){}
        
ssize_t SocketIO::readn(char* buf, size_t cnt)
{
	char* pBuf = buf;
	size_t total = 0;
	int pos;
	while(total < cnt)
	{
		pos = ::recv(_socketFd, pBuf + total, cnt - total, 0);
		if(-1 == pos)
		{
			if(EINTR == errno)
			{
				continue;
			}
			return -1;
		}
		else if(0 == pos)
		{
			break;
		}
		total += pos;
	}
	return total;
}

ssize_t SocketIO::writen(const char* buf, size_t cnt)
{
	const char* pBuf = buf;
	size_t total = 0;
	int pos;
	while(total < cnt)
	{
		pos = ::send(_socketFd, pBuf + total, cnt - total, 0);
		if(pos <= 0)
		{
			if(-1 == pos && EINTR == errno)
			{
				continue;
			}
			return -1;
		}
		total += pos;
	}
	return total -= pos;
}

ssize_t SocketIO::readline(char* usrbuf, size_t maxlen)
{
	size_t nleft = maxlen - 1;
	char* pBuf = usrbuf;
	size_t total = 0;
	ssize_t nread;

	while(nleft > 0)
	{
		nread = recvpeek(pBuf, nleft);
		if(nread <= 0)
		{
			return nread;
		}

		int i;
		for(i = 0; i < nread; ++i)
		{
			if('\n' == pBuf[i])
			{
				size_t nsize = i + 1;
				if(readn(pBuf, nsize) != static_cast<ssize_t>(nsize))
				{
					return -1;
				}
				pBuf += nsize;
				total += nsize;
				//*pBuf = 0;
				memset(pBuf, 0, sizeof(pBuf));
				return total;
			}
		}

		if(readn(pBuf, nread) != nread)
		{
			return -1;
		}
		pBuf += nread;
		total += nread;
		nleft -= nread;
	}
	//*pBuf = 0;
	memset(pBuf, 0, sizeof(pBuf));
	return maxlen - 1;
}

ssize_t SocketIO::recvpeek(char* buf, size_t len)
{
	int nread;
	do
	{
		nread = ::recv(_socketFd, buf, len, MSG_PEEK);
	}
	while(-1 == nread && EINTR == errno);
	return nread;
}
