#include <iostream>
#include "FuncTest\FuncTest.h"
#include "FuncTest\LibApiTest.h"
using namespace std;

/*当前测试模块标识宏							**/
#define CURRENT_TEST_FLAG						19

/*测试函数										**/
void funcTest();

int main()
{
	funcTest();

	return 0;
}

void funcTest()
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


#if 7 == CURRENT_TEST_FLAG
	/*OpenSSL RSA API测试						**/
	funcOpensslRsaSaveApiTest();
#endif


#if 8 == CURRENT_TEST_FLAG
	/*OpenSSL RSA API测试						**/
	funcOpensslRsaBIOSaveApiTest();
#endif


#if 9 == CURRENT_TEST_FLAG
	/*OpenSSL RSA API测试						**/
	funcOpensslRsaSaveApiTest();
	funcOpensslRsaEnCodeApiTest();
#endif


#if 10 == CURRENT_TEST_FLAG
	/*OpenSSL RSA API测试						**/
	funcOpensslRsaVertifyApiTest();
#endif


#if 11 == CURRENT_TEST_FLAG
	/*OpenSSL AES API测试						**/
	funcOpensslAesApiTest();
#endif


#if 12 == CURRENT_TEST_FLAG
	/*JsonCpp 写文件 API测试					**/
	funcJsonCppOfstreamWriteFileApiTest();
#endif


#if 13 == CURRENT_TEST_FLAG
	/*JsonCpp 写文件 API测试					**/
	funcJsonCppFastWriterWriteFileApiTest();
#endif


#if 14 == CURRENT_TEST_FLAG
	/*JsonCpp 读文件 API测试					**/
	funcJsonCppReadFileApiTest();
#endif


#if 15 == CURRENT_TEST_FLAG
	/*OpenSSL Base64 API测试					**/
	funcOpensslBase64ApiTest();
#endif


#if 16 == CURRENT_TEST_FLAG
	/*客户端共享内存模块测试					**/
	funModelClientMemoryShareTest();
#endif 
	

#if 17 == CURRENT_TEST_FLAG
	/*RSA加密模块测试							**/
	funcRsaEncryptTest();
#endif
	

#if 18 == CURRENT_TEST_FLAG
	/*json读取配置模块测试						**/
	funcClientJsonConfTest();
#endif
	

#if 19 == CURRENT_TEST_FLAG
	/*工厂模块测试								**/
	funcFactoryTest();
#endif
	
}