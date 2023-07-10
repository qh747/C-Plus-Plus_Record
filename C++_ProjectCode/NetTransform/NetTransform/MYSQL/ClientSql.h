#pragma once
#pragma warning(disable: 4996)
#include <mysql.h>
#include <iostream>
#include <cstring>
#include <string>
#include "../PublicDataDef/PublicDataDef.h"
using namespace std;

class ClientSql
{
public:
	ClientSql();
	~ClientSql();

public:
	bool			connectDatabase(const DBJsConf_dt& dbInfo);			// 连接数据库
	bool			insertKeyInfo(const KeyInfo_dt& data);				// 插入密钥信息
	bool			getKeyInfo(int keyId, KeyInfo_dt& data);			// 获取密钥信息
	bool			getValuedKeyInfo(KeyInfo_dt& data);					// 获取数据库已经存储的有效密钥信息
	bool			removeKeyInfo(int keyId);							// 移除密钥信息

private:
	DBJsConf_dt		m_dbConnInfo;
	MYSQL*			m_pSqlHandle;
};