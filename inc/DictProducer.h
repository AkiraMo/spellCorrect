 //
 /// @file    DictProducer.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-23 17:43:41
 ///

#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

class SplitTool;

class DictProducer
{
public:
	DictProducer(const string &dir);
	DictProducer(const string &dir, SplitTool* splittool);

	void get_files();
	void push_dict(const string &word);
	void store_dict(const string &filepath);

private:
	string _sDir;
	vector<string> _vecFile;
	map<string,int> _mapDict;
	SplitTool* _pSplitTool;
	
	void bulid_dict();
	void bulid_cn_dict();
	
	void show_file() const;
	void show_dict() const;
};

#endif
