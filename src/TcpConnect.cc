 ///
 /// @file    TcpConnect.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 15:54:08
 ///

#include "../inc/TcpConnection.h"
#include "../inc/Socket.h"
#include "../inc/SocketIO.h"
#include "../inc/Inetaddress.h"
#include "../inc/Mylog.h"

#include <iostream>

#define BUFFSIZE 1024

using std::cout;
using std::endl;

TcpConnection::TcpConnection(int socket)
:_socketFd(socket), _socketIO(socket), _localAdd(Socket::getLocalAdd(socket)), _peerAdd(Socket::getPeerAdd(socket)), _isShutdownWrite(false){}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
	{
		shutdown();
	}
}

void TcpConnection::shutdown()
{
	_socketFd.shutdownWrite();
	_isShutdownWrite = true;
}

ssize_t TcpConnection::readn(char* buf, size_t cnt)
{
	ssize_t ret = _socketIO.readn(buf, cnt);
	if(-1 == ret)
	{
		logError("TcpConnection readn");
		exit(0);
	}
	return ret;
}

ssize_t TcpConnection::writen(const char* buf, size_t cnt)
{
	ssize_t ret = _socketIO.writen(buf, cnt);
	if(-1 == ret)
	{
		logError("TcpConnection writen");
		exit(0);
	}
	return ret;
}

ssize_t TcpConnection::readline(char* usrbuf, size_t maxlen)
{
	ssize_t ret = _socketIO.readline(usrbuf, maxlen);
	if(-1 == ret)
	{
		logError("TcpConnection readline");
		exit(0);
	}
	return ret;
}

string TcpConnection::recv()
{
	char buf[BUFFSIZE] = {0};
	int ret = readline(buf, sizeof(buf));
	if(0 == ret)
	{
		return std::string();
	}
	else
	{
		return std::string(buf);
	}
}

void TcpConnection::send(const string &msg)
{
	writen(msg.c_str(), msg.size());
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb = std::move(cb);
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb = std::move(cb);
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCb = std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnectionCb)
	{
		_onConnectionCb(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessageCb)
	{
		_onMessageCb(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(_onCloseCb)
	{
		_onCloseCb(shared_from_this());
	}
}

const Inetaddress & TcpConnection::getLocalAdd()
{
	return _localAdd;
}

const Inetaddress & TcpConnection::getPeerAdd()
{
	return _peerAdd;
}

string TcpConnection::toString()
{
	char text[100] = {0};
	snprintf(text, sizeof(text),
			"%s:%d->%s:%d",
			_localAdd.toIp().c_str(), _localAdd.toPort(),
			_peerAdd.toIp().c_str(),_peerAdd.toPort());
	return text;
}
