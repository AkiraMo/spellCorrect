 ///
 /// @file    Configuration.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-23 16:49:05
 ///

#include "../inc/Configuration.h"
#include "../inc/Mylog.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::cout;
using std::endl;
using std::pair;

Configuration::Configuration(const string & filepath):_sFilePath(filepath)
{
	std::ifstream ifs(_sFilePath);
	if(!ifs.good())
	{
		logError("ifstream");
		exit(0);
	}

	string line, key, value;
	while(getline(ifs, line))
	{
		std::istringstream iss(line);
		iss >> key >> value;
		_mapConfig.insert(std::make_pair(key,value));
	}
	ifs.close();
}

map<string,string> & Configuration::getMapConfig()
{
	return _mapConfig;
}
