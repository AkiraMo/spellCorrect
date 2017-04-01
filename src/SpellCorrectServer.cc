 //
 /// @file    SpellCorrectServer.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-30 23:10:28
 ///

#include "../inc/SpellCorrectServer.h"
#include "../inc/DictProducer.h"
#include "../inc/WorkTask.h"
#include "../inc/Mylog.h"


#include <iostream>
#include <map>
#include <functional>

using std::map;
using std::cout;
using std::endl;
using std::ref;
using std::placeholders::_2;
using std::bind;

SpellCorrectServer* SpellCorrectServer::_p = NULL;

SpellCorrectServer::SpellCorrectServer(const string &configpath, size_t threadsize, size_t buffsize)
:_conf(configpath), _threadpool(std::make_shared<Threadpool>(threadsize, buffsize))
{
	map<string, string> mapConfig = _conf.getMapConfig();
	DictProducer dictmaker(mapConfig["yuliao"]);
	dictmaker.get_files();

	string dictenpath = mapConfig["dicten"];
	dictmaker.store_dict(dictenpath);
	_dict = Dict::getDict(dictenpath, "");

	string ip = mapConfig["IP"];
	unsigned short port = 8000;
	_tcpserver = std::make_shared<TcpServer>(ip,port);
	_p = this;
}

void SpellCorrectServer::start()
{
	_tcpserver->setConnectCallback(&SpellCorrectServer::onConnection);
	_tcpserver->setMessageCallback(&SpellCorrectServer::onMessage);
	_tcpserver->setCloseCallback(&SpellCorrectServer::onClose);
	
	_threadpool->start();
	_tcpserver->start();
}

void SpellCorrectServer::onConnection(const TcpConnectionPtr & conn)
{
	logInfo(conn->toString());
}

void SpellCorrectServer::onMessage(const TcpConnectionPtr & conn)
{
	string s(conn->recv());
	ElemType task = new WorkTask(s, conn, *(_p->_dict));
	_p->_threadpool->addTask(task);
}

void SpellCorrectServer::onClose(const TcpConnectionPtr & conn)
{
	string s = "close " + conn->toString();
	logInfo(s);
}

