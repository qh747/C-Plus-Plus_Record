#include "DirectInsertSort.h"

/*直接插入排序												**/
void funcCallDirectInsertSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{ 1, 3, 2, 10, 5, 4, 7 ,8 };
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcDirectInsertSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 6, 7, 1, 5, 2, 9, 11 ,0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcDirectInsertSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 3, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcDirectInsertSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcDirectInsertSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	for (int i = 1; i < size; ++i)
	{
		int curSortVal = sortVec[i];
		int j = i - 1;
		for (; j >= 0; --j)
		{
			if (sortVec[j] > curSortVal)
				sortVec[j + 1] = sortVec[j];
			else
				break;
		}
		sortVec[j + 1] = curSortVal;
	}
}