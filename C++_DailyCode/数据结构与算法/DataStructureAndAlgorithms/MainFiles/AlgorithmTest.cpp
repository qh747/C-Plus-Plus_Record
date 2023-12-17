#include "AlgorithmTest.h"
#define ALGTHM_TEST_SEQ  4

/*功能测试											**/
void algorithmTest()
{
#if 1 == ALGTHM_TEST_SEQ
	/*冒泡排序测试									**/
	funcBubbleSort();
#endif

#if 2 == ALGTHM_TEST_SEQ
	/*冒泡排序改进测试								**/
	funcBubbleImproveSort();
#endif

#if 3 == ALGTHM_TEST_SEQ
	/*快速排序										**/
	funcCallQuickSort();
#endif


#if 4 == ALGTHM_TEST_SEQ
	/*链表反转										**/
	funcLinkListReverse();
#endif
}