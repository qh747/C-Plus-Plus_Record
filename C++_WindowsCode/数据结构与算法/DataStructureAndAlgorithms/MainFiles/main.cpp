#include  <iostream>
#include "AlgorithmTest.h"
#include "DataStructTest.h"
#include "AlgorithmPracticeTest.h"
using namespace std;

#define TEST_TYPE 1

int main()
{
#if 1 == TEST_TYPE

	/*算法测试									**/
	algorithmTest();

#elif 2 == TEST_TYPE

	/*数据结构测试								**/
	dataStructTest();

#elif 3 == TEST_TYPE

	/*算法练习测试								**/
	algorithmPracticeTest();

#endif 

	return 0;
}

