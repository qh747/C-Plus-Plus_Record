#include "RadixSort.h"

/*基数排序															**/
void funcCallRadixSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{ 1000, 300, 20, 10000, 5, 45, 789 ,856 };
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcRadixSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 60, 70, 101, 5, 2, 999, 1100, 0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcRadixSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 2, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcRadixSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcRadixSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	/*获取最大值																	**/
	int maxVal = -1;
	for (int i = 0; i < size; ++i)
	{
		if (maxVal < sortVec[i])
			maxVal = sortVec[i];
	}
	
	/*获取最大值的位数																**/
	int maxPos = 0;
	while (maxVal > 0)
	{
		++maxPos;
		maxVal /= 10;
	}

	/*由最大值的位数决定循环总共需要进行多少次										**/
	int base = 1;
	while (maxPos--)
	{
		/*记录元素出现的次数														**/
		vector<int> countVec(10, 0);
		for (int i = 0; i < size; ++i)
		{
			int index = sortVec[i] / base % 10;
			++countVec[index];
		}

		/*根据上的元素的起始位置和出现次数推导当前元素的起始位置					**/
		vector<int> startVec(11, 0);
		for (int j = 1; j <= 10; ++j)
		{
			/*例如: 位数为0的起始位置为0，出现次数3次, 则位数为1的起始位置为3		**/
			startVec[j] = countVec[j - 1] + startVec[j - 1];
		}

		/*根据元素的起始位置对元素进行排序											**/
		vector<int> tmpValVec(size, 0);
		for (int k = 0; k < size; ++k)
		{
			/*获取当前元素的末位													**/
			int index = sortVec[k] / base % 10;

			/*根据位数的起始位置对元素排序											**/
			tmpValVec[startVec[index]] = sortVec[k];

			/*当前位数的起始位置向后移动1位											**/
			++startVec[index];
		}

		/*将本轮排序好的元素进行赋值												**/
		for (int index = 0; index < size; ++index)
		{
			sortVec[index] = tmpValVec[index];
		}

		/*基数扩大10倍																**/
		base *= 10;
	}
}