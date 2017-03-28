 /// @file    DictProducer.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-23 22:12:49
 ///
 
#include "../inc/DictProducer.h"
#include "../inc/Mylog.h"

#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::cout;
using std::endl;
using std::ifstream;

DictProducer::DictProducer(const string &dir):_sDir(dir),_pSplitTool(NULL){}
DictProducer::DictProducer(const string &dir, SplitTool* splittool):_sDir(dir),_pSplitTool(splittool){}

void DictProducer::get_files()
{
	DIR* dir;
	dir = opendir(_sDir.c_str());
	if(NULL == dir)
	{
		logError("dir");
		exit(0);
	}
	struct dirent* p;
	string filepath;
	while((p = readdir(dir)) != NULL)
	{
		if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
		{
			continue;
		}
		filepath = _sDir + p->d_name;
		_vecFile.push_back(filepath);
	}
	bulid_dict();
}

void DictProducer::push_dict(const string &word)
{
	map<string,int>::iterator it = _mapDict.find(word);
	if(it != _mapDict.end())
	{
		++(it->second);
	}
	else
	{
		_mapDict.insert(std::make_pair(word,1));
	}
}

void DictProducer::bulid_dict()
{
	for(auto &elem : _vecFile)
	{
		ifstream ifs(elem);
		if(!ifs.good())
		{
			logError("ifs");
			exit(0);
		}
		string line, word;
		while(getline(ifs,line))
		{
			std::istringstream iss(line);
			word.clear();
			while(iss >> word)
			{
				push_dict(word);
			}
		}
		ifs.close();
	}
}

void DictProducer::bulid_cn_dict(){}

void DictProducer::store_dict(const string &filepath)
{
	std::ofstream ofs(filepath);
	if(!ofs.good())
	{
		logError("ofs");
		exit(0);
	}
	for(auto &elem : _mapDict)
	{
		ofs << elem.first << " " << elem.second << endl;
	}
	ofs.close();
}

void DictProducer::show_file() const
{
	for(auto &elem : _vecFile)
	{
		cout << elem << endl;
	}
}
void DictProducer::show_dict() const
{
	for(auto &elem : _mapDict)
	{
		cout << elem.first << " " << elem.second << endl;
	}
}
