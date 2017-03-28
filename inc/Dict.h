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
typedef map<string, set<int> > index;

class Dict
{
public:
	Dict(const string &dictEnPath, const string &dictCnPath);

	dict get_dict();
	index get_index();

private:
	index _mapIndex;
	dict _vecDict;

	void init(const string &dictEnPath, const string &dictCnPath);
	void store_index();
};

#endif

