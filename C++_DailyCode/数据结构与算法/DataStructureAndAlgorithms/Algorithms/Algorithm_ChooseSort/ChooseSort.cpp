#include "ChooseSort.h"

/*选择排序															**/
void funcCallChooseSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{1, 3, 2, 10, 5, 4, 7 ,8};
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val){ cout << val << " "; });
	cout << endl;

	funcChooseSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 6, 7, 1, 5, 2, 9, 11 ,0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcChooseSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 3, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcChooseSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcChooseSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	for (int i = 0; i < size; ++i)
	{
		int curSortIndex = i;
		for (int j = i; j < size; ++j)
		{
			/*找到本次循环数值最小的索引编号						**/
			if (sortVec[j] < sortVec[curSortIndex])
				curSortIndex = j;
		}

		/*交换本次循环数值最小的索引编号和当前循环的索引编号的值	**/
		if (i != curSortIndex)
			swap(sortVec[i], sortVec[curSortIndex]);
	}
}