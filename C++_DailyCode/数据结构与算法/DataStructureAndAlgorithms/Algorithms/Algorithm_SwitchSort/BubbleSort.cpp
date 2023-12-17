#include "BubbleSort.h"

void funcBubbleSort()
{
	int testArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 9, 8 };
	int arraySize = sizeof(testArray) / sizeof(testArray[0]);

	/*打印排序前的数组																										**/
	cout << "Before Sort. Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;

	/*冒泡排序, 对于长度为n的数组，只需要比较n-1个元素即可																	**/
	for (int foreachTimes = 0; foreachTimes < (arraySize - 1); ++foreachTimes)
	{
		int tempVal = 0;
		/*因为每一轮比较，都能够将一个最大值放在对应的位置上, 因此每次进行循环时就只比对就需要减去比对循环次数				**/
		for (int curForeachSeq = 0; curForeachSeq < (arraySize - 1 - foreachTimes); ++curForeachSeq)
		{
			int& lftVal = testArray[curForeachSeq];
			int& rgtVal = testArray[curForeachSeq + 1];

			/*当前一个元素大于后一个元素时，需要调换前后元素的位置															**/
			if (lftVal > rgtVal)
			{
				tempVal = lftVal;
				lftVal = rgtVal;
				rgtVal = tempVal;
			}
		}
	}

	/*打印排序后的数组																										**/
	cout << "After Sort.  Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;
}

void funcBubbleImproveSort()
{
	int testArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 9, 8 };
	int arraySize = sizeof(testArray) / sizeof(testArray[0]);

	/*打印排序前的数组																										**/
	cout << "Before Sort. Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;

	/*冒泡排序																												**/
	bool switchFlag = true;
	for (int foreachTimes = 0; foreachTimes < (arraySize - 1); ++foreachTimes)
	{
		/*标志位判断, 如果上轮没有更换元素位置, 代表数组已有序，退出冒泡排序循环											**/
		if (false == switchFlag)
			break;

		int tempVal = 0;
		/*因为每一轮比较，都能够将一个最大值放在对应的位置上, 因此每次进行循环时就只比对就需要减去比对循环次数				**/
		switchFlag = false;
		for (int curForeachSeq = 0; curForeachSeq < (arraySize - 1 - foreachTimes); ++curForeachSeq)
		{
			int& lftVal = testArray[curForeachSeq];
			int& rgtVal = testArray[curForeachSeq + 1];

			/*当前一个元素大于后一个元素时，需要调换前后元素的位置															**/
			if (lftVal > rgtVal)
			{
				tempVal = lftVal;
				lftVal = rgtVal;
				rgtVal = tempVal;

				switchFlag = true;
			}
		}
	}

	/*打印排序后的数组																										**/
	cout << "After Sort.  Array: ";
	for (int i = 0; i < arraySize; ++i)
		cout << testArray[i] << " ";
	cout << endl;
}
