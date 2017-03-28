 ///
 /// @file    EpollPoller.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 20:19:32
 ///

#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "TcpConnection.h"
#include "Noncopyable.h"

#include <vector>
#include <map>

#include <sys/epoll.h>

typedef TcpConnectionCallback EpollCallback;

class EpollPoller:private Noncopyable
{
public:
	explicit EpollPoller(int listenfd);
	~EpollPoller();

	void loop();
	void unloop();

	void setConnectCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);

private:
	void waitEpollFd();
	void handleConnection();
	void handleMessage(int peerfd);

private:
	const int _epollFd;
	const int _listenFd;
	bool _isLoop;

	typedef std::vector<struct epoll_event> EventList;
	EventList _vecEvents;

	typedef std::map<int, TcpConnectionPtr> ConnectionList;
	ConnectionList _mapLists;

	EpollCallback _onConnectCallback;
	EpollCallback _onMessageCallback;
	EpollCallback _onCloseCallback;
};

#endif
