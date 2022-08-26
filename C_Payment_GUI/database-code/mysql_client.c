/*
 * mysql_client mysql_client.c
 * 
 * Copyright 2022 lime <lime@lime-ThinkPad-T450>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/**
 * you can compile this code with: gcc -o mysql_client mysql_client.c $(mysql_config --libs --cflags)
 **/
 
 
//#include <my_global.h>// header ini tidak terlalu diperlukan tetapi include standar library seperti stdio.h, dll
#include <stdio.h>
#include <mysql/mysql.h>

unsigned int mysql_errno(MYSQL *mysql);
const char *mysql_error(MYSQL *mysql);
void mysql_close(MYSQL *mysql);
int mysql_query(MYSQL *mysql, const char *stmt_str);
uint64_t mysql_insert_id(MYSQL *mysql);//query result last auto-incremented
uint64_t mysql_num_rows(MYSQL_RES *result);
unsigned long *mysql_fetch_lengths(MYSQL_RES *result);


MYSQL *mysql_init(MYSQL *mysql);
//ambil data dari database
MYSQL_RES *mysql_store_result(MYSQL *mysql);
MYSQL_RES *mysql_use_result(MYSQL *mysql);
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);

int main(int argc, char **argv[]){
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES *result;
	int number_of_rows;
	
	char uid[] = "CH3CO0";
	int saldo_akhir = 0;
	char status_transaksi[] = "Failed";
	char sql_statement[4096];
	
	conn= mysql_init(NULL);
	if(mysql_real_connect(conn, "192.168.1.15", "ridwan", "", "parking_area", 3306, NULL,0)==NULL){
		printf("The authentication failed with the following message:\n");
		printf("%s %d\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	
	sprintf(sql_statement, "INSERT INTO tb_monitor(uid, saldo_akhir,status_transaksi) VALUES('%s', '%d', '%s')", uid, saldo_akhir,status_transaksi);
	if(mysql_query(conn, sql_statement) !=0){
		printf("Query failed  with the following message:\n");
		printf("%s\n", mysql_error(conn));
		exit(1);
	} else{
	  //Kondisi ketika jika data pada tabel sudah ada maka akan mengembalikan kondisi error query
	  //sehingga ID tidak bertambah
	  //terminal akan memberi keterangan bahwa duplikasi telah terjadi.
	printf("The auto-generated ID is: %ld\n", (long) mysql_insert_id(conn));
	exit(1);
	}
	
	////ambil data
	//if(mysql_query(conn, "SELECT ID, LOGIN, PASSWORD FROM PAYMENT_TBL") !=0){
		//printf("Query failed  with the following message:\n");
		//printf("%s\n", mysql_error(conn));
		//exit(1);
	//}
	//result = mysql_store_result(conn);
	//printf("Number of rows: %ld\n", (long) mysql_num_rows(result));
	
	//while((row = mysql_fetch_row(result)) != NULL){
		//printf("ID: %s\n", row[0]);
		//printf("LOGIN: %s\n", row[1]);
		//printf("PASSWORD: %s\n", row[2]);
		//printf("\n");
	//}
	
 
	printf("The MySQL client version is %s\n", mysql_get_client_info());
	printf("The connection is sucessfull\n");
	printf("Newcard %s inserted into the database\n", uid);
	mysql_close(conn);
}

