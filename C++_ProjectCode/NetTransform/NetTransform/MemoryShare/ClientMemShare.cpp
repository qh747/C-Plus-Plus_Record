#include "ClientMemShare.h"

ClientMemShare::ClientMemShare(int keyId) : MemoryShare()
{
	m_keyId = -1;

	if (-1 != keyId)
		this->createKeyInfo(keyId);
}

ClientMemShare::~ClientMemShare()
{
	if(-1 != m_keyId)
		this->releaseMemory(m_keyId, 0.1);

	m_keyId = -1;
}

bool ClientMemShare::createKeyInfo(int keyId)
{
	/*客户端共享内存空间已经被创建																		**/
	if (-1 != m_keyId)
	{
		cerr << "KEY INFO HAS BEEN CREATED. KEY ID: " << m_keyId << " FUNC: createKeyInfo()" << endl;
		return false;
	}

	/*客户端共享内存名称创建																			**/
	char memShareName[128] = "\0";
	sprintf(memShareName, "CLIENT_MEMORY_INFO_%d", keyId);
	memShareName[strlen(memShareName)] = '\0';

	/*客户端共享内存空间申请																			**/
	bool allocateResult = false;
	for (int i = 0; i < 3; ++i)
	{
		allocateResult = this->allocateMemory(keyId, memShareName, sizeof(KeyInfo_dt) + 1, 0.1);
		if (true == allocateResult)
		{
			m_keyId = keyId;
			break;
		}
		else
			Sleep(100);
	}

	/*客户端共享内存空间申请失败																		**/
	if(false == allocateResult)
		cerr << "CLIENT KEY INFO ALLOCATE FAILED" << endl;

	return allocateResult;
}

int ClientMemShare::writeKeyInfo(KeyInfo_dt* pKeyInfo)
{
	/*客户端共享内存空间无效																			**/
	if (-1 == m_keyId)
	{
		cerr << "CLIENT KEY INFO IS INVALIED. WRITE FAILED" << endl;
		return -1;
	}

	/*传入参数无效																						**/
	if (NULL == pKeyInfo)
	{
		cerr << "FUNC INPUT PARAM INVALID. FUNC: writeKeyInfo()" << endl;
		return -1;
	}

	/*写入密钥信息																						**/
	DWORD writeSize = 0;
	for (int i = 0; i < 3; ++i)
	{
		writeSize = this->writeData(m_keyId, pKeyInfo, sizeof(KeyInfo_dt), 0, 0.1);
		if (writeSize > 0)
			break;
		else
			Sleep(100);
	}

	/*写入密钥信息失败																					**/
	if (0 == writeSize)
		cerr << "CLIENT KEY INFO WRITE FAILED" << endl;

	return writeSize;
}

int	ClientMemShare::readKeyInfo(KeyInfo_dt* pKeyInfo)
{
	/*客户端共享内存空间无效																			**/
	if(-1 == m_keyId)
	{
		cerr << "CLIENT KEY INFO IS INVALIED. READ FAILED" << endl;
		return -1;
	}

	/*传入参数无效																						**/
	if (NULL == pKeyInfo)
	{
		cerr << "FUNC INPUT PARAM INVALID. FUNC: readKeyInfo()" << endl;
		return -1;
	}

	/*读取密钥信息																						**/
	DWORD readSize = 0;
	for (int i = 0; i < 3; ++i)
	{
		readSize = this->readData(m_keyId, pKeyInfo, sizeof(KeyInfo_dt), 0, 0.1);
		if (readSize > 0)
			break;
		else
			Sleep(100);
	}

	/*读取密钥信息失败																					**/
	if (0 == readSize)
		cerr << "CLIENT KEY INFO READ FAILED" << endl;

	return readSize;
}