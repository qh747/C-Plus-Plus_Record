#pragma once
#pragma warning(disable: 4996)

// 宏定义WIN32, 否则会默认调用Linux系统的库
#define WIN32

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <pcap.h>
#include "WinPcapDataDef.h"
using namespace std;

/*开发环境配置测试						**/
void funcWinPcapEnviromentTest();

/*查找网卡信息接口函数测试				**/
void funcFindDevsTest();

/*显示网卡详细信息测试					**/
void funcDisplayDevsDetailInfo();
string funcIPIntToStr(u_long pAddr);

/*打开网卡, 回调函数形式捕获数据包		**/
void funcOpenAdapterTest();
void funcOpenCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

/*打开网卡, 非回调函数形式捕获数据包	**/
void funcOpenAdapterNonCbTest();

/*数据包过滤							**/
void funcPacketFliterTest();
void funcPacketFliterTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

/*数据包解析							**/
void funcPacketPraseTest();
void funcPacketPraseTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

/*数据包存储							**/
void funcPacketDumpTest();
void funcPacketDumpTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

/*打开抓包文件							**/
void funcOpenCaptureFileTest();
void funcOpenCaptureFileTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

/*发送数据								**/
void funcSendPacketTest();
void funcSendPacketTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);