#include "WinPcap_BasicTest.h"

int main()
{
	/*WinPcap开发环境测试					**/
	//funcWinPcapEnviromentTest();

	/*查找网卡信息接口函数测试				**/
	//funcFindDevsTest();

	/*显示网卡详细信息测试					**/
	//funcDisplayDevsDetailInfo();

	/*打开网卡, 回调函数形式捕获数据包		**/
	//funcOpenAdapterTest();

	/*打开网卡, 非回调函数形式捕获数据包	**/
	//funcOpenAdapterNonCbTest();

	/*数据包过滤							**/
	//funcPacketFliterTest();

	/*数据包解析							**/
	//funcPacketPraseTest();

	/*数据包存储							**/
	//funcPacketDumpTest();

	/*打开抓包文件							**/
	//funcOpenCaptureFileTest();

	/*发送数据								**/
	funcSendPacketTest();

	system("pause");
	return 0;
}
