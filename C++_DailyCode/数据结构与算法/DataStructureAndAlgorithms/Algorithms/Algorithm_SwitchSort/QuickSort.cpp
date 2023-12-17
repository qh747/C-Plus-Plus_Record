#include "QuickSort.h"

/*快速排序																			**/
void funcCallQuickSort()
{
	int testArray[5] = { 0, 8, 2, 7, 4 };
	int arraySize = sizeof(testArray) / sizeof(testArray[0]);

	/*打印排序前的数组																**/
	cout << "Before Sort. Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;

	/*快速排序																		**/
	int startPos = 0;
	int endPos = arraySize - 1;
	funcQuickSort(testArray, startPos, endPos);

	/*打印排序后的数组																**/
	cout << "After Sort.  Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;
}

void funcQuickSort(int* pArray, int startPos, int endPos)
{
	if (startPos >= endPos)
		return;

	/*获取当前循环起始和结束值														**/
	int curStartPos = startPos;
	int curEndPos = endPos;

	/*设置起始位置的元素为当前循环的中间值											**/
	int midVal = pArray[startPos]; 

	/*将数组中大于中间值的元素移动至左边											**/
	while (curEndPos > curStartPos)
	{
		/*当前值小于中间值, 移动至中间值左边										**/
		if (pArray[curEndPos] < midVal)
		{
			pArray[curStartPos] = pArray[curEndPos];
			break;
		}
		else
			--curEndPos;
	}

	/*将数组中小于中间值的元素移动至右边											**/
	while (curStartPos < curEndPos)
	{
		/*当前值大于中间值, 移动至中间值右边										**/
		if (pArray[curStartPos] > midVal)
		{
			pArray[curEndPos] = pArray[curStartPos];
			break;
		}
		else
			++curStartPos;
	}

	/*中间值移动																	**/
	pArray[curStartPos] = midVal;
	int lstPos = curStartPos;

	/*中间值左侧元素递归排序														**/
	funcQuickSort(pArray, 0, lstPos - 1);

	/*中间值右侧元素递归排序														**/
	funcQuickSort(pArray, lstPos + 1, endPos);
}