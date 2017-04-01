 ///
 /// @file    Dict.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-24 16:06:53
 ///

#ifndef __DICT_H__
#define __DICT_H__

#include <map>
#include <vector>
#include <set>
#include <utility>

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::set;

typedef vector<pair<string, int> > dict;
typedef map<string, set<int> > myindex;

class Dict
{
public:
	dict &get_dict();
	myindex &get_index();
//	Dict(const string &dictEnPath, const string &dictCnPath);

	static Dict* getDict(const string& dictEnPath, const string& dictCnPath);
private:
	myindex _mapIndex;
	dict _vecDict;

	Dict(const string &dictEnPath, const string &dictCnPath);

	void init(const string &dictEnPath, const string &dictCnPath);
	void store_index();

	static Dict* _pDict;
};

#endif

