#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <openssl\md4.h>
#include <openssl\md5.h>
#include <openssl\sha.h>
using namespace std;

/*加密类																		**/
class Encrypt
{
public:
	typedef enum TYPE_ENCRYPT													// 加密类型
	{
		TYPE_MD4			= 0,												// MD4加密
		TYPE_MD5			= 1,												// MD5加密
		TYPE_SHA1			= 2,												// SHA1加密
		TYPE_SHA224			= 3,												// SHA224加密
		TYPE_SHA256			= 4,												// SHA256加密
		TYPE_SHA384			= 5,												// SHA384加密
		TYPE_SHA512			= 6,												// SHA512加密
	}Encrypt_t;

public:
	Encrypt(Encrypt_t type);													// 构造函数
	virtual ~Encrypt();															// 析构函数

public:
	bool			addOriginalData(const string& data, size_t dataSize);		// 添加原始数据
	string			getEncryptData();											// 获得加密数据(原始数据为二进制)
	string			getEncryptHexData();										// 获得十六进制加密数据

private:
	void			initEncryptStruct(Encrypt_t type);							// 初始化加密结构体
	void			releaseEncryptStruct(Encrypt_t type);						// 销毁加密结构体
	void			initDftEncryptStruct();										// 初始化默认加密结构体
	void			releaseDftEncryptStruct();									// 销毁默认加密结构体

private:
	Encrypt_t		m_type;														// 加密类型
	void*			m_pEncrtpyStruct;											// 加密哈希结构体
};