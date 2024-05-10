#include "MyMessageTest.h"
#include "MyEnumMsgTest.h"
#include "MyImportInfoTest.h"
#include "MyImportPkgTest.h"

/*测试函数控制开关									**/
#define CUR_TEST_SEQ 4

int main()
{
#if 1 == CUR_TEST_SEQ
	/*protobufs使用MyMessage测试函数				**/
	funcMyMessageTest();
#endif

#if 2 == CUR_TEST_SEQ
	/*protobuf使用MyEnumMsg测试函数					**/
	funcMyEnumMsgTest();
#endif

#if 3 == CUR_TEST_SEQ
	/*protobuf使用MyImportInfo测试函数				**/
	funcMyImportInfoTest();
#endif

#if 4 == CUR_TEST_SEQ
	/*protobuf使用MyImportPkg测试函数				**/
	funcMyImportPkgTest();
#endif

	return 0;
}