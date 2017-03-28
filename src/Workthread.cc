 ///
 /// @file    Workthread.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-26 23:11:27
 ///

#include "../inc/Workthread.h"
#include "../inc/Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;

Workthread::Workthread(Threadpool &threadpool):_threadpool(threadpool){}

void Workthread::run()
{
	_threadpool.processTask();
}
