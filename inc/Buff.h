 ///
 /// @file    Buff.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 21:56:57
 ///

#ifndef __BUFF_H__
#define __BUFF_H__

#include "../inc/Mutex.h"
#include "../inc/Condition.h"

#include <queue>

class Task;
typedef Task* ElemType;

class Buff
{
public:
	Buff(size_t size);

	void push(ElemType task);
	ElemType pop();

	void wakeup();

	bool full();
	bool empty();

private:
	Mutex _mutex;
	Condition _notEmpty;
	Condition _notFull;
	size_t _size;
	std::queue<ElemType> _que;
	bool _isRun;
};


#endif
