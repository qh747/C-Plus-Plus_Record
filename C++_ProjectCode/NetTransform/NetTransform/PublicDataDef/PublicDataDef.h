#pragma once 
#pragma warning(disable: 4996)
#include <cstring>
#include <string>
using std::string;

const int			CLIENT_ID_LENGTH		= 128;								// 客户端ID长度
const int			SERVER_ID_LENGTH		= 128;								// 服务端ID长度
const int			KEY_INFO_LENGTH			= 128;								// 密钥长度
const int			KEY_IN_USE_STATE		= 1;								// 密钥可用
const int			KEY_IN_UNUSE_STATE		= 0;								// 密钥不可用
const int			SERVER_IP_LENGTH		= 32;								// 服务端IP地址长度
const int			DB_IP_LENGTH			= 32;								// 数据库IP长度
const int			DB_NAME_LENGTH			= 64;								// 数据库名称长度
const int			DB_USER_LENGTH			= 64;								// 数据库用户名称
const int			DB_PASSWD_LENGTH		= 64;								// 数据库密码长度
const int			DB_TBLNAME_LENGTH		= 64;								// 数据表名称
const string		DB_COLU_CLIENT_ID		= "ClientId";						// 数据库字段 客户端ID
const string		DB_COLU_SERVER_ID		= "ServerId";						// 数据库字段 服务端ID
const string		DB_COLU_KEY_INFO		= "KeyInfo";						// 数据库字段 密钥数据
const string		DB_COLU_KEY_STATUS		= "KeyStatus";						// 数据库字段 密钥状态
const string		DB_COLU_KEY_ID			= "KeyId";							// 数据库字段 密钥ID


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


/*数据库信息																	**/
typedef struct DATA_TYPE_DATABASE_CONFIGURE
{
	char			sDBIpAddr[DB_IP_LENGTH];									// 数据库IP
	char			sDBUserName[DB_USER_LENGTH];								// 数据库用户名称
	char			sDBUserPasswd[DB_PASSWD_LENGTH];							// 数据库密码
	char			sDBName[DB_NAME_LENGTH];									// 数据库名称
	char			sDBTblName[DB_TBLNAME_LENGTH];								// 数据表名称
	int				iDBPort;													// 数据库端口

	DATA_TYPE_DATABASE_CONFIGURE()
	{
		memset(this, 0, sizeof(DATA_TYPE_DATABASE_CONFIGURE));
	}
}DBJsConf_dt;


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