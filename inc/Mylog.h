 ///
 /// @file    Mylog.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-02-22 22:28:53
 ///
#ifndef _MOLOG_H_
#define _MOLOG_H_

#include <iostream>
#include <log4cpp/Category.hh>

using std::cout;
using std::endl;
using std::string;

class Mylog
{
public:
	static Mylog* getInstance();
	static void destory();

	void error(const string &msg);
	void warn(const string &msg);
	void info(const string &msg);
	void debug(const string &msg);

private:
	Mylog();
	~Mylog();
private:
	static Mylog* _pInstance;
	log4cpp::Category &_cat;
};

inline string int_to_string(int num)
{
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

#define postfix(msg)\
	    string(msg).append("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(int_to_string(__LINE__)).append("]")

inline void logError(const string &msg)
{
	Mylog* pLog = Mylog::getInstance();
	pLog->error(msg);
}

inline void logWarn(const string &msg)
{
	Mylog* pLog = Mylog::getInstance();
	pLog->warn(msg);
}

inline void logInfo(const string &msg)
{
	Mylog* pLog = Mylog::getInstance();
	pLog->info(msg);
}

inline void logDebug(const string &msg)
{
	Mylog* pLog = Mylog::getInstance();
	pLog->debug(msg);
}

#define logError(msg) logError(postfix(msg))
#define logWarn(msg) logWarn(postfix(msg))
#define logInfo(msg) logInfo(postfix(msg))
#define logDebug(msg) logDebug(postfix(msg))

#endif
