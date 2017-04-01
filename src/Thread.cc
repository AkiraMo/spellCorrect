 ///
 /// @file    Thread.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-25 18:30:45
 ///

#include "../inc/Thread.h"

#include <iostream>
using std::cout;
using std::endl;

Thread::Thread():_pthId(0), _isRun(false){}

void Thread::start()
{
	pthread_create(&_pthId, NULL, threadFunc, this);
	_isRun = true;
}

void Thread::join()
{
	if(_isRun)
	{
		pthread_join(_pthId, NULL);
		_isRun = false;
	}
}

void* Thread::threadFunc(void* arg)
{
	Thread* p = static_cast<Thread*>(arg);
	while(true)
	{
		if(p)
		{
			p->run();
		}
	}
	return NULL;
}

Thread::~Thread()
{
	if(!_isRun)
	{
		pthread_detach(_pthId);
	}
}
