 ///
 /// @file    WorkTask.cc
 /// @author  AkiraMo(motongying941@gmail.com)
 /// @date    2017-03-27 11:10:03
 ///

#include "../inc/WorkTask.h"
#include "../inc/Dict.h"

#include <string.h>

#include  <algorithm>
#include <iostream>
using std::cout;
using std::endl;

WorkTask::WorkTask(const string& word, const TcpConnectionPtr connt, Dict& dict)
:_sQueryWord(word), _connt(connt), _dict(dict)
{
}

void WorkTask::execute()
{
	queryIndex();
	response();
}

void WorkTask::queryIndex()
{
	set<int> setResult;
	myindex tmp = _dict.get_index();
	string chr;
	int i;
	for(i = 0; i < _sQueryWord[i]; ++i)
	{
		chr = _sQueryWord[i];
		for(auto &elem : tmp[chr])
		{
			setResult.insert(elem);
		}
	}

	statistic(setResult);
}

void WorkTask::statistic(set<int> &ist)
{
	Result result;
	::memset(&result, 0, sizeof(result));
	dict tmp = _dict.get_dict();
	for(auto &elem : ist)
	{
		result._sWord = tmp[elem].first;
		result._iFreq = tmp[elem].second;
		result._iDist = distance(result._sWord);
		_queResult.push(result);
	}
}

int min(const int &a, const int &b, const int &c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int WorkTask::distance(const string &word)
{
	int s = word.size();
	int t = _sQueryWord.size();

	int arr[t][s];

	int i;
	for(i = 1; i <= t; ++i)
	{
		arr[i - 1][0] = i;
	}
	for(i = 1; i <= s; ++i)
	{
		arr[0][i - 1] = i;
	}

	int j;
	string tch,sch;
	for(i = 1; i <= t; ++i)
	{
		tch = _sQueryWord[i];
		for(j = 1; j <= s; ++j)
		{
			sch = word[j];
			if(tch == sch)
			{
				arr[i][j] = arr[i - 1][j - 1];
			}
			else
			{
				arr[i][j] = min(arr[i - 1][j - 1] + 1,
								arr[i - 1][j] + 1,
								arr[i][j - 1] + 1);
			}
		}
	}
	return arr[t][s];
}

void WorkTask::response()
{
	string res;
	string en = "\n";
	int i;
	if(_queResult.empty())
	{
		res = "No result\n";
	}
	else
	{
		for(i = 0; i < 10; ++i)
		{
			res += (_queResult.top()._sWord + en);
			_queResult.pop();
		}
	}
	_connt->sendInLoop(res);
}
