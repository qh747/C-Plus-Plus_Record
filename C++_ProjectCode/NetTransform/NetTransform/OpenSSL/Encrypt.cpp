#include "Encrypt.h"

Encrypt::Encrypt(Encrypt_t type)
{
	this->initEncryptStruct(type);
}

Encrypt::~Encrypt()
{
	this->releaseEncryptStruct(this->m_type);
}

bool Encrypt::addOriginalData(const string& data, size_t dataSize)
{
	bool encryptResult = true;
	switch (this->m_type)
	{
		case TYPE_MD4:
		{
			MD4_CTX* pCtx = static_cast<MD4_CTX *>(this->m_pEncrtpyStruct);
			MD4_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_MD5:
		{
			MD5_CTX* pCtx = static_cast<MD5_CTX *>(this->m_pEncrtpyStruct);
			MD5_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_SHA1:
		{
			SHA_CTX* pCtx = static_cast<SHA_CTX *>(this->m_pEncrtpyStruct);
			SHA1_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_SHA224:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
			SHA224_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_SHA256:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
			SHA256_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_SHA384:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
			SHA384_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		case TYPE_SHA512:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
			SHA512_Update(pCtx, data.c_str(), dataSize);
			break;
		}
		default:
			encryptResult = false;
	}
	return encryptResult;
}

string Encrypt::getEncryptData()
{
	string resultData;
	switch (this->m_type)
	{
	case TYPE_MD4:
	{
		MD4_CTX* pCtx = static_cast<MD4_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[MD4_DIGEST_LENGTH] = "\0";
		MD4_Final(buf, pCtx);
		
		resultData = (char *)buf;
		resultData[MD4_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_MD5:
	{
		MD5_CTX* pCtx = static_cast<MD5_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[MD5_DIGEST_LENGTH] = "\0";
		MD5_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[MD5_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_SHA1:
	{
		SHA_CTX* pCtx = static_cast<SHA_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[SHA_DIGEST_LENGTH] = "\0";
		SHA1_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[SHA_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_SHA224:
	{
		SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[SHA224_DIGEST_LENGTH] = "\0";
		SHA224_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[SHA224_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_SHA256:
	{
		SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[SHA256_DIGEST_LENGTH] = "\0";
		SHA256_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[SHA256_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_SHA384:
	{
		SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[SHA384_DIGEST_LENGTH] = "\0";
		SHA384_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[SHA384_DIGEST_LENGTH] = '\0';
		break;
	}
	case TYPE_SHA512:
	{
		SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
		unsigned char buf[SHA512_DIGEST_LENGTH] = "\0";
		SHA512_Final(buf, pCtx);

		resultData = (char *)buf;
		resultData[SHA512_DIGEST_LENGTH] = '\0';
		break;
	}
	default:
		resultData = "";
	}
	return resultData;
}

string Encrypt::getEncryptHexData()
{
	string resultData;
	switch (this->m_type)
	{
		case TYPE_MD4:
		{
			MD4_CTX* pCtx = static_cast<MD4_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[MD4_DIGEST_LENGTH] = "\0";
			MD4_Final(buf, pCtx);

			resultData.resize(MD4_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < MD4_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[MD4_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_MD5:
		{
			MD5_CTX* pCtx = static_cast<MD5_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[MD5_DIGEST_LENGTH] = "\0";
			MD5_Final(buf, pCtx);

			resultData.resize(MD5_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[MD5_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_SHA1:
		{
			SHA_CTX* pCtx = static_cast<SHA_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[SHA_DIGEST_LENGTH] = "\0";
			SHA1_Final(buf, pCtx);

			resultData.resize(SHA_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[SHA_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_SHA224:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[SHA224_DIGEST_LENGTH] = "\0";
			SHA224_Final(buf, pCtx);

			resultData.resize(SHA224_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < SHA224_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[SHA224_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_SHA256:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[SHA256_DIGEST_LENGTH] = "\0";
			SHA256_Final(buf, pCtx);

			resultData.resize(SHA256_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[SHA256_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_SHA384:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[SHA384_DIGEST_LENGTH] = "\0";
			SHA384_Final(buf, pCtx);

			resultData.resize(SHA384_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < SHA384_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[SHA384_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		case TYPE_SHA512:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(this->m_pEncrtpyStruct);
			unsigned char buf[SHA512_DIGEST_LENGTH] = "\0";
			SHA512_Final(buf, pCtx);

			resultData.resize(SHA512_DIGEST_LENGTH * 2 + 1);
			for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i)
			{
				sprintf((char *)&(resultData[i * 2]), "%02x", buf[i]);
			}
			resultData[SHA512_DIGEST_LENGTH * 2] = '\0';
			break;
		}
		default:
			resultData = "";
		}
	return resultData;
}

void Encrypt::initEncryptStruct(Encrypt_t type)
{
	switch (type)
	{
		case TYPE_MD4:
		{
			MD4_CTX* pCtx = new MD4_CTX();
			MD4_Init(pCtx);
			m_type = TYPE_MD4;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_MD5:
		{
			MD5_CTX* pCtx = new MD5_CTX();
			MD5_Init(pCtx);
			m_type = TYPE_MD5;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_SHA1:
		{
			SHA_CTX* pCtx = new SHA_CTX();
			SHA1_Init(pCtx);
			m_type = TYPE_SHA1;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_SHA224:
		{
			SHA256_CTX* pCtx = new SHA256_CTX();
			SHA224_Init(pCtx);
			m_type = TYPE_SHA224;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_SHA256:
		{
			SHA256_CTX* pCtx = new SHA256_CTX();
			SHA256_Init(pCtx);
			m_type = TYPE_SHA256;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_SHA384:
		{
			SHA512_CTX* pCtx = new SHA512_CTX();
			SHA384_Init(pCtx);
			m_type = TYPE_SHA384;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		case TYPE_SHA512:
		{
			SHA512_CTX* pCtx = new SHA512_CTX();
			SHA512_Init(pCtx);
			m_type = TYPE_SHA512;
			m_pEncrtpyStruct = pCtx;
			break;
		}
		default:
		{
			/*初始化默认加密结构体				**/
			this->initDftEncryptStruct();
		}
	}
}

void Encrypt::releaseEncryptStruct(Encrypt_t type)
{
	switch (type)
	{
		case TYPE_MD4:
		{
			MD4_CTX* pCtx = static_cast<MD4_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_MD5:
		{
			MD5_CTX* pCtx = static_cast<MD5_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_SHA1:
		{
			SHA_CTX* pCtx = static_cast<SHA_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_SHA224:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_SHA256:
		{
			SHA256_CTX* pCtx = static_cast<SHA256_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_SHA384:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		case TYPE_SHA512:
		{
			SHA512_CTX* pCtx = static_cast<SHA512_CTX *>(m_pEncrtpyStruct);
			delete pCtx;
			break;
		}
		default:
		{
			/*销毁默认加密结构体				**/
			this->releaseDftEncryptStruct();
		}
	}
}

void Encrypt::initDftEncryptStruct()
{
	/*默认使用MD5加密方式						**/
	MD5_CTX* pCtx = new MD5_CTX();
	MD5_Init(pCtx);

	m_type = TYPE_MD5;
	m_pEncrtpyStruct = pCtx;
}

void Encrypt::releaseDftEncryptStruct()
{
	/*默认使用MD5加密方式						**/
	MD5_CTX* pCtx = static_cast<MD5_CTX *>(m_pEncrtpyStruct);
	delete pCtx;
}