 ///
 /// @file    Mutex.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-25 14:37:46
 ///

#include "../inc/Mutex.h"

Mutex::Mutex():_isLock(false)
{
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

void Mutex::lock()
{
	_isLock = true;
	pthread_mutex_lock(&_mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLock = false;
}

pthread_mutex_t* Mutex::getMutexPtr()
{
	return &_mutex;
}

MutexGuard::MutexGuard(Mutex &mutex):_mutex(mutex)
{
	_mutex.lock();
}

MutexGuard::~MutexGuard()
{
	_mutex.unlock();
}
