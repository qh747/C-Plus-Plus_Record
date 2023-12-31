#include "MergeSort.h"

/*归并排序															**/
void funcCallMergeSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{ 1, 3, 2, 10, 5, 4, 7 ,8 };
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcMergeSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 6, 7, 1, 5, 2, 9, 11 ,0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcMergeSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 2, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcMergeSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcMergeVec(vector<int>& vec, int startIndex, int endIndex, int midIndex)
{
	vector<int> curSortVec;
	int curLeftIndex = startIndex;
	int curRightIndex = midIndex + 1;
	while (curLeftIndex <= midIndex && curRightIndex <= endIndex)
	{
		if (vec[curLeftIndex] < vec[curRightIndex])
		{
			curSortVec.push_back(vec[curLeftIndex]);
			++curLeftIndex;
		}
		else
		{
			curSortVec.push_back(vec[curRightIndex]);
			++curRightIndex;
		}
	}

	while (curLeftIndex <= midIndex)
	{
		curSortVec.push_back(vec[curLeftIndex]);
		++curLeftIndex;
	}

	while (curRightIndex <= endIndex)
	{
		curSortVec.push_back(vec[curRightIndex]);
		++curRightIndex;
	}

	int sortVecIndex = 0;
	for (int i = startIndex; i <= endIndex; ++i)
	{
		vec[i] = curSortVec[sortVecIndex];
		++sortVecIndex;
	}
}

void funcSpiltVec(vector<int>& vec, int startIndex, int endIndex, int midIndex)
{
	if (startIndex >= endIndex)
		return;

	funcSpiltVec(vec, startIndex, midIndex, (startIndex + midIndex) / 2);
	funcSpiltVec(vec, midIndex + 1, endIndex, (midIndex + 1 + endIndex) / 2);
	funcMergeVec(vec, startIndex, endIndex, midIndex);
}

void funcMergeSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	int startIndex = 0;
	int endIndex = size - 1;
	int midIndex = (startIndex + endIndex) / 2;

	funcSpiltVec(sortVec, startIndex, endIndex, midIndex);
}