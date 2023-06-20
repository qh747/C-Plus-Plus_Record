#include <iostream>
#include "FuncTest\FuncTest.h"
using namespace std;

/*当前测试模块标识宏							**/
#define CURRENT_TEST_FLAG 3

int main()
{
#if 1 == CURRENT_TEST_FLAG
	/*编解码模块测试							**/
	funcThreadCodecTest();
#endif // 1 == CURRENT_TEST_FLAG

#if 2 == CURRENT_TEST_FLAG
	/*Socket模块测试							**/
	funcThreadSocketTest();
#endif // 2 == CURRENT_TEST_FLAG

#if 3 == CURRENT_TEST_FLAG
	/*共享内存模块测试							**/
	funcMemoryShareTest();
#endif // 3 == CURRENT_TEST_FLAG

	return 0;
}