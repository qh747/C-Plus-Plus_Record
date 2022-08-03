#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
	int num = 0x12345678;			/*12为高字节, 78为低字节**/
	char* numPtr = (char*)&num;

	cout << "测试本机存储方式: ";
	int cmpNum = 0;
	memcpy(&cmpNum, &numPtr[0], sizeof(char));
	if (0x78 == cmpNum)					/*num在低地址到高地址的顺序中，小端存储方式为：78 56 34 12    **/
	{
		cout << "小端存储." << endl;	/*小端存储为低字节存储在低地址，高字节存储在高地址    **/
	}
	else if (0x12 == cmpNum)			/*num在低地址到高地址的顺序中，大端存储方式为：12 34 56 78    **/
	{
		cout << "大端存储" << endl;		/*大端存储为低字节存储在高地址，高字节存储在低地址    **/
	}
	else
		cout << "错误." << endl;

	cout << "大小端存储转换: ";			/*大小端存储的转换方式为将原本低地址的数据拷贝到高地址中或将原本高地址的数据拷贝到低地址中    **/
	int changeNum = 0;
	char* tmpNumPtr = (char *)&changeNum;
	for (int i = 0; i < 4; ++i)        
	{
		memcpy(&tmpNumPtr[i], &numPtr[3 - i], sizeof(char));
	}
	cout << setbase(16) << changeNum << endl;

	system("pause");
	return 0;
}