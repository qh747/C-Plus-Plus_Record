#include "MemoryShare.h"

map<int, MemShareStruct_dt>		MemoryShare::GBLMemManageMap;					// 共享内存管理map
HANDLE							MemoryShare::GBLMemManageMapMutex =  NULL;		// 共享内存管理map互斥量
atomic<unsigned long>			MemoryShare::GBLMemoryShareObjects = 0;			// 共享内存类对象记录

MemoryShare::MemoryShare()
{
	bool createResult = MemoryShare::CREATEMemManageMapMutex();
	if (false == createResult)
	{
		cerr << "MEMORY SHARE INIT FAILED." << endl;
		this->setMemoryShareState(false);
	}
	else
	{
		this->setMemoryShareState(true);
		MemoryShare::ADDMemoryShareObject();
	}
}

MemoryShare::~MemoryShare()
{
	if (false == this->getMemoryShareState())
		return;
	else
		MemoryShare::REDUCEMemoryShareObject();
}

bool MemoryShare::allocateMemory(int id, const char* name, DWORD size, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return false;
	}
	
	if (id < 0 || NULL == name || 0 == size || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: allocateMemory()" << endl;
		return false;
	}

	bool allocateResult = MemoryShare::ALLOCATEMemory(id, name, size, sec);
	return allocateResult;
}

bool MemoryShare::releaseMemory(int id, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return false;
	}

	if (id < 0 || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: releaseMemory()" << endl;
		return false;
	}

	bool releaseResult = MemoryShare::RELEASEMemory(id, sec);
	return releaseResult;
}

bool MemoryShare::clearMemory(int id, DWORD pos, DWORD clearSize, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return false;
	}

	if (id < 0 || 0 == clearSize || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: clearMemory()" << endl;
		return false;
	}

	bool clearResult = MemoryShare::CLEARMemory(id, pos, clearSize, sec);
	return clearResult;
}

DWORD MemoryShare::getMemorySize(int id, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return 0;
	}

	if (id < 0 || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: getMemorySize()" << endl;
		return 0;
	}

	DWORD size = MemoryShare::GETMemorySize(id, sec);
	return size;
}

DWORD MemoryShare::writeData(int id, void* pData, DWORD dataSize, DWORD pos, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return 0;
	}

	if (id < 0 || NULL == pData || 0 == dataSize || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: writeData()" << endl;
		return 0;
	}

	DWORD writeSize = MemoryShare::WRITEMemory(id, pData, dataSize, pos, sec);
	return writeSize;
}

DWORD MemoryShare::readData(int id, void* pData, DWORD dataSize, DWORD pos, double sec)
{
	if (false == this->getMemoryShareState())
	{
		cerr << "MEMORY SHARE CAN NOT BE USED." << endl;
		return 0;
	}

	if (id < 0 || NULL == pData || 0 == dataSize || sec <= 0)
	{
		cerr << "FUNC INPUT PARAM ERROR. FUNC: readData()" << endl;
		return 0;
	}

	DWORD readSize = MemoryShare::READMemory(id, pData, dataSize, pos, sec);
	return readSize;
}

void MemoryShare::setMemoryShareState(bool state)
{
	m_memoryShareState = state;
}

bool MemoryShare::getMemoryShareState()
{
	return m_memoryShareState;
}

DWORD MemoryShare::GETMemorySize(int id, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(sec))
		return 0;

	DWORD size = 0;
	map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
	if (GBLMemManageMap.end() != findIter)
		size = findIter->second.ulMemSize;
	else
		cerr << "CAN NOT FIND ID. FUNC: GETMemorySize()" << endl;

	MemoryShare::UNLOCKMemManageMapMutex();
	return size;
}

DWORD MemoryShare::WRITEMemory(int id, void* pData, DWORD dataSize, DWORD pos, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(sec))
		return 0;

	DWORD size = 0;
	map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
	if (GBLMemManageMap.end() != findIter)
	{
		if (findIter->second.ulMemSize > pos + dataSize)
		{
			char* pDataBuf = static_cast<char *>(findIter->second.pMemory);
			memcpy(pDataBuf + pos, pData, dataSize);
			size = dataSize;
		}
		else
			cerr << "WRITE SIZE OVERFLOW. FUNC: WRITEMemory()" << endl;
	}
	else
		cerr << "CAN NOT FIND ID. FUNC: WRITEMemory()" << endl;

	MemoryShare::UNLOCKMemManageMapMutex();
	return size;
}

DWORD MemoryShare::READMemory(int id, void* pData, DWORD dataSize, DWORD pos, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(sec))
		return 0;

	DWORD size = 0;
	map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
	if (GBLMemManageMap.end() != findIter)
	{
		if (findIter->second.ulMemSize > pos + dataSize)
		{
			char* pDataBuf = static_cast<char *>(findIter->second.pMemory);
			memcpy(pData, pDataBuf + pos, dataSize);
			size = dataSize;
		}
		else
			cerr << "READ SIZE OVERFLOW. FUNC: READMemory()" << endl;
	}
	else
		cerr << "CAN NOT FIND ID. FUNC: READMemory()" << endl;

	MemoryShare::UNLOCKMemManageMapMutex();
	return size;
}

bool MemoryShare::CLEARMemory(int id, DWORD pos, DWORD clearSize, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(sec))
		return false;

	map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
	if (GBLMemManageMap.end() != findIter)
	{
		if (findIter->second.ulMemSize > pos + clearSize)
		{
			char* pDataBuf = static_cast<char *>(findIter->second.pMemory);
			memset(pDataBuf + pos, 0, clearSize);
		}
		else
			cerr << "CLEAR SIZE OVERFLOW. FUNC: CLEARMemory()" << endl;
	}
	else
		cerr << "CAN NOT FIND ID. FUNC: CLEARMemory()" << endl;

	MemoryShare::UNLOCKMemManageMapMutex();
	return true;
}

void MemoryShare::CLEARMemManageMap()
{
	if (false == MemoryShare::LOCKMemManageMapMutex(0.1))
		return;

	if (false == GBLMemManageMap.empty())
	{
		for (map<int, MemShareStruct_dt>::iterator iter = GBLMemManageMap.begin(); iter != GBLMemManageMap.end(); iter++)
		{
			MemShareStruct_dt& memShare = iter->second;

			UnmapViewOfFile(memShare.pMemory);
			CloseHandle(memShare.pMemHandle);
		}
		GBLMemManageMap.clear();
	}

	MemoryShare::UNLOCKMemManageMapMutex();
}

bool MemoryShare::ALLOCATEMemory(int id, const char* name, DWORD size, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(sec))
		return false;

	map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
	if (GBLMemManageMap.end() == findIter)
	{
		/*创建共享内存																**/
		HANDLE memHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, (LPCSTR)name);
		if (NULL == memHandle)
		{
			/*共享内存创建失败														**/
			cerr << "FUNC ERROR: CreateFileMapping(). ERR CODE: " << GetLastError() << endl;

			MemoryShare::UNLOCKMemManageMapMutex();
			return false;
		}

		/*内存映射																	**/
		LPVOID pMemory = MapViewOfFile(memHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (NULL == pMemory)
		{
			/*内存映射失败															**/
			cerr << "FUNC ERROR: MapViewOfFile(). ERR CODE: " << GetLastError() << endl;
			CloseHandle(memHandle);

			MemoryShare::UNLOCKMemManageMapMutex();
			return false;
		}

		/*共享内存数据创建															**/
		MemShareStruct_dt memShare;
		memShare.iMemId = id;
		memShare.sMemName = name;
		memShare.pMemHandle = memHandle;
		memShare.pMemory = pMemory;
		memShare.ulMemSize = size;

		/*插入共享内存数据															**/
		GBLMemManageMap.insert(make_pair(id, memShare));
	}

	MemoryShare::UNLOCKMemManageMapMutex();
	return true;
}

bool MemoryShare::RELEASEMemory(int id, double sec)
{
	if (false == MemoryShare::LOCKMemManageMapMutex(0.1))
		return false;

	if (false == GBLMemManageMap.empty())
	{
		map<int, MemShareStruct_dt>::iterator findIter = GBLMemManageMap.find(id);
		if (GBLMemManageMap.end() != findIter)
		{
			MemShareStruct_dt& memShare = findIter->second;

			UnmapViewOfFile(memShare.pMemory);
			CloseHandle(memShare.pMemHandle);

			GBLMemManageMap.erase(findIter);
		}
		else
			cerr << "CAN NOT FIND ID. FUNC: RELEASEMemory()" << endl;
	}
	else
		cerr << "MEMORY MANAGE MAP IS EMPTY. FUNC: RELEASEMemory()" << endl;

	MemoryShare::UNLOCKMemManageMapMutex();
	return true;
}

bool MemoryShare::CREATEMemManageMapMutex()
{
	if (NULL == GBLMemManageMapMutex)
	{
		/*创建互斥量句柄							**/
		GBLMemManageMapMutex = CreateMutex(NULL, FALSE, (LPCSTR)"MUTEX_NAME");
	}

	if (NULL == GBLMemManageMapMutex)
	{
		cerr << "CREATE MEMORY SHARE LOCK FAILED. ERR CODE: " << GetLastError() << endl;
		return false;
	}
	else
		return true;
}

bool MemoryShare::RELEASEMemManageMapMutex()
{
	if (NULL != GBLMemManageMapMutex)
	{
		bool closeResult = CloseHandle(GBLMemManageMapMutex);
		GBLMemManageMapMutex = NULL;
		return closeResult;
	}
	else
		return true;
}

bool MemoryShare::LOCKMemManageMapMutex(double sec)
{
	DWORD waitResult = WaitForSingleObject(GBLMemManageMapMutex, sec * 1000);
	if (WAIT_FAILED == waitResult)
	{
		cerr << "LOCK FAILED. ERR CODE: " << GetLastError() << endl;
		return false;
	}
	else if (WAIT_TIMEOUT == waitResult)
	{
		cerr << "LOCK TIMEOUT. ERR CODE: " << GetLastError() << endl;
		return false;
	}
	else
		return true;
}

bool MemoryShare::UNLOCKMemManageMapMutex()
{
	return ReleaseMutex(GBLMemManageMapMutex);
}

void MemoryShare::ADDMemoryShareObject()
{
	++GBLMemoryShareObjects;
}

void MemoryShare::REDUCEMemoryShareObject()
{
	--GBLMemoryShareObjects;

	if (GBLMemoryShareObjects <= 0)
	{
		MemoryShare::CLEARMemManageMap();
		MemoryShare::RELEASEMemManageMapMutex();
	}
}