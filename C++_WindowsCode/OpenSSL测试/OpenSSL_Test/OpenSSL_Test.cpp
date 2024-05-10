#include "OpenSSL_Test.h"

/*OpenSSL安装是否成功测试				**/
void funcOpenSSLInstallSuccessTest()
{
	/*原始数据					**/
	char srcStr[6] = "hello";

	/*加密后数据				**/
	char dstStr[33] = "\0";
	memset(dstStr, 0, sizeof(dstStr));

	/*使用md5加密				**/
	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, srcStr, strlen(srcStr));
	unsigned char md[MD5_DIGEST_LENGTH] = "\0";
	MD5_Final(md, &ctx);
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf(&dstStr[i * 2], "%02x", md[i]);
	}

	/*输出加密前后的字符串		**/
	cout << "SRC STR: " << srcStr << endl;
	cout << "DST STR: " << dstStr << endl;
}