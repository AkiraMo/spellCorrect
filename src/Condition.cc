 ///
 /// @file    Condition.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 21:42:12
 ///

#include "../inc/Condition.h"
#include "../inc/Mutex.h"

#include <iostream>
using std::cout;
using std::endl;

Condition::Condition(Mutex &mutex):_mutex(mutex)
{
	pthread_cond_init(&_cond, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
	pthread_cond_wait(&_cond, _mutex.getMutexPtr());
}

void Condition::notify()
{
	pthread_cond_signal(&_cond);
}

void Condition::notifyall()
{
	pthread_cond_broadcast(&_cond);
}
