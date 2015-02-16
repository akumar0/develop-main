// testproj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

typedef std::vector<int> IntVector;
using namespace std;

vector<string>
cheap_tokenize(string const& input)
{
    istringstream str(input);
    istream_iterator<string> cur(str), end;
    return vector<string>(cur, end);
}

void runCheck(IntVector& workVector, int idx, int maxIdx)
{	
	int& val = workVector[idx];

	for (val=1; val <= maxIdx; ++val) {
		if (idx) {
			IntVector::iterator it = std::find(workVector.begin(), workVector.begin()+idx, val);
			if (it != (workVector.begin()+idx))
				continue;
		}
		if (idx == maxIdx-1) {
			int val1 = workVector[0] + workVector[1];
			int val2 = workVector[0] + workVector[2] + workVector[5];
			int val3 = workVector[1] + workVector[4] + workVector[6];
			int val4 = workVector[2] + workVector[3] + workVector[4];
			if ((val1 == val2) && (val2 == val3) && (val3==val4)) {
				std::cout << "Found a solution:\n";
				for (IntVector::iterator it1 = workVector.begin(); it1 != workVector.end(); ++it1) {
					std::cout << *it1 << ", ";
				}
				std::cout << std::endl;
			}
		} else {
			runCheck(workVector, idx+1, maxIdx);
		}
	}
}

void computeCombination()
{
	std::vector<int> workVector(7, 8);
	
	runCheck(workVector, 0, 7);
}

namespace Patterns {
	typedef std::vector<std::vector<int>> AdjList;

	void initAdjList(AdjList& adjList, int patternSize) {
		adjList.resize(patternSize*patternSize);
		for (int i=0; i < patternSize * patternSize; ++i) {
			//TBD
		}

	}

	void countCombinations(int& count, const AdjList& adjList, std::vector<bool> visitedList, int nodeId) {
		if (visitedList[nodeId])
			return;
		++count;
		for (std::vector<int>::const_iterator it = adjList[nodeId].begin(); it != adjList[nodeId].end(); ++it) {
			visitedList[*it] = true;
			countCombinations(count, adjList, visitedList, *it);
			visitedList[*it] = false;
		}
	}

	void countMain() {
		int patternSize = 3;
		AdjList adjList;
		initAdjList(adjList, patternSize);
		std::vector<bool> visitedList(patternSize*patternSize, false);
		int count;
		countCombinations(count, adjList, visitedList, 0);
	}
}

namespace SortVarious
{
void sortMain()
{
	using namespace std;

	std::string line;
	if (std::getline(std::cin, line))
	{
		std::cout << line << std::endl;
	} else {
		return;
	}
    istringstream str(line);
	vector<string> strVals;
	vector<int> intVals;
	vector<bool> valTypeIsString;
	for (istream_iterator<string> cur(str), end;cur != end; ++cur) {
		string val = *cur;
		if (val.empty())
			continue;
		if ((val[0] >= 'a') && (val[0] <= 'z')) {
			strVals.push_back(val);
			valTypeIsString.push_back(true);
		} else if ((val[0] == '-')  || ((val[0] >= '0') && (val[0] <= '9'))) {
			intVals.push_back(atoi(val.c_str()));
			valTypeIsString.push_back(false);
		}
	}

	std::sort(intVals.begin(), intVals.end());
	std::sort(strVals.begin(), strVals.end());

	std::vector<string>::iterator itS = strVals.begin();
	std::vector<int>::iterator itI = intVals.begin();
	for (vector<bool>::const_iterator it=valTypeIsString.begin(), itEnd = valTypeIsString.end();
		it != itEnd; ++it) {
		if (*it) {
			std::cout << *(itS++) << " ";
		} else {
			std::cout << *(itI++) << " ";
		}
	}
	std::getline(std::cin, line);
}
}


namespace Animate {

void formatForOutput(string& str)
{
	for (string::iterator it = str.begin(), itEnd = str.end();
		it != itEnd; ++it) {
			if (*it != '.')
				*it = 'X';
	}
}

bool setValue(int i, string& out, char val)
{
	if ((i <0) || (i >= out.size()))
		return false;
	switch (val) {
	case 'L':
		{
			if (out[i] == 'R')
				out[i] = 'B';
			else
				out[i] = 'L';
		}
		break;
	case 'R':
		{
			if (out[i] == 'L')
				out[i] = 'B';
			else
				out[i] = 'R';
		}
		break;
	}
	return true;
}

bool moveString(string& out, const string& str, int step)
{
	out.clear();
	out.resize(str.size(), '.');
	bool hasValue = false;

	for (std::size_t i=0; i < str.size(); ++i) {
			switch(str[i]) {
			case 'L':
				hasValue = setValue(i-step, out, 'L') || hasValue;
				break;
			case 'R':
				hasValue = setValue(i+step, out, 'R') || hasValue;
				break;
			case 'B':
				hasValue = setValue(i-step, out, 'L')|| hasValue;
				hasValue = setValue(i+step, out, 'R')|| hasValue;
				break;
			default:
				break;
			}
	}
	return hasValue;
}

 vector<string> animate(int speed, const string& init) {
	 vector<string> result;

	string current(init);
	bool hasValue = true;
	for (;hasValue;) {
		result.push_back(string());
		hasValue = moveString(result.back(), current, speed);
		current = result.back();
		formatForOutput(result.back());
	}

	 return result;
 }

void animateAndPrint(int speed, const string& init) {
	vector<string> res = animate(speed, init);
	for (vector<string>::const_iterator it = res.begin(), itEnd = res.end();
		it != itEnd; ++it) {
			cout << *it << std::endl;
	}
	string line;
	std::getline(std::cin, line);
}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//computeCombination();
	//Patterns::countMain();
	//SortVarious::sortMain(');
	//Animate::animateAndPrint(2,  "LRLR.LRLR");
	Animate::animateAndPrint(1,  "LRRL.LR.LRR.R.LRRL.");
	return 0;
}

