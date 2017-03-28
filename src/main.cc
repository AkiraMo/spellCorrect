 ///
 /// @file    main.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-24 22:01:48
 ///
 
#include "../inc/Configuration.h"
#include "../inc/Dict.h"
#include "../inc/DictProducer.h"


#include <iostream>

#define CONFIGPATH "../conf/config"

using std::cout;
using std::endl;

string find_config(Configuration & config, const string & key)
{
	map<string,string> mapConfig  = config.getMapConfig();
	map<string,string>::iterator itMapConfigFind = mapConfig.find(key);
	string tmp;
	if(itMapConfigFind != mapConfig.end())
	{
		tmp = itMapConfigFind->second;
	}	
	return tmp;
}

int main()
{
	string configpath = CONFIGPATH;
	Configuration config(configpath);

	DictProducer dictmaker(find_config(config,"yuliao"));

	dictmaker.get_files();
	string dictpath = find_config(config,"dict");
	dictmaker.store_dict(dictpath);

	Dict dict(dictpath,"");
	
}
