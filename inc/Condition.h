 ///
 /// @file    Condition.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 21:38:26
 ///

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "../inc/Noncopyable.h"

#include <pthread.h>

class Mutex;
class Condition:private Noncopyable
{
public:
	Condition(Mutex &mutex);
	~Condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t _cond;
	Mutex &_mutex;
};

#endif

