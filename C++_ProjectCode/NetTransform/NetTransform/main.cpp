#include <iostream>
#include "FuncTest\FuncTest.h"
using namespace std;

/*当前测试模块标识宏							**/
#define CURRENT_TEST_FLAG 1

int main()
{
#if 1 == CURRENT_TEST_FLAG

	/*Request_Codec模块测试						**/
	funcModelRequestCodecTest();

	/*Response_Codec模块测试					**/
	funcModelResponseCodecTest();

#endif // 1 == CURRENT_TEST_FLAG

	return 0;
}