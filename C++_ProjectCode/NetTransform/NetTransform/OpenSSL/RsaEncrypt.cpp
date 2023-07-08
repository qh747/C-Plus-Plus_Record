#include "RsaEncrypt.h"
extern "C" 
{ 
	#include <openssl\applink.c> 
};

RsaEncrypt::RsaEncrypt()
{
	m_pPrivateRsaKey = NULL;
	m_pPublicRsaKey = NULL;
}

RsaEncrypt::~RsaEncrypt()
{
	if (NULL != m_pPrivateRsaKey)
	{
		RSA_free(m_pPrivateRsaKey);
		m_pPrivateRsaKey = NULL;
	}

	if(NULL != m_pPublicRsaKey)
	{
		RSA_free(m_pPublicRsaKey);
		m_pPublicRsaKey = NULL;
	}
}

bool RsaEncrypt::generateRsaKey(int bits, const string& pubKeyFileName, const string& priKeyFileName)
{
	if (bits <= 0 || true == pubKeyFileName.empty() || true == priKeyFileName.empty())
	{
		cerr << "FUNC INPUT PARAM INVALID. FUNC: generateRsaKey()" << endl;
		return false;
	}

	/*生成RSA密钥对																									**/
	RSA* pRsa = RSA_new();
	BIGNUM* pBigNum = BN_new();
	BN_set_word(pBigNum, RSA_F4);
	int generateResult = RSA_generate_key_ex(pRsa, bits, pBigNum, NULL);

	/*RSA密钥对生成错误																								**/
	if (0 == generateResult)
	{
		cerr << "RSA GENERATE KEY FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;

		RSA_free(pRsa);
		BN_free(pBigNum);
		return false;
	}

	/*写入RSA公钥																									**/
	FILE* pPubFileHnadle = fopen(pubKeyFileName.c_str(), "wb");
	int pubWriteResult = PEM_write_RSAPublicKey(pPubFileHnadle, pRsa);

	FILE* pPriFileHnadle = fopen(priKeyFileName.c_str(), "wb");
	int priWriteResult = PEM_write_RSAPrivateKey(pPriFileHnadle, pRsa, NULL, NULL, 0, NULL, NULL);

	/*密钥拷贝																										**/
	m_pPrivateRsaKey = RSAPrivateKey_dup(pRsa);
	m_pPublicRsaKey = RSAPublicKey_dup(pRsa);

	/*释放内存空间																									**/
	RSA_free(pRsa);
	BN_free(pBigNum);
	fclose(pPubFileHnadle);
	fclose(pPriFileHnadle);
	return true;
}

bool RsaEncrypt::prasePubKeyFromFile(const string& pubKeyFileName)
{
	FILE* pPubFileHnadle = fopen(pubKeyFileName.c_str(), "rb");
	if (NULL == PEM_read_RSAPublicKey(pPubFileHnadle, &m_pPublicRsaKey, NULL, NULL))
	{
		cerr << "RSA PRASE PUBLIC KEY FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;

		fclose(pPubFileHnadle);
		return false;
	}

	fclose(pPubFileHnadle);
	return true;
}

bool RsaEncrypt::prasePriKeyFromFile(const string& priKeyFileName)
{
	FILE* pPriFileHnadle = fopen(priKeyFileName.c_str(), "rb");
	if (NULL == PEM_read_RSAPrivateKey(pPriFileHnadle, &m_pPrivateRsaKey, NULL, NULL))
	{
		cerr << "RSA PRASE PRIVATE KEY FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;

		fclose(pPriFileHnadle);
		return false;
	}

	fclose(pPriFileHnadle);
	return true;
}

string RsaEncrypt::encryptByPubKey(const string& origData)
{
	if (NULL == m_pPublicRsaKey)
	{
		cerr << "RSA PUBLIC KEY IS INVALID, ENCRYPT FAILED" << endl;
		return false;
	}

	/*数据加密																										**/
	char* pBuffer = new char[RSA_size(m_pPublicRsaKey) + 1];
	int encryptSize = RSA_public_encrypt(origData.size(), (const unsigned char *)origData.data(), (unsigned char *)pBuffer, m_pPublicRsaKey, RSA_PKCS1_PADDING);
	pBuffer[encryptSize] = '\0';

	/*数据Base64编码																								**/
	string baseEncryptData = this->encodeByBase64(pBuffer, encryptSize);

	delete[] pBuffer;
	return baseEncryptData;
}

string RsaEncrypt::decryptByPriKey(const string& encryptData)
{
	if (NULL == m_pPrivateRsaKey)
	{
		cerr << "RSA PRIVATE KEY IS INVALID, DECRYPT FAILED" << endl;
		return "";
	}

	/*数据Base64解码																								**/
	string decodeData = this->decodeByBase64(encryptData);

	int dataSize = RSA_size(m_pPrivateRsaKey);
	char* pBuffer = new char[dataSize + 1];

	/*数据解密																										**/
	int decryptSize = RSA_private_decrypt(dataSize, (const unsigned char *)decodeData.data(), (unsigned char *)pBuffer, m_pPrivateRsaKey, RSA_PKCS1_PADDING);
	
	string resultData("");
	if (-1 == decryptSize)
		cerr << "RSA DECRYPT FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;
	else
		resultData = string(pBuffer, decryptSize);

	delete[] pBuffer;
	return resultData;
}

string RsaEncrypt::sign(const string& data, SignLevel_t level)
{
	if (NULL == m_pPrivateRsaKey)
	{
		cerr << "RSA PRIVATE KEY IS INVALID, SIGN FAILED" << endl;
		return "";
	}

	/*数据签名																										**/
	char* pBuffer = new char[RSA_size(m_pPrivateRsaKey)];
	int signSize = 0;
	int signResult = RSA_sign(level, (const unsigned char *)data.data(), data.size(), (unsigned char *)pBuffer, (unsigned int *)&signSize, m_pPrivateRsaKey);

	/*数据Base64编码																								**/
	string baseEncryptData("");
	if (1 != signResult)
		cerr << "RSA SIGN FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;
	else
		baseEncryptData = this->encodeByBase64(pBuffer, signSize);

	delete[] pBuffer;
	return baseEncryptData;
}

bool RsaEncrypt::signVerify(const string& data, const string& signData, SignLevel_t level)
{
	if (NULL == m_pPublicRsaKey)
	{
		cerr << "RSA PUBLIC KEY IS INVALID, VERIFY FAILED" << endl;
		return false;
	}

	/*数据Base64解码																								**/
	string decodeData = this->decodeByBase64(signData);
	
	/*数据签名验证																									**/
	int verifyResult = RSA_verify(level, (const unsigned char *)data.data(), data.size(), (const unsigned char *)decodeData.data(), RSA_size(m_pPublicRsaKey), m_pPublicRsaKey);

	/*数据签名验证比对																								**/
	if (1 == verifyResult)
		return true;
	else
		return false;
}

string RsaEncrypt::encodeByBase64(const string& data, int size)
{
	BIO* pCodec = BIO_new(BIO_f_base64());
	BIO* pCodecMem = BIO_new(BIO_s_mem());
	BIO_push(pCodec, pCodecMem);

	BIO_write(pCodec, data.c_str(), size);
	BIO_flush(pCodec);

	BUF_MEM* pCodecBuf = NULL;
	BIO_get_mem_ptr(pCodec, &pCodecBuf);

	string buffer = string(pCodecBuf->data, pCodecBuf->length - 1);

	BIO_free_all(pCodec);
	return buffer;
}

string RsaEncrypt::decodeByBase64(const string& encodeData)
{
	int encodeDataSize = encodeData.size();
	BIO* pDeCodec = BIO_new(BIO_f_base64());
	BIO* pDecodecMem = BIO_new_mem_buf(encodeData.c_str(), encodeDataSize);
	BIO_push(pDeCodec, pDecodecMem);

	char* pBuffer = new char[encodeDataSize];
	memset(pBuffer, 0, encodeDataSize);
	int readLen = BIO_read(pDeCodec, pBuffer, encodeDataSize);

	string resultData("");
	if (-1 == readLen)
		cerr << "RSA BASE64 DECODE FAILED. ERR INFO: " << ERR_error_string(ERR_get_error(), NULL) << endl;
	else
		resultData = string(pBuffer, readLen);

	BIO_free_all(pDeCodec);
	delete[] pBuffer;
	return resultData;
}
