#include "ClientSql.h"

ClientSql::ClientSql()
{
	m_pSqlHandle = NULL;
}

ClientSql::~ClientSql()
{
	if (NULL != m_pSqlHandle)
		mysql_close(m_pSqlHandle);
}

bool ClientSql::connectDatabase(const DBJsConf_dt& dbInfo)
{
	/*数据库环境初始化																		**/
	MYSQL* pSqlInitHandle = mysql_init(NULL);
	if (NULL == pSqlInitHandle)
	{
		cerr << "MYSQL INIT ERR. ERR INFO: " << mysql_error(pSqlInitHandle) << endl;
		return false;
	}

	/*数据库连接																			**/
	m_pSqlHandle = mysql_real_connect(pSqlInitHandle, dbInfo.sDBIpAddr, dbInfo.sDBUserName, dbInfo.sDBUserPasswd, dbInfo.sDBName, (unsigned int)dbInfo.iDBPort, NULL, (unsigned long)0);
	if(NULL == m_pSqlHandle)
	{
		cerr << "MYSQL CONNECT ERR. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;

		mysql_close(pSqlInitHandle);
		return false;
	}

	/*数据库连接信息拷贝																	**/
	m_dbConnInfo.iDBPort = dbInfo.iDBPort;
	strcpy(m_dbConnInfo.sDBIpAddr, dbInfo.sDBIpAddr);
	strcpy(m_dbConnInfo.sDBUserName, dbInfo.sDBUserName);
	strcpy(m_dbConnInfo.sDBUserPasswd, dbInfo.sDBUserPasswd);
	strcpy(m_dbConnInfo.sDBName, dbInfo.sDBName);
	strcpy(m_dbConnInfo.sDBTblName, dbInfo.sDBTblName);

	return true;
}

bool ClientSql::insertKeyInfo(const KeyInfo_dt& data)
{
	if (NULL == m_pSqlHandle)
	{
		cerr << "MYSQL CURRENT IS NULL. INSERT FAILED." << endl;
		return false;
	}

	char sSqlBuf[512] = "\0";
	int size = sprintf(sSqlBuf, "insert into %s values('%s', '%s', '%s', %d, %d)", m_dbConnInfo.sDBTblName, data.sClientId, data.sServerId, data.sKeyInfo, data.iKetStatus, data.iKeyId);
	sSqlBuf[size] = '\0';

	int execResult = mysql_real_query(m_pSqlHandle, sSqlBuf, size);
	if (0 != execResult)
	{
		cerr << "INERT KEY INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}
	else
		return true;
}

bool ClientSql::getKeyInfo(int keyId, KeyInfo_dt& data)
{
	if (NULL == m_pSqlHandle)
	{
		cerr << "MYSQL CURRENT IS NULL. GET KEY FAILED." << endl;
		return false;
	}

	/*准备数据查询语句																													**/
	char sSqlBuf[512] = "\0";
	int size = sprintf(sSqlBuf, "select * from %s where %s = %d", m_dbConnInfo.sDBTblName, DB_COLU_KEY_ID.c_str(), keyId);
	sSqlBuf[size] = '\0';

	/*数据查询																															**/
	int execResult = mysql_real_query(m_pSqlHandle, sSqlBuf, size);
	if (0 != execResult)
	{
		cerr << "SEARCH KEY INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}
	
	/*获取数据查询结果集																												**/
	MYSQL_RES* pSqlResult = mysql_store_result(m_pSqlHandle);
	if (NULL == pSqlResult)
	{
		cerr << "STORE KEY RESULT INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}

	/*获取列序号																														**/
	int cloumnClientId = -1;
	int cloumnServerId = -1;
	int cloumnKeyInfo = -1;
	int cloumnKeyStatus = -1;
	int cloumnKeyId = -1;
	int columnSeq = 0;
	MYSQL_FIELD* pColuInfo = mysql_fetch_field(pSqlResult);
	while (NULL != pColuInfo)
	{
		if (0 == strncmp(DB_COLU_CLIENT_ID.c_str(), pColuInfo->name, DB_COLU_CLIENT_ID.size()))
			cloumnClientId = columnSeq;
		else if (0 == strncmp(DB_COLU_SERVER_ID.c_str(), pColuInfo->name, DB_COLU_SERVER_ID.size()))
			cloumnServerId = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_INFO.c_str(), pColuInfo->name, DB_COLU_KEY_INFO.size()))
			cloumnKeyInfo = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_STATUS.c_str(), pColuInfo->name, DB_COLU_KEY_STATUS.size()))
			cloumnKeyStatus = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_ID.c_str(), pColuInfo->name, DB_COLU_KEY_ID.size()))
			cloumnKeyId = columnSeq;
		++columnSeq;
		pColuInfo = mysql_fetch_field(pSqlResult);
	}

	if (-1 == cloumnClientId || -1 == cloumnServerId || -1 == cloumnKeyInfo || -1 == cloumnKeyStatus || -1 == cloumnKeyId)
	{
		cerr << "GET COLUMN SEQUENCE FAILED." << endl;
		mysql_free_result(pSqlResult);
		return false;
	}

	/*获取MYSQL查询结果的行数和列数																										**/
	int rows = mysql_num_rows(pSqlResult);
	int columns = mysql_num_fields(pSqlResult);

	bool searchResult = false;
	MYSQL_ROW curRowInfo = mysql_fetch_row(pSqlResult);
	while (NULL != curRowInfo)
	{
		string sKeyId = std::to_string(keyId);
		string curKeyId = curRowInfo[cloumnKeyId];
		if (sKeyId == curKeyId)
		{
			data.iKetStatus = atoi(curRowInfo[cloumnKeyStatus]);
			data.iKeyId = keyId;
			strcpy(data.sClientId, curRowInfo[cloumnClientId]);
			strcpy(data.sServerId, curRowInfo[cloumnServerId]);
			strcpy(data.sKeyInfo, curRowInfo[cloumnKeyInfo]);

			searchResult = true;
			break;
		}
		curRowInfo = mysql_fetch_row(pSqlResult);
	}
	mysql_free_result(pSqlResult);

	if (false == searchResult)
		cerr << "SEARCH FAILED. CAN NOT FIND SPECIFIC KEY INFO OF KEY ID: " << keyId << endl;

	return searchResult;
}

bool ClientSql::getValuedKeyInfo(KeyInfo_dt& data)
{
	if (NULL == m_pSqlHandle)
	{
		cerr << "MYSQL CURRENT IS NULL. GET VALUE KEY FAILED." << endl;
		return false;
	}

	/*准备数据查询语句																													**/
	char sSqlBuf[512] = "\0";
	int size = sprintf(sSqlBuf, "select * from %s", m_dbConnInfo.sDBTblName);
	sSqlBuf[size] = '\0';

	/*数据查询																															**/
	int execResult = mysql_real_query(m_pSqlHandle, sSqlBuf, size);
	if (0 != execResult)
	{
		cerr << "SEARCH KEY INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}

	/*获取数据查询结果集																												**/
	MYSQL_RES* pSqlResult = mysql_store_result(m_pSqlHandle);
	if (NULL == pSqlResult)
	{
		cerr << "STORE KEY RESULT INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}

	/*获取列序号																														**/
	int cloumnClientId = -1;
	int cloumnServerId = -1;
	int cloumnKeyInfo = -1;
	int cloumnKeyStatus = -1;
	int cloumnKeyId = -1;
	int columnSeq = 0;
	MYSQL_FIELD* pColuInfo = mysql_fetch_field(pSqlResult);
	while (NULL != pColuInfo)
	{
		if (0 == strncmp(DB_COLU_CLIENT_ID.c_str(), pColuInfo->name, DB_COLU_CLIENT_ID.size()))
			cloumnClientId = columnSeq;
		else if (0 == strncmp(DB_COLU_SERVER_ID.c_str(), pColuInfo->name, DB_COLU_SERVER_ID.size()))
			cloumnServerId = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_INFO.c_str(), pColuInfo->name, DB_COLU_KEY_INFO.size()))
			cloumnKeyInfo = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_STATUS.c_str(), pColuInfo->name, DB_COLU_KEY_STATUS.size()))
			cloumnKeyStatus = columnSeq;
		else if (0 == strncmp(DB_COLU_KEY_ID.c_str(), pColuInfo->name, DB_COLU_KEY_ID.size()))
			cloumnKeyId = columnSeq;
		++columnSeq;
		pColuInfo = mysql_fetch_field(pSqlResult);
	}

	if (-1 == cloumnClientId || -1 == cloumnServerId || -1 == cloumnKeyInfo || -1 == cloumnKeyStatus || -1 == cloumnKeyId)
	{
		cerr << "GET COLUMN SEQUENCE FAILED." << endl;
		mysql_free_result(pSqlResult);
		return false;
	}

	/*获取MYSQL查询结果的行数和列数																										**/
	int rows = mysql_num_rows(pSqlResult);
	int columns = mysql_num_fields(pSqlResult);

	bool searchResult = false;
	MYSQL_ROW curRowInfo = mysql_fetch_row(pSqlResult);
	while (NULL != curRowInfo)
	{
		int curKeyStatus = atoi(curRowInfo[cloumnKeyStatus]);
		if (0 != curKeyStatus)
		{
			data.iKetStatus = curKeyStatus;
			data.iKeyId = atoi(curRowInfo[cloumnKeyId]);
			strcpy(data.sClientId, curRowInfo[cloumnClientId]);
			strcpy(data.sServerId, curRowInfo[cloumnServerId]);
			strcpy(data.sKeyInfo, curRowInfo[cloumnKeyInfo]);

			searchResult = true;
			break;
		}
		curRowInfo = mysql_fetch_row(pSqlResult);
	}
	mysql_free_result(pSqlResult);

	if (false == searchResult)
		cerr << "SEARCH FAILED. CAN NOT FIND INVALIED KEY INFO." << endl;

	return searchResult;
}

bool ClientSql::removeKeyInfo(int keyId)
{
	if (NULL == m_pSqlHandle)
	{
		cerr << "MYSQL CURRENT IS NULL. REMOVE KEY FAILED." << endl;
		return false;
	}

	char sSqlBuf[128] = "\0";
	int size = sprintf(sSqlBuf, "delete from %s where %s = %d", m_dbConnInfo.sDBTblName, DB_COLU_KEY_ID.c_str(), keyId);
	sSqlBuf[size] = '\0';

	int execResult = mysql_real_query(m_pSqlHandle, sSqlBuf, size);
	if (0 != execResult)
	{
		cerr << "REMOVE KEY INFO FAILED. ERR INFO: " << mysql_error(m_pSqlHandle) << endl;
		return false;
	}
	else
		return true;
}