#include "HashAlg.h"

int MoreThanHalfNum_Solution::solve(vector<int>& numbers)
{
	unordered_map<int, int> recordMap;
	for (int i = 0; i < numbers.size(); ++i) {
		unordered_map<int, int>::iterator iter = recordMap.find(numbers[i]);
		if (recordMap.end() == iter)
			recordMap.insert(make_pair(numbers[i], 1));
		else {
			if (iter->second >= numbers.size() / 2)
				return iter->first;
			else
				iter->second += 1;
		}
	}

	return -1;
}

void MoreThanHalfNum_Solution::demo()
{
	vector<int> vec = initializer_list<int>{3, 3, 3, 3, 2, 2, 3};
	cout << this->solve(vec) << endl;
}