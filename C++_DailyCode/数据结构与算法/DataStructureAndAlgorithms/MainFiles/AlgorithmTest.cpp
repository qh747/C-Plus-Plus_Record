#include "AlgorithmTest.h"
#define ALGTHM_TEST_SEQ  7

/*功能测试											**/
void algorithmTest()
{
#if 1 == ALGTHM_TEST_SEQ
	/*冒泡排序测试									**/
	funcBubbleSort();

#elif 2 == ALGTHM_TEST_SEQ
	/*冒泡排序改进测试								**/
	funcBubbleImproveSort();

#elif 3 == ALGTHM_TEST_SEQ
	/*快速排序										**/
	funcCallQuickSort();

#elif 4 == ALGTHM_TEST_SEQ
	/*链表反转										**/
	funcLinkListReverse();

#elif 5 == ALGTHM_TEST_SEQ
	/*选择排序										**/
	funcCallChooseSort();

#elif 6 == ALGTHM_TEST_SEQ
	/*直接插入排序									**/
	funcCallDirectInsertSort();

#elif 7 == ALGTHM_TEST_SEQ
	/*二分插入排序									**/
	funcCallBinaryInsertSort();

#elif 8 == ALGTHM_TEST_SEQ
	/*希尔排序										**/
	funcCallShellInsertSort();

#endif
}