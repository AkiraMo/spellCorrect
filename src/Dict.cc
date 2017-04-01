 ///
 /// @file    Dict.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-24 20:12:22
 ///

#include "../inc/Dict.h"
#include "../inc/Mylog.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

Dict* Dict::_pDict = NULL;

Dict* Dict::getDict(const string& dictEnPath, const string& dictCnPath)
{
	if(!_pDict)
	{
		_pDict = new Dict(dictEnPath, dictCnPath);
	}
	return _pDict;
}

Dict::Dict(const string &dictEnPath, const string &dictCnPath)
{
	init(dictEnPath,dictCnPath);
	store_index();
}

dict &Dict::get_dict()
{
	return _vecDict;
}

myindex &Dict::get_index()
{
	return _mapIndex;
}

void Dict::init(const string &dictEnPath, const string &dictCnPath)
{
	//生成dict
	string cntmp = dictCnPath;//报错太烦了，先写着，八百年以后再写真的处理吧
	ifstream ifse(dictEnPath);
	if(!ifse.good())
	{
		logError("ifse");
		exit(0);
	}

	string line, word, tmp;
	int freq;

	while(getline(ifse,line))
	{
		istringstream isse(line);	
		isse >> word >> tmp;
		freq = atoi(tmp.c_str());
		_vecDict.push_back(std::make_pair(word,freq));
	}
	ifse.close();

	//生成index
	char a = 'a';
	int pos = 0, i;
	string cur;

	for(; a != 'z' + 1; ++a)
	{
		tmp = a;
		set<int> settmp;
		_mapIndex.insert(std::make_pair(tmp,settmp));
		a -= 32;
		tmp = a;
		_mapIndex.insert(std::make_pair(tmp,settmp));
		a += 32;
	}

	dict::iterator itVecEn = _vecDict.begin();
	for(; itVecEn != _vecDict.end(); ++itVecEn, ++pos)
	{
		tmp = itVecEn->first;
		for(i = 0; i <= (int)tmp.size(); ++i)
		{
			cur = tmp[i];
			myindex::iterator itMapEn = _mapIndex.find(cur);
			if(itMapEn != _mapIndex.end())
			{
				itMapEn->second.insert(pos);
			}
		}
	}
}

void Dict::store_index()
{
	std::ofstream ofs("../data/index");

	for(auto &elem : get_index())
	{
		ofs << elem.first << " ";
		for(auto &setelem : elem.second)
		{
			ofs << setelem << ",";
		}
		ofs << endl;
	}
}
