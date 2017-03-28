 ///
 /// @file    Thread.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-25 18:30:45
 ///

#include "../inc/Thread.h"

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
		_pthId = false;
	}
}

void* Thread::threadFunc(void* arg)
{
	Thread* p = static_cast<Thread*>(arg);
	if(p)
	{
		p->run();
	}
	return NULL;
}

Thread::~Thread()
{
	if(_isRun)
	{
		pthread_detach(_pthId);
	}
}
