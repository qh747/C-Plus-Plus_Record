#include "HeapSort.h"

/*堆排序															**/
void funcCallHeapSort()
{
	/*第一组数据测试												**/
	vector<int> fstIntVec = initializer_list<int>{ 1, 3, 2, 10, 5, 4, 7 ,8 };
	cout << "First Test Before Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcHeapSort(fstIntVec);
	cout << "First Test After Sort: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 6, 7, 1, 5, 2, 9, 11 ,0 };
	cout << "Second Test Before Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcHeapSort(secIntVec);
	cout << "Second Test After Sort: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 2, 5, 7, 2, 4, 6 ,8 };
	cout << "Third Test Before Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	funcHeapSort(trdIntVec);
	cout << "Third Test After Sort: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << endl;
}

void funcHeapAdjust(vector<int>& vec, int curSize, int curIndex)
{
	/*暂且认为当前数值最大的元素索引为传入参数的元素索引					**/
	int curBiggestIndex = curIndex;

	/*获取当前元素的左孩子、右孩子节点的索引								**/
	int leftSonIndex = curIndex * 2 + 1;
	int rightSonIndex = curIndex * 2 + 2;

	/*最大值元素索引比较以及获取											**/
	if (leftSonIndex < curSize && vec[curBiggestIndex] < vec[leftSonIndex])
	{
		/*左孩子节点索引未数组越界 && 最大元素索引 < 左孩子节点索引			**/
		curBiggestIndex = leftSonIndex;
	}

	if (rightSonIndex < curSize && vec[curBiggestIndex] < vec[rightSonIndex])
	{
		/*左孩子节点索引未数组越界 && 最大元素索引 < 左孩子节点索引			**/
		curBiggestIndex = rightSonIndex;
	}

	/*最大值节点元素索引发生改变											**/
	if (curBiggestIndex != curIndex)
	{
		swap(vec[curIndex], vec[curBiggestIndex]);

		/*递归调整															**/
		funcHeapAdjust(vec, curSize, curBiggestIndex);
	}
}

void funcHeapSort(vector<int>& sortVec)
{
	int size = sortVec.size();
	if (size < 2)
		return;

	/*建立堆，从最后一个非叶子节点开始建立堆								**/
	for (int i = (size /2 - 1); i >= 0; --i)
	{
		funcHeapAdjust(sortVec, size, i);
	}

	/*堆调整																**/
	for (int j = size - 1; j > 0; --j)
	{
		/*建立堆和调整堆后, 0号索引元素为数组中最大值, 与末尾值进行交换		**/
		swap(sortVec[0], sortVec[j]);

		/*从堆中移除末尾元素, 并对剩余元素重新进行堆调整					**/
		funcHeapAdjust(sortVec, --size, 0);
	}
}