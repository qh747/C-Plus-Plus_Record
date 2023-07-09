#pragma once 
#pragma warning(disable: 4996)
#include <cstring>
#include <string>
using std::string;

const int CLIENT_ID_LENGTH		= 128;											// 客户端ID长度
const int SERVER_ID_LENGTH		= 128;											// 服务端ID长度
const int KEY_INFO_LENGTH		= 128;											// 密钥长度
const int KEY_IN_USE_STATE		= 1;											// 密钥可用
const int KEY_IN_UNUSE_STATE	= 0;											// 密钥不可用
const int SERVER_IP_LENGTH		= 32;											// 服务端IP地址长度


/*序列化数据类型																**/
typedef enum TYPE_SERIAL
{
	SERIAL_TYPE		= 1,														// 序列化类型
	UNSERIAL_TYPE	= 2,														// 未序列化类型
}Serial_t;


/*密钥信息																		**/
typedef struct DATA_TYPE_KEY_INFO
{
	char			sClientId[CLIENT_ID_LENGTH];								// 客户端ID
	char			sServerId[SERVER_ID_LENGTH];								// 服务端ID
	char			sKeyInfo[KEY_INFO_LENGTH];									// 服务端密钥
	int				iKetStatus;													// 密钥状态
	int				iKeyId;														// 密钥ID

	DATA_TYPE_KEY_INFO()
	{
		memset(this, 0, sizeof(DATA_TYPE_KEY_INFO));
	}
}KeyInfo_dt;


/*客户端配置信息																**/
typedef struct DATA_TYPE_CLIENT_JSON_CONFIGURE
{
	char			sClientId[CLIENT_ID_LENGTH];								// 客户端ID
	char			sServerId[SERVER_ID_LENGTH];								// 服务端ID
	char			sServerIp[SERVER_IP_LENGTH];								// 服务端IP
	int				iServerPort;												// 服务端端口
	int				iClientMemShareId;											// 客户端内存映射ID

	DATA_TYPE_CLIENT_JSON_CONFIGURE()
	{
		memset(this, 0, sizeof(DATA_TYPE_CLIENT_JSON_CONFIGURE));
	}
}ClitJsConf_dt;


/*请求消息																		**/
typedef struct DATA_TYPE_REQUEST_MSG
{
	int				iCmdType;													// 报文类型：1.密钥协商  2.密钥校验  3.密钥注销
	std::string		sClientId;													// 客户端ID
	std::string		sServerId;													// 服务端ID
	std::string		sSign;														// 签名数据
	std::string		sData;														// 原始数据

	DATA_TYPE_REQUEST_MSG() : sClientId(""), sServerId(""), sSign(""), sData("")
	{
		iCmdType	= -1;
	}
}RequestMsg_dt;


/*响应消息																		**/
typedef struct DATA_TYPE_RESPONSE_MSG
{
	bool			bStatus;													// 服务端密钥状态
	int				iSeckeyId;													// 服务端密钥ID
	std::string		sClientId;													// 客户端ID
	std::string		sServerId;													// 服务端ID
	std::string		sData;														// 服务端密钥

	DATA_TYPE_RESPONSE_MSG() : sClientId(""), sServerId(""), sData("")
	{
		bStatus		= false;
		iSeckeyId	= -1;
	}
}ResponseMsg_dt;