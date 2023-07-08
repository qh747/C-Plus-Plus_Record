#pragma once 
#pragma warning(disable: 4996)
#include <cstring>

const int CLIENT_ID_LENGTH		= 128;											// 客户端ID长度
const int SERVER_ID_LENGTH		= 128;											// 服务端ID长度
const int KEY_INFO_LENGTH		= 128;											// 密钥长度
const int KEY_IN_USE_STATE		= 1;											// 密钥可用
const int KEY_IN_UNUSE_STATE	= 0;											// 密钥不可用

/*密钥信息																		**/
typedef struct DATA_TYPE_KEY_INFO
{
	char			sClientId[CLIENT_ID_LENGTH];
	char			sServerId[SERVER_ID_LENGTH];
	char			sKeyInfo[KEY_INFO_LENGTH];
	int				iKetStatus;
	int				iKeyId;

	DATA_TYPE_KEY_INFO()
	{
		memset(this, 0, sizeof(DATA_TYPE_KEY_INFO));
	}
}KeyInfo_dt;