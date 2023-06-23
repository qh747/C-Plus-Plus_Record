#include "LibApiTest.h"

/*OpenSSL MD5 API测试											**/
void funcOpensslMd5ApiTest()
{
	/*md5多条数据加密											**/
	/*md5哈希上下文初始化										**/
	MD5_CTX md5Data;
	MD5_Init(&md5Data);
	
	char fstSrcData[10] = "hello";
	char secSrcData[10] = " world.";
	printf("SRC DATA: %s%s\n", fstSrcData, secSrcData);

	/*对多条数据进行加密										**/
	MD5_Update(&md5Data, fstSrcData, strlen(fstSrcData));
	MD5_Update(&md5Data, secSrcData, strlen(secSrcData));

	/*得到加密数据												**/
	unsigned char totalDstData[MD5_DIGEST_LENGTH] = "\0";
	MD5_Final(totalDstData, &md5Data);

	/*打印加密数据												**/
	printf("DST DATA: ");
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		printf("%02x", totalDstData[i]);
	}
	printf("\n\n");

	/*md5单条数据加密											**/
	char srcData[20] = "hello md5\0";
	unsigned char dstData[MD5_DIGEST_LENGTH] = "\0";
	MD5((const unsigned char *)srcData, strlen(srcData), dstData);

	printf("SRC DATA: %s\n", srcData);
	printf("DST DATA: ");
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		printf("%02x", dstData[i]);
	}
	printf("\n");
}

/*OpenSSL SHA API测试												**/
void funcOpensslShaApiTest()
{
	/*sha256多条数据加密											**/
	/*sha256哈希上下文初始化										**/
	SHA256_CTX sha256Data;
	SHA256_Init(&sha256Data);

	char fstSrcData[10] = "hello";
	char secSrcData[10] = " world.";
	printf("SRC DATA: %s%s\n", fstSrcData, secSrcData);

	/*对多条数据进行加密											**/
	SHA256_Update(&sha256Data, fstSrcData, strlen(fstSrcData));
	SHA256_Update(&sha256Data, secSrcData, strlen(secSrcData));

	/*得到加密数据													**/
	unsigned char totalDstData[SHA256_DIGEST_LENGTH] = "\0";
	SHA256_Final(totalDstData, &sha256Data);

	/*打印加密数据													**/
	printf("DST DATA: ");
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		printf("%02x", totalDstData[i]);
	}
	printf("\n\n");

	/*sha256单条数据加密											**/
	char srcData[20] = "hello sah256\0";
	unsigned char dstData[SHA256_DIGEST_LENGTH] = "\0";
	SHA256((const unsigned char *)srcData, strlen(srcData), dstData);

	printf("SRC DATA: %s\n", srcData);
	printf("DST DATA: ");
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		printf("%02x", dstData[i]);
	}
	printf("\n");
}