 ///
 /// @file    Threadpool.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 22:30:12
 ///

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "../inc/Buff.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Thread;

class Threadpool
{
	friend class Workthread;
public:
	Threadpool(size_t threadsize, size_t buffsize);

	void start();
	void stop();

	void addTask(ElemType task);

private:
	ElemType getTask();
	void processTask();

private:
	size_t _sizeThread;
	size_t _sizeBuff;
	Buff _buff;
	bool _isExit;
	vector<shared_ptr<Thread> > _vecPThreads;	
};


#endif
