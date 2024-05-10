#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
using namespace std;

int firstSendTestFunc();

/*发送端代码	**/
int main()
{
	firstSendTestFunc();

	system("pause");
	return 0;
}

int firstSendTestFunc()
{
	int GLOBAL_SIZE = 64;
	string memObjName = "ShareMemory";

	/*创建内存映射对象		**/
	HANDLE hMemObj = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, GLOBAL_SIZE, (LPCWSTR)memObjName.c_str());
	if (NULL == hMemObj)
	{
		cout << "ERROR: CreateFileMapping() - " << GetLastError() << endl;
		return -1;
	}

	/*获取映射数据的地址	**/
	LPVOID pData = MapViewOfFile(hMemObj, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (NULL == pData)
	{
		cout << "ERROR: MapViewOfFile() - " << GetLastError() << endl;
		return -1;
	}

	/*写入数据	  **/
	string shareData = "This Is Share Data.";
	strncpy((char*)pData, shareData.c_str(), shareData.length() + 1);
	cout << "WRITE DATA SUCCESS." << endl;
	cout << "DATA: " << shareData << endl;

	/*解除文件映射		**/
	UnmapViewOfFile(pData);

	/*关闭文件映射句柄, 关闭句柄前需要留出时间给接收数据进程读取数据		**/
	Sleep(5 * 1000);
	CloseHandle(hMemObj);

	return 0;
}