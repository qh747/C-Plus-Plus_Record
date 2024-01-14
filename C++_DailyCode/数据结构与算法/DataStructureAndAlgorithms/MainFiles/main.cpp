#include  <iostream>
#include "AlgorithmTest.h"
#include "DataStructTest.h"
using namespace std;

#define TEST_TYPE 1

int main()
{
#if 1 == TEST_TYPE

	/*算法测试									**/
	algorithmTest();

#endif 

#if 2 == TEST_TYPE

	/*数据结构测试								**/
	dataStructTest();

#endif 

	return 0;
}

