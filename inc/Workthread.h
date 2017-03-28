 ///
 /// @file    Workthread.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 22:47:02
 ///

#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include "Thread.h"
#include "Noncopyable.h"

class Threadpool;

class Workthread:public Thread
{
public:
	Workthread(Threadpool &threadpool);

	void run();

private:
	Threadpool &_threadpool;
};


#endif
