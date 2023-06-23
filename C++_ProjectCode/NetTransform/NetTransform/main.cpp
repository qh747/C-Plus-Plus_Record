#include <iostream>
#include "FuncTest\FuncTest.h"
#include "FuncTest\LibApiTest.h"
using namespace std;

/*当前测试模块标识宏							**/
#define CURRENT_TEST_FLAG						6

int main()
{
#if 1 == CURRENT_TEST_FLAG
	/*编解码模块测试							**/
	funcThreadCodecTest();
#endif 


#if 2 == CURRENT_TEST_FLAG
	/*Socket模块测试							**/
	funcThreadSocketTest();
#endif 


#if 3 == CURRENT_TEST_FLAG
	/*共享内存模块测试							**/
	funcMemoryShareTest();
#endif 


#if 4 == CURRENT_TEST_FLAG
	/*OpenSSL MD5 API测试						**/
	funcOpensslMd5ApiTest();
#endif


#if 5 == CURRENT_TEST_FLAG
	/*OpenSSL SHA API测试						**/
	funcOpensslShaApiTest();
#endif


#if 6 == CURRENT_TEST_FLAG
	/*加密模块测试								**/
	funcEncryptTest();
#endif
	

	return 0;
}