//C program to insert data  in the table in 
//MySQL database dynamically in Linux.

#include <mysql.h>
#include <stdio.h>
#include <string.h>

int main()
{
   	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server = "127.0.0.1";
	char *user = "root";
	char *password = ""; /* set me first */
	char *database = "mysql";
	
	conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("MySQL initialization failed");
        return 1;
    }
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, 
                                      database, 3306, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

    //if (mysql_query(conn, "CREATE TABLE status(saldo INT, uid VARCHAR(16))")) {
        //printf("Unable to create database table in MyDb database\n");
        //mysql_close(conn);
        //return 1;
    //}

    if (mysql_query(conn, "insert into payment values(10000,'KIRAN')")) {
        printf("Unable to insert data into Employee table\n");
        mysql_close(conn);
        return 1;
    }
    if (mysql_query(conn, "Insert into payment values(200000,'DANI')")) {
        printf("Unable to insert data into Employee table\n");
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "Insert into payment values(1000000,'RAMAN')")) {
        printf("Unable to insert data into Employee table\n");
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    printf("Data inserted successfully\n");

    return 0;
}
