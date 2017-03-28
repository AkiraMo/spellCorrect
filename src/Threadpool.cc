 ///
 /// @file    Threadpool.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 22:38:23
 ///

#include "../inc/Threadpool.h"
#include "../inc/Workthread.h"
#include "../inc/Task.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

Threadpool::Threadpool(size_t threadsize, size_t buffsize)
:_sizeThread(threadsize), _sizeBuff(buffsize), _buff(_sizeBuff), _isExit(false)
{
	_vecPThreads.reserve(_sizeThread);
}

void Threadpool::start()
{
	int i;
	for(i = 0; i < (int)_sizeThread; ++i)
	{
		Thread* p = new Workthread(*this);
		shared_ptr<Thread> sp(p);
		_vecPThreads.push_back(sp);
		sp->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_buff.empty())
		{
			sleep(1);
		}

		_isExit = true;
		_buff.wakeup();
		for(auto &elem : _vecPThreads)
		{
			elem->join();
		}

		_vecPThreads.clear();
	}
}

void Threadpool::addTask(ElemType task)
{
	_buff.push(task);
}

ElemType Threadpool::getTask()
{
	return _buff.pop();
}

void Threadpool::processTask()
{
	if(!_isExit)
	{
		ElemType task = getTask();
		if(task)
		{
			task->execute();
		}
	}
}
