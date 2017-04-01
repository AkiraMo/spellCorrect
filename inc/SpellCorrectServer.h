 ///
 /// @file    SpellCorrectServer.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-30 23:03:41
 ///

#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__

#include "Dict.h"
#include "Configuration.h"
#include "Threadpool.h"
#include "TcpServer.h"

#include <memory>

using std::string;
using std::shared_ptr;


class SpellCorrectServer
{
public:
	SpellCorrectServer(const string & configpath, size_t threadsize, size_t buffsize);
	
	void start();

	static void onConnection(const TcpConnectionPtr & conn);
	static void onMessage(const TcpConnectionPtr & conn);
	static void onClose(const TcpConnectionPtr & conn);

private:
	Configuration _conf;
	shared_ptr<Threadpool> _threadpool;
	Dict * _dict;
	shared_ptr<TcpServer> _tcpserver;
	static SpellCorrectServer* _p;

};

#endif
