#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main()
{
	/*初始化MYSQL句柄					**/
	MYSQL* pSqlHandle = mysql_init(NULL);
	if(NULL == pSqlHandle)
	{
		printf("mysql_init() error\n");
		return -1;
	}

	/*连接MYSQL数据库					**/
	MYSQL* pSqlConn = mysql_real_connect(pSqlHandle, "192.168.0.195", "quhan", "123456", "my_c_db", 3306, NULL, 0);
	if(NULL == pSqlConn)
	{
		printf("%s\n", mysql_error(pSqlConn));
		mysql_close(pSqlHandle);
		return -1;
	}

	/*执行MYSQL查询						**/
	int selectRet = mysql_query(pSqlConn, "select * from my_c_tbl");
	if(0 != selectRet)
	{
		printf("%s\n", mysql_error(pSqlConn));
        mysql_close(pSqlHandle);
        return -1;
	}

	/*获取MYSQL查询结果					**/
	MYSQL_RES* pSqlResults = mysql_store_result(pSqlConn);
	if(NULL == pSqlResults)
    {
        printf("%s\n", mysql_error(pSqlConn));
        mysql_close(pSqlHandle);
        return -1;
    }

	/*获取列名称						**/
	MYSQL_FIELD* pColuInfo = mysql_fetch_field(pSqlResults);
	while(NULL != pColuInfo)
	{
		printf("%s ", pColuInfo->name);
		pColuInfo = mysql_fetch_field(pSqlResults);
	}
	printf("\n");

	/*获取MYSQL查询结果的行数和列数		**/
	int rows = mysql_num_rows(pSqlResults);
	int columns = mysql_num_fields(pSqlResults);

	MYSQL_ROW curRowInfo = mysql_fetch_row(pSqlResults);
	while(NULL != curRowInfo)
	{
		for(int i = 0; i < columns; ++i)
		{
			printf("%s ", curRowInfo[i]);
		}
		printf("\n");

		curRowInfo = mysql_fetch_row(pSqlResults);
	}
	
	/*释放MYSQL查询结果占用的内存空间	**/
	mysql_free_result(pSqlResults);

	/*关闭MYSQL数据连接					**/
	mysql_close(pSqlHandle);
	return 0;
}
