 ///
 /// @file    EpollPoller.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 20:19:32
 ///

#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "TcpConnection.h"
#include "Noncopyable.h"
#include "Mutex.h"

#include <vector>
#include <map>

#include <sys/epoll.h>

using std::string;

typedef TcpConnectionCallback EpollCallback;
typedef std::function<void()> Function;

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

	void runInLoop(Function cb);

private:
	void waitEpollFd();
	void handleConnection();
	void handleMessage(int peerfd);
	void handleRead();
	void wakeup();
	void doPendingFunc();

private:
	const int _epollFd;
	const int _listenFd;
	const int _eventFd;
	bool _isLoop;

	typedef std::vector<struct epoll_event> EventList;
	EventList _vecEvents;

	typedef std::map<int, TcpConnectionPtr> ConnectionList;
	ConnectionList _mapLists;

	Mutex _mutex;
	std::vector<Function> _pendingFunc;

	EpollCallback _onConnectCallback;
	EpollCallback _onMessageCallback;
	EpollCallback _onCloseCallback;
};

#endif
