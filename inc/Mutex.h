 ///
 /// @file    Mutex.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-25 13:24:51
 ///
 
#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

	pthread_mutex_t* getMutexPtr();
private:
	pthread_mutex_t _mutex;
	bool _isLock;
};

class MutexGuard
{
public:
	MutexGuard(Mutex & mutex);
	~MutexGuard();

private:
	Mutex _mutex;
};

#endif
