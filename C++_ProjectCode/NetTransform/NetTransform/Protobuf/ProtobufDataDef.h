#pragma once
#include <string>

/*请求消息						**/
typedef struct DATA_TYPE_REQUEST_MSG
{
	int				cmdType;		// 报文类型：1.密钥协商  2.密钥校验  3.密钥注销
	std::string		clientId;		// 客户端ID
	std::string		serverId;		// 服务端ID
	std::string		sign;
	std::string		data;
}RequestMsg_dt;


/*响应消息						**/
typedef struct DATA_TYPE_RESPONSE_MSG
{
	bool			status;
	int				seckeyId;
	std::string		clientId;		// 客户端ID
	std::string		serverId;		// 服务端ID
	std::string		data;
}ResponseMsg_dt;
