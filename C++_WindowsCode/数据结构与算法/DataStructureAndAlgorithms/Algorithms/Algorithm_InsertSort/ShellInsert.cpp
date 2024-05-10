#include "ShellInsert.h"

/*希尔插入排序												**/
void funcCallShellInsertSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7 ,8 };
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcShellInsertSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 6, 7, 1, 5, 2, 9, 11 ,0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcShellInsertSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 3, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcShellInsertSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcShellInsertSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	int increment = size / 2;

	/*原始序列分组												**/
	for (int curIncr = increment; curIncr > 0; --curIncr)
	{
		/*每个组进行排序, 起始位置为各子序列索引为[1]的元素		**/
		for (int i = curIncr; i < size; ++i)
		{
			if (sortVec[i] < sortVec[i - curIncr])				// 子序列第一次调用时, 将索引为[1]的元素与索引为[0]的元素比较
			{
				int sortValue = sortVec[i];
				int j = i - curIncr;							// 子序列第一次调用时, 指向索引为[0]的元素
				for (; j >= 0; j -= curIncr)
				{
					sortVec[j + curIncr] = sortVec[j];			// 子序列第一次调用时, 将索引为[0]的元素拷贝至索引为[1]的位置
				}
				sortVec[j + curIncr] = sortValue;				// 子序列第一次调用时, 将索引为[1]的元素拷贝至索引为[0]的位置
			}
		}
	}
}