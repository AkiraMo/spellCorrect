 ///
 /// @file    Configuration.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-23 10:32:09
 ///

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Noncopyable.h"

#include <string>
#include <map>

using std::string;
using std::map;

class Configuration:private Noncopyable
{
	public:
	Configuration(const string & filepath);
	map<string,string> & getMapConfig();

	private:
	string _sFilePath;
	map<string,string> _mapConfig;
};

#endif
