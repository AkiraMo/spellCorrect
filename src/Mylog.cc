 ///
 /// @file    Mylog.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-02-23 16:00:27
 ///

#include "../inc/Mylog.h"
#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;
using namespace log4cpp;
Mylog::Mylog()
	:_cat(Category::getRoot().getInstance("cat"))
{
	PatternLayout* ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d:%c %p %x:%m%n");
	PatternLayout* ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d:%c %p %x:%m%n");

	OstreamAppender* osApp = new OstreamAppender("osApp",&cout);
	osApp->setLayout(ptn1);

	FileAppender* fileApp = new FileAppender("fileApp","log.log");
	fileApp->setLayout(ptn2);

	_cat.addAppender(osApp);
	_cat.addAppender(fileApp);

	_cat.setPriority(Priority::DEBUG);
}

Mylog::~Mylog()
{
}

Mylog* Mylog::_pInstance = NULL;

Mylog* Mylog::getInstance()
{
	if(_pInstance == NULL)
	{
		_pInstance = new Mylog;
	}
	return _pInstance;
}

void Mylog::destory()
{
	if(_pInstance)
	{
		Category::shutdown();
		delete _pInstance;
	}
}

void Mylog::error(const string &msg)
{
	_cat.error(msg.c_str());
}

void Mylog::warn(const string &msg)
{
	_cat.warn(msg.c_str());
}

void Mylog::info(const string &msg)
{
	_cat.info(msg.c_str());
}

void Mylog::debug(const string &msg)
{
	_cat.debug(msg.c_str());
}

