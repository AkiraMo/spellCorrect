 ///
 /// @file    Buff.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 22:05:12
 ///

#include "../inc/Buff.h"

#include <iostream>
using std::cout;
using std::endl;

Buff::Buff(size_t size):_mutex(), _notEmpty(_mutex), _notFull(_mutex), _size(size), _isRun(true){}

void Buff::push(ElemType task)
{
	MutexGuard tmp(_mutex);
	while(full())
	{
		_notFull.wait();
	}
	_que.push(task);
	_notEmpty.notify();
	_mutex.unlock();
}

ElemType Buff::pop()
{
	MutexGuard tmp(_mutex);
	while(_isRun && empty())
	{
		_notEmpty.wait();
	}
	if(_isRun)
	{
		ElemType ret = _que.front();
		_que.pop();
		_notFull.notify();
		return ret;
	}
	else
	{
		return NULL;
	}
}

void Buff::wakeup()
{
	_isRun = false;
	_notFull.notifyall();
}

bool Buff::full()
{
	return (_que.size() == _size);
}

bool Buff::empty()
{
	return (_que.size() == 0);
}
