#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>

int main()
{
	/*初始化MYSQL句柄				**/
	MYSQL* pSqlHandle = mysql_init(NULL);
	if(NULL == pSqlHandle)
	{
		printf("mysql_init() error\n");
		return -1;
	}
	else
		printf("mysql_init() success\n");

	/*连接MYSQL数据库				**/
	MYSQL* pSqlConnHandle = mysql_real_connect(pSqlHandle, "127.0.0.1", "quhan", "123456", "mydb_class", 3306, NULL, 0);
	if(NULL == pSqlConnHandle)
	{
		printf("mysql_real_connect() error. error info: %s\n", mysql_error(pSqlHandle));
		mysql_close(pSqlHandle);
		return -1;
	}
	else
		printf("mysql_real_connect() success\n");

	/*关闭MYSQL连接					**/
	mysql_close(pSqlHandle);
	printf("mysql_close() success\n");

	return 0;
}
