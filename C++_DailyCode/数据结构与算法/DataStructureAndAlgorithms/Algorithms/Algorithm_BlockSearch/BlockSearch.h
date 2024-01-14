#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*索引表中存储的数据格式			**/
typedef struct DATA_TYPE_INDEX
{
	int		iVal;					// 元素关键信息
	int		iIndex;					// 元素索引

	DATA_TYPE_INDEX(int val, int idx)
	{
		iVal = val;
		iIndex = idx;
	}

}Index_dt;

/*分块查找							**/
void funcCallBlockSort();
int funcBlockSort(const vector<int>& vec, const vector<Index_dt>& idxVec, int keyVal);