#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::vector;
using std::initializer_list;

// BM2 - 数组中出现次数超过一半的数字
class MoreThanHalfNum_Solution
{
public:
	int solve(vector<int>& numbers);
	void demo();
};