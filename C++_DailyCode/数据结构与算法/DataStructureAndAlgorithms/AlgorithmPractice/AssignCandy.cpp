#include "GreedyAlgorithmHeaders.h"

/*糖果分配问题										**/
void funcTestAssignCandy()
{
	/*第一组数据测试								**/
	vector<int> fstBboys = initializer_list<int>{ 1, 3, 5, 7 };

	int candyCount = AlgorithmAssignCandy(fstBboys);
	cout << "First Test Of Candy Count: " << candyCount << endl;

	/*第二组数据测试								**/
	vector<int> secBboys = initializer_list<int>{ 1, 9, 15, 3 };

	candyCount = AlgorithmAssignCandy(secBboys);
	cout << "Second Test Of Candy Count: " << candyCount << endl;

	/*第三组数据测试								**/
	vector<int> trdBboys = initializer_list<int>{ 11, 10, 7, 2 };

	candyCount = AlgorithmAssignCandy(trdBboys);
	cout << "Third Test Of Candy Count: " << candyCount << endl;
}

int AlgorithmAssignCandy(vector<int> boys)
{
	vector<int> candyVec(boys.size(), 1);

	for (int i = 0; i < (boys.size() - 1); ++i)
	{
		if (boys[i + 1] > boys[i])
			candyVec[i + 1] = candyVec[i] + 1;
	}

	for (int j = (boys.size() - 1); j > 0; --j)
	{
		if (boys[j - 1] > boys[j])
			candyVec[j - 1] = max(candyVec[j - 1], candyVec[j] + 1);
	}

	return accumulate(candyVec.begin(), candyVec.end(), 0);
}