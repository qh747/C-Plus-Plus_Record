#include "LibApiTest.h"

//extern "C"
//{
//	/*解决APPLINK错误问题										**/
//	#include <openssl\applink.c>
//};

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

/*OpenSSL SHA API测试											**/
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

/*OpenSSL RSA API测试											**/
void funcOpensslRsaSaveApiTest()
{
	/*初始化RSA													**/
	RSA* pRsa = RSA_new();

	BIGNUM* pBigNum = BN_new();
	BN_set_word(pBigNum, RSA_F4);

	/*生成RSA密钥对												**/
	int genResult = RSA_generate_key_ex(pRsa, 2048, pBigNum, NULL);

	/*RSA密钥对写入文件											**/
	FILE* pFile = fopen("./FuncTest/publickey.pem", "wb");
	PEM_write_RSAPublicKey(pFile, pRsa);
	fclose(pFile);

	pFile = fopen("./FuncTest/privatekey.pem", "wb");
	PEM_write_RSAPrivateKey(pFile, pRsa, NULL, NULL, 0, NULL, NULL);
	fclose(pFile);

	/*销毁RSA													**/
	BN_free(pBigNum);
	RSA_free(pRsa);
}

void funcOpensslRsaBIOSaveApiTest()
{
	/*初始化RSA													**/
	RSA* pRsa = RSA_new();

	BIGNUM* pBigNum = BN_new();
	BN_set_word(pBigNum, RSA_F4);

	/*生成RSA密钥对												**/
	int genResult = RSA_generate_key_ex(pRsa, 2048, pBigNum, NULL);

	/*RSA密钥对写入文件											**/
	BIO* pPubBio = BIO_new_file("./FuncTest/BIO_publickey.pem", "wb");
	PEM_write_bio_RSAPublicKey(pPubBio, pRsa);

	BIO* pPrvBio = BIO_new_file("./FuncTest/BIO_prvlickey.pem", "wb");
	PEM_write_bio_RSAPrivateKey(pPrvBio, pRsa, NULL, NULL, 0, NULL, NULL);

	/*销毁RSA													**/
	BN_free(pBigNum);
	RSA_free(pRsa);
	BIO_free(pPubBio);
	BIO_free(pPrvBio);
}

void funcOpensslRsaEnCodeApiTest()
{
	/*从文件中读取公钥											**/
	RSA* pRsa = RSA_new();

	/*读取公钥													**/
	FILE* pFile = fopen("./FuncTest/publickey.pem", "rb");
	PEM_read_RSAPublicKey(pFile, &pRsa, NULL, NULL);
	fclose(pFile);

	/*读取私钥													**/
	pFile = fopen("./FuncTest/privatekey.pem", "rb");
	PEM_read_RSAPrivateKey(pFile, &pRsa, NULL, NULL);
	fclose(pFile);

	/*原始数据加密												**/
	char originData[16] = "hello world.";
	int keyLen = RSA_size(pRsa);
	
	char* pEncryptBuf = new char[keyLen + 1];
	memset(pEncryptBuf, 0, sizeof(pEncryptBuf));
	int encryptSize = RSA_public_encrypt(strlen(originData), (unsigned char *)originData, (unsigned char *)pEncryptBuf, pRsa, RSA_PKCS1_PADDING);
	pEncryptBuf[encryptSize] = '\0';

	/*数据解密													**/
	char* pDecryptBuf = new char[keyLen];
	memset(pDecryptBuf, 0, sizeof(pDecryptBuf));
	int decryptSize = RSA_private_decrypt(keyLen, (const unsigned char *)pEncryptBuf, (unsigned char *)pDecryptBuf, pRsa, RSA_PKCS1_PADDING);
	pDecryptBuf[decryptSize] = '\0';

	cout << "ORIGIN  DATA: " << originData << endl << endl;
	cout << "ENCRYPT DATA: " << pEncryptBuf << endl << endl;
	cout << "DECRYPT DATA: " << pDecryptBuf << endl << endl;

	delete[] pEncryptBuf;
	delete[] pDecryptBuf;
	RSA_free(pRsa);
}

void funcOpensslRsaVertifyApiTest()
{
	/*从文件中读取公钥											**/
	RSA* pRsa = RSA_new();

	/*读取公钥													**/
	FILE* pFile = fopen("./FuncTest/publickey.pem", "rb");
	PEM_read_RSAPublicKey(pFile, &pRsa, NULL, NULL);
	fclose(pFile);

	/*读取私钥													**/
	pFile = fopen("./FuncTest/privatekey.pem", "rb");
	PEM_read_RSAPrivateKey(pFile, &pRsa, NULL, NULL);
	fclose(pFile);

	/*数字签名计算												**/
	char originData[16] = "hello world.";
	int sigVertifyLen = RSA_size(pRsa);
	char* sigVertify = new char[RSA_size(pRsa) + 1];
	
	int result = RSA_sign(NID_md5, (unsigned char *)originData, strlen(originData), (unsigned char *)sigVertify, (unsigned int *)&sigVertifyLen, pRsa);
	sigVertify[strlen(sigVertify)] = '\0';
	cout << "SIGN: " << result  << " " << sigVertify << endl;

	/*数字签名验证												**/
	result = RSA_verify(NID_md5, (unsigned char *)originData, strlen(originData), (unsigned char *)sigVertify, sigVertifyLen, pRsa);
	sigVertify[strlen(sigVertify)] = '\0';
	cout << "VERTIFY: " << result << " " << sigVertify << endl;

	delete[] sigVertify;
	RSA_free(pRsa);
}

/*OpenSSL AES API测试											**/
void funcOpensslAesApiTest()
{
	/*原始数据准备						**/
	const unsigned char* originData = (const unsigned char *)"qwertyuiopasdfghjklzxcvbnm01234567899876543210mnbvcxzlkjhgfdsapoiuytrewq";
	cout << "SRC DATA: " << originData << endl;

	/*密钥准备							**/
	const char* userKey = "1234567887654321";
	int bits = strlen(userKey);

	/*设置加密密钥						**/
	AES_KEY encryptKey;
	AES_set_encrypt_key((const unsigned char *)userKey, bits * 8, &encryptKey);

	/*加密								**/
	int dataLen = strlen((const char *)originData) + 1;
	int padLen = AES_BLOCK_SIZE - (dataLen % AES_BLOCK_SIZE);
	int length = dataLen + padLen;

	unsigned char* enc = new unsigned char[length];
	unsigned char* enIvec = new unsigned char[bits];

	AES_cbc_encrypt(originData, enc, length, &encryptKey, enIvec, AES_ENCRYPT);
	cout << "ENC DATA: " << enc << endl;

	/*设置解密密钥						**/
	AES_KEY decryptKey;
	AES_set_decrypt_key((const unsigned char *)userKey, bits * 8, &decryptKey);

	/*解密								**/
	unsigned char* dec = new unsigned char[length];
	unsigned char* deIvec = new unsigned char[bits];

	AES_cbc_encrypt(enc, dec, length, &decryptKey, deIvec, AES_DECRYPT);
	cout << "DEC DATA: " << dec << endl;

	delete[] enc;
	delete[] enIvec;
	delete[] dec;
	delete[] deIvec;
}

/*OpenSSL Base64 API测试										**/
void funcOpensslBase64ApiTest()
{
	const char* originData = "hello world";
	int originDataLen = strlen(originData);
	cout << "ORIGIN DATA: " << originData << endl;

	/*编码流程													**/
	BIO* pCodec = BIO_new(BIO_f_base64());
	BIO* pCodecMem = BIO_new(BIO_s_mem());
	BIO_push(pCodec, pCodecMem);

	BIO_write(pCodec, originData, originDataLen);
	BIO_flush(pCodec);

	BUF_MEM* pCodecBuf = NULL;
	BIO_get_mem_ptr(pCodec, &pCodecBuf);
	
	char* pCodecData = new char[pCodecBuf->length + 1];
	memcpy(pCodecData, pCodecBuf->data, pCodecBuf->length);
	pCodecData[pCodecBuf->length] = '\0';
	
	cout << "CODEC DATA : " << pCodecData << endl;
	BIO_free_all(pCodec);
	
	/*解码流程													**/
	BIO* pDeCodec = BIO_new(BIO_f_base64());
	BIO* pDecodecMem = BIO_new_mem_buf(pCodecData, strlen(pCodecData));
	BIO_push(pDeCodec, pDecodecMem);

	char decodecData[256] = "\0";
	int readLen = BIO_read(pDeCodec, decodecData, sizeof(decodecData));
	decodecData[readLen] = '\0';
	
	cout << "DECODEC DATA: " << decodecData << endl;
	BIO_free_all(pDeCodec);
	delete[] pCodecData;
}

/*JsonCpp 写文件 API测试										**/
void funcJsonCppOfstreamWriteFileApiTest()
{
	/*创建Value类型的json根对象									**/
	Value root;

	/*添加int类型数据											**/
	root.append(1);												// append()函数会进行隐式转换，将int类型数据转换为Value类型

	/*添加double类型数据										**/
	root.append(2.2);

	/*添加bool类型数据											**/
	root.append(true);

	/*添加字符串类型数据										**/
	root.append("hello");

	/*添加数组类型数据											**/
	Value subVec;												// Value数组类型对象支持添加不同类型数据
	subVec[0] = 11;
	subVec[1] = true;
	subVec[2] = 22.22;
	subVec[3] = "bye";
	root.append(subVec);

	/*添加object类型数据										**/
	Value subObj;
	subObj["key"] = "value";
	root.append(subObj);

	/*数据类型转换												**/
	string sJson = root.toStyledString();

	/*写入文件													**/
	ofstream ofs("./FuncTest/JsonCppOfstreamWrite.json");
	ofs << sJson;
	ofs.close();
}

void funcJsonCppFastWriterWriteFileApiTest()
{
	/*创建Value类型的json根对象									**/
	Value root;

	Value fstSubObj;
	fstSubObj["key1"] = "value1";
	fstSubObj["key11"] = "value11";
	root.append(fstSubObj);

	Value secSubObj;
	secSubObj["key2"] = 2;
	root.append(secSubObj);

	Value thrSubObj;
	thrSubObj["key3"] = true;
	root.append(thrSubObj);

	Value forSubObj;
	forSubObj["key4"] = 4.4;
	root.append(forSubObj);

	/*创建FastWriter对象并生成字符串类型json数据				**/
	FastWriter fWrtr;
	string sJson = fWrtr.write(root);

	/*写入文件													**/
	ofstream ofs("./FuncTest/JsonCppFastWriterWrite.json");
	ofs << sJson;
	ofs.close();
}

/*JsonCpp 读文件 API测试										**/
void funcJsonCppReadFileApiTest()
{
	/*创建流对象，打开json文件									**/
	ifstream ifs("./FuncTest/JsonCppOfstreamWrite.json");

	/*创建Value对象, 存储json数据								**/
	Value root;
	
	/*创建Reader对象, 读取json数据								**/
	Reader jsonFileReader;
	jsonFileReader.parse(ifs, root);

	/*json数据解析												**/
	funcArrayProcess(root);

	/*流对象关闭												**/
	ifs.close();
}

void funcArrayProcess(Value& nodeVec)
{
	for (ValueIterator iter = nodeVec.begin(); iter != nodeVec.end(); iter++)
	{
		Value curSubNode = *iter;
		if (true == curSubNode.isBool())
			cout << "BOOL    : " << curSubNode.asBool() << endl;
		else if (true == curSubNode.isInt())
			cout << "INT     : " << curSubNode.asInt() << endl;
		else if (true == curSubNode.isDouble())
			cout << "DOUBLE  : " << curSubNode.asDouble() << endl;
		else if (true == curSubNode.isString())
			cout << "STRING  : " << curSubNode.asString() << endl;
		else if (true == curSubNode.isObject())
			funcObjectProcess(curSubNode);
		else if (true == curSubNode.isArray())
			funcArrayProcess(curSubNode);
	}
}

void funcObjectProcess(Value& nodeObj)
{
	vector<string> keyNameVec = nodeObj.getMemberNames();
	for (int i = 0; i < keyNameVec.size(); ++i)
	{
		string& keyName = keyNameVec[i];
		cout << "OBJ KEY : " << keyName << endl;
		cout << "OBJ VAL : " << nodeObj[keyName].asString() << endl;
	}
}