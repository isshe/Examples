
//ubuntu下要：
//sudo apt-get install libmysqlclient-dev
//sudo apt-get mysql...

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

const char *server_host = "localhost";
const char *user_name = "root";
const char *user_pwd = "root";
const char *db_name = "isshe";
const unsigned int port = 0;//3306;         //都可以
const char * unix_socket_name = NULL;
const unsigned int flags = 0;

const char *sql_create_table =
			"CREATE TABLE `isshe`.`isshe_table` ("
            "`abc` INT NOT NULL,"
            "`def` VARCHAR(45) NULL,"
            "PRIMARY KEY (`abc`))";
const char *sql_insert = "INSERT INTO isshe_table(abc, def) VALUES(3, 'haha')";
const char *sql_select = "SELECT * FROM isshe";
const char *sql_delete = "DELETE FROM isshe_table WHERE abc = 1";
const char *sql_alter = "UPDATE isshe_table SET def = 'hehe' WHERE abc = 1";

int main(void)
{
    MYSQL *pconn = NULL;
    int res = 0;

    pconn = mysql_init(NULL);   //
    if (pconn == NULL)
    {
        printf("mysql_init failed!\n");
        return -1;
    }

	//连接
    pconn = mysql_real_connect(pconn, server_host, user_name,
                user_pwd, db_name, port, unix_socket_name, flags);
    if (pconn == NULL)
    {
        printf("connection failed\n");
    }
    else
    {
        printf("connection success\n");
        //返回0表示成功！
		//新建表
        //res = mysql_query(pconn,sql_create_table);
        //printf("res = %d\n", res);

		//插入数据
		//res = mysql_query(pconn,sql_insert);
        //printf("res = %d\n", res);

		//修改数据
		//res = mysql_query(pconn,sql_alter);
        //printf("res = %d\n", res);

		//删除
		res = mysql_query(pconn,sql_delete);
        printf("res = %d\n", res);
    }

    mysql_close(pconn);
    return 0;
}
