 ///
 /// @file    Thread.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-25 18:26:17
 ///

#ifndef __THREAD_H__
#define __THREAD_H__

#include "Noncopyable.h"

#include <pthread.h>

class Thread:private Noncopyable
{
public:
	Thread();
	virtual ~Thread();

	virtual void run() = 0;

	void start();
	void join();

	static void* threadFunc(void* arg);

private:
	pthread_t _pthId;
	bool _isRun;

};

#endif
