#pragma once
#pragma warning(disable: 4996)
#include <openssl\rsa.h>
#include <openssl\pem.h>
#include <openssl\bio.h>
#include <openssl\err.h>
#include <openssl/buffer.h>
#include <string>
#include <iostream>
using namespace std;

class RsaEncrypt
{
public:
	typedef enum TYPE_SIGN_LEVEL																		// RSA签名等级
	{
		SIGN_LEVEL1 = NID_md5,
		SIGN_LEVEL2 = NID_sha1,
		SIGN_LEVEL3 = NID_sha224,
		SIGN_LEVEL4 = NID_sha256,
		SIGN_LEVEL5 = NID_sha384,
		SIGN_LEVEL6 = NID_sha512
	}SignLevel_t;

public:
	RsaEncrypt();																						// 构造函数
	virtual ~RsaEncrypt();																				// 析构函数

public:
	bool	generateRsaKey(int bits, const string& pubKeyFileName, const string& priKeyFileName);		// 生成RSA密钥对
	bool	prasePubKeyFromFile(const string& pubKeyFileName);											// 从文件中解析公钥
	bool	prasePriKeyFromFile(const string& priKeyFileName);											// 从文件中解析私钥

	string	encryptByPubKey(const string& origData);													// 使用公钥加密
	string  decryptByPriKey(const string& encryptData);													// 使用私钥解密

	string	sign(const string& data, SignLevel_t level);												// 签名(使用私钥)
	bool	signVerify(const string& data, const string& signData, SignLevel_t level);					// 签名验证(使用公钥)

private:
	string	encodeByBase64(const string& data, int size);												// 使用Base64编码
	string	decodeByBase64(const string& encodeData);													// 使用Base64解码

private:
	RSA*	m_pPrivateRsaKey;																			// RSA私钥
	RSA*	m_pPublicRsaKey;																			// RSA公钥
};
