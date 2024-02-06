#include "AlgorithmPracticeTest.h"

#define ALGTHM_PRACTICE_TEST_SEQ  2

/*算法练习测试															**/
void algorithmPracticeTest()
{
#if 1 == ALGTHM_PRACTICE_TEST_SEQ
	/*饼干分配测试														**/
	funcTestAssignCookies();

#elif 2 == ALGTHM_PRACTICE_TEST_SEQ
	/*糖果分配问题														**/
	funcTestAssignCandy();
	

#endif
}