#pragma once
#include <WinSock2.h>

/*IP地址结构										**/
typedef struct DATA_TYPE_IP_ADDRESS
{
	u_char		ucByteFst;
	u_char		ucByteSec;
	u_char		ucByteTrd;
	u_char		ucByteFrth;

}IPAddress_dt;


/*IP首部结构										**/
typedef struct DATA_TYPE_IP_HEADER
{
	u_char			ucVersionAndLength;				// 版本 + 首部长度
	u_char			ucTos;							// 服务质量
	u_short			usTotalLength;					// IP数据总长度
	u_short			usIdentification;				// 标识
	u_short			usFlagAndFragmentOffset;		// 标志位 + 段偏移量
	u_char			ucTtl;							// 生命周期
	u_char			ucProto;						// 协议类型
	u_short			ucCrc;							// 循环校验码
	IPAddress_dt	ipSrcAddr;						// IP源地址
	IPAddress_dt	ipDstAddr;						// IP目的地址
	u_int			uiOption;						// 选项

}IPHeader_dt;


/*UDP首部											**/
typedef struct DATA_TYPE_UDP_HEADER
{
	u_short			usSrcPort;						// UDP源端口
	u_short			usDstPort;						// UDP目的端口
	u_short			usLength;						// UDP数据长度
	u_short			usCrc;							// 循环校验码

}UDPHeader_dt;


/*发送数据结构										**/
typedef struct DATA_TYPE_SEND_DATA
{
	char*			pData;
	int				iDataSize;

}SendData_dt;