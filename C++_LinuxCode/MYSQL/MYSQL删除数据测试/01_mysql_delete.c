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

	/*向数据库插入数据					**/
	char buf[128] = "\0";
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "delete from my_c_tbl where id = 1");
	int length = strlen(buf);

	int insertRet = mysql_real_query(pSqlConn, buf, length);
	if(0 != insertRet)
		printf("%s\n", mysql_error(pSqlConn));
	else
		printf("delete data from my_c_tbl success\n");

	mysql_close(pSqlHandle);
	return 0;
}
