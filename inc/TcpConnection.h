 ///
 /// @file    TcpConnection.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 15:17:00
 ///

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include "Inetaddress.h"

#include <memory>
#include <functional>  

using std::shared_ptr;
using std::string;

class TcpConnection;
typedef shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void(const TcpConnectionPtr&)> TcpConnectionCallback;

class TcpConnection:private Noncopyable,public std::enable_shared_from_this<TcpConnection>
{
public:
	explicit TcpConnection(int socket);
	~TcpConnection();

	void shutdown();

	ssize_t readn(char* buf, size_t cnt);
	ssize_t writen(const char* buf, size_t cnt);
	ssize_t readline(char* usrbuf, size_t maxlen);
	string recv();
	void send(const string &msg);

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	const Inetaddress & getLocalAdd();
	const Inetaddress & getPeerAdd();

	string toString();

private:
	Socket _socketFd;
	SocketIO _socketIO;
	const Inetaddress _localAdd;
	const Inetaddress _peerAdd;
	bool _isShutdownWrite;
	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};

#endif
