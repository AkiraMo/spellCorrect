 ///
 /// @file    main.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-24 22:01:48
 ///
#include "../inc/SpellCorrectServer.h"
#include "../inc/Mylog.h"
#include "../inc/WorkTask.h"

#include <iostream>
#include <string>

#define CONFIGPATH "../conf/config"
#define THREADSIZE 2
#define BUFFSIZE 20

using std::cout;
using std::endl;
using std::string;

int main()
{
	SpellCorrectServer server(CONFIGPATH, THREADSIZE, BUFFSIZE);
	server.start();
}
