 ///
 /// @file    WorkTask.h
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 11:10:17
 ///

#ifndef __WORKTASK_H__
#define __WORKTASK_H__

#include "Task.h"
#include "TcpConnection.h"

#include <string>
#include <queue>
#include <vector>
#include <set>

using std::set;
using std::string;
using std::priority_queue;
using std::vector;

class Dict;

struct Result
{
	string _sWord;
	int _iDist;
	int _iFreq;
};

struct compare
{
	bool operator()(const Result &lhs, const Result &rhs)
	{
		if(lhs._iDist > rhs._iDist)
		{
			return true;
		}
		else if(lhs._iDist == rhs._iDist && lhs._iFreq > rhs._iFreq)
		{
			return true;
		}
		else if(lhs._iDist == rhs._iDist && lhs._iFreq == rhs._iFreq && lhs._sWord > rhs._sWord)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class WorkTask:public Task
{
public:
	WorkTask(const string& word, const TcpConnectionPtr connt, Dict& dict);
	void execute();

private:
	void queryIndex();
	void statistic(set<int> &ist);
	int distance(const string &rhs);

	void response();

private:
	string _sQueryWord;
	TcpConnectionPtr _connt;
	Dict &_dict;
	priority_queue<Result, vector<Result>, compare> _queResult;
};

#endif
