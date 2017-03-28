 ///
 /// @file    EpollPoller.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 20:36:34
 ///

#include "../inc/EpollPoller.h"
#include "../inc/Mylog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>                                                                           
#include <assert.h>

#include <iostream>

using std::cout;
using std::endl;

int creatEpollFd()
{
	int epollfd = ::epoll_create1(0);
	if(-1 == epollfd)
	{
		logError("creatEpollFd");
		exit(0);
	}
	return epollfd;
}

void addEpollReadFd(int epollfd, int fd)
{
	struct epoll_event eve;
	eve.data.fd = fd;
	eve.events = EPOLLIN;
	int ret;
	ret = ::epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &eve);
	if(-1 == ret)
	{
		logError("addEpollReadFd");
		exit(0);
	}
}

void delEpollReadFd(int epollfd, int fd)
{
	struct epoll_event eve;
	eve.data.fd = fd;
	int ret;
	ret = ::epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &eve);
	if(-1 == ret)
	{
		logError("delEpollReadFd");
		exit(0);
	}
}

int accpetConnFd(int listenfd)
{
	int peerfd = ::accept(listenfd, NULL, NULL);
	if(-1 == peerfd)
	{
		logError("accpetConnFd");
		exit(0);
	}
	return peerfd;
}

ssize_t recvPeek(int sockfd, void* buf, size_t len)
{
	int nread;
	do
	{
		nread = ::recv(sockfd, buf, len, MSG_PEEK);
	}
	while(-1 == nread && EINTR == errno);

	return nread;
}

bool isConnectionClose(int sockfd)
{
	char buf[1024];
	ssize_t nread = recvPeek(sockfd, buf, sizeof(buf));
	if(-1 == nread)
	{
		logError("isConnectionClose");
		exit(0);
	}

	return nread == 0;
}

EpollPoller::EpollPoller(int listenfd)
:_epollFd(creatEpollFd()), _listenFd(listenfd), _isLoop(false), _vecEvents(1024)
{
	addEpollReadFd(_epollFd, _listenFd);
}

EpollPoller::~EpollPoller()
{
	::close(_epollFd);
}

void EpollPoller::loop()
{
	_isLoop = true;

	while(_isLoop)
	{
		waitEpollFd();
	}

	logInfo("loop quit");
}

void EpollPoller::unloop()
{
	_isLoop = false;
}

void EpollPoller::setConnectCallback(EpollCallback cb)
{
	_onConnectCallback = std::move(cb);
}

void EpollPoller::setMessageCallback(EpollCallback cb)
{
	_onMessageCallback = std::move(cb);
}

void EpollPoller::setCloseCallback(EpollCallback cb)
{
	_onCloseCallback = std::move(cb);
}

void EpollPoller::waitEpollFd()
{
	int nready;
	do
	{
		nready = ::epoll_wait(_epollFd, &(*_vecEvents.begin()), static_cast<int>(_vecEvents.size()), 5000);
	}
	while(-1 == nready && EINTR == errno);

	if(-1 == nready)
	{
		logError("waitEpollFd");
		exit(0);
	}
	else if (nready == 0)
	{
		logInfo("epoll timeout");
	}
	else
	{
		if(nready == static_cast<int>(_vecEvents.size()))
		{
			_vecEvents.resize(_vecEvents.size() * 2);
		}

		int i;
		for(i = 0; i != nready; ++i)
		{
			if(_vecEvents[i].data.fd == _listenFd)
			{
				if(_vecEvents[i].events & EPOLLIN)
				{
					handleConnection();
				}
			}
			else
			{
				if(_vecEvents[i].events & EPOLLIN)
				{
					handleMessage(_vecEvents[i].data.fd);
				}
			}
		}
	}
}

void EpollPoller::handleConnection()
{
	int peerfd = accpetConnFd(_listenFd);
	addEpollReadFd(_epollFd, peerfd);

	TcpConnectionPtr conn(new TcpConnection(peerfd));
	conn->setConnectionCallback(_onConnectCallback);
	conn->setMessageCallback(_onMessageCallback);
	conn->setCloseCallback(_onCloseCallback);

	_mapLists.insert(std::make_pair(peerfd, conn));

	conn->handleConnectionCallback();
}

void EpollPoller::handleMessage(int peerfd)
{
	bool isClosed = isConnectionClose(peerfd);
	ConnectionList::iterator it = _mapLists.find(peerfd);
	if(it != _mapLists.end())
	{
		if(isClosed)
		{
			it->second->handleCloseCallback();
			delEpollReadFd(_epollFd, peerfd);
			_mapLists.erase(it);
		}
		else
		{
			it->second->handleMessageCallback();
		}
	}
}
