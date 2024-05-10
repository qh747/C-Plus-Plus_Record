#include "GreedyAlgorithmHeaders.h"

void funcTestIntervalOverlap()
{
	/*第一组数据测试													**/
	vector<vector<int>> fstIntervalVec;
	fstIntervalVec.push_back(vector<int>{1, 2});
	fstIntervalVec.push_back(vector<int>{1, 3});
	fstIntervalVec.push_back(vector<int>{2, 4});

	int overlapCount = AlgorithmIntervalOverlap(fstIntervalVec);
	cout << "First Overlap Count: " << overlapCount << endl;

	/*第二组数据测试													**/
	vector<vector<int>> secIntervalVec;
	secIntervalVec.push_back(vector<int>{2, 5});
	secIntervalVec.push_back(vector<int>{0, 3});
	secIntervalVec.push_back(vector<int>{1, 4});

	overlapCount = AlgorithmIntervalOverlap(secIntervalVec);
	cout << "Second Overlap Count: " << overlapCount << endl;

	/*第三组数据测试													**/
	vector<vector<int>> trdIntervalVec;
	trdIntervalVec.push_back(vector<int>{2, 3});
	trdIntervalVec.push_back(vector<int>{0, 1});
	trdIntervalVec.push_back(vector<int>{4, 7});

	overlapCount = AlgorithmIntervalOverlap(trdIntervalVec);
	cout << "Third Overlap Count: " << overlapCount << endl;
}

int	AlgorithmIntervalOverlap(vector<vector<int>> intervalVec)
{
	if (intervalVec.empty())
		return 0;

	for (int i = 0; i < intervalVec.size(); ++i)
	{
		vector<int>& curSubVec = intervalVec[i];
		sort(curSubVec.begin(), curSubVec.end());
	}

	sort(intervalVec.begin(), intervalVec.end(), [](vector<int>& fstSubVec, vector<int>& secSubVec) {
		return fstSubVec[1] < secSubVec[1];
		});

	int overlapCount = 0;
	vector<int>& subVec = intervalVec[0];
	for (int j = 1; j < intervalVec.size(); ++j)
	{
		vector<int>& curSubVec = intervalVec[j];
		if (subVec[1] > curSubVec[0])
			++overlapCount;
		else
			subVec = intervalVec[j];
	}

	return overlapCount;
}