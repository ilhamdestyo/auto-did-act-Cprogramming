/*Georgian Calendar algorithm programming*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare array 
const char *months[]= {"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OKTOBER","NOVEMBER","DECEMBER"};
const char Days[7][20] = {"   Monday     ","Tuesday   ","Wednesday  ","Thursday    ","Friday    ","Saturday    ","Sunday"};//Mul-Dim Array
const int monthinDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

//Declare enum
enum state{FALSE, TRUE};

//Declare union
union monthtype{
	int num; 
	char str[20];
}month;
	
//Function untuk ambil data integer dari user 
int get_int(char text[]){
    int num;
    printf("%s", text);
    scanf("%d", &num);
    return num;
}

// Function untuk menentukan tahun kabisat(366 hari) dalam kurun waktu 4 tahun sekali 
 int leapYears(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return TRUE; 	//mendeskripsikan benarnya tahun kabisat dan 
						//dengan menyimpan value 1 pada TRUE yang akan digunakan untuk penambahan hari kabisat
	}else {
		return FALSE; 	//Mendeskripsikan tidak pada tahun kabisat 
						//dengan menyimpan angka 0 pada FALSE akan digunakan untuk penambahan hari kabisat
	}   
}

//Function data hari dalam sebulan
int get_days_in_month(int year, int month) {
    if (month == 1) {
		/* logika yang berada dalam if adalah ketika if dengan parameter bulan sama dengan 1(arr-Februari)
		 * maka berikan input kabisat dari Function leapYear.
		 */
        int leap = leapYears(year);// tahun kabisat, ambil function tahun kabisat
        return 28 + leap;//28+1 hari = 29 Hari
    } else {
        return monthinDays[month]; //bulan lainnya mengikuti array monthDays[]
    }
}		

//Function untuk menentukan hari pertama dalam suatu bulan
int day_of_the_week(int y,int m,int d){		/* 0 = Monday */
	m++; //menyesuaikan pada array months karna element januari berada di index 0
	d--; //menyesuaikan agar hari pertama adalah hari senin
    //algoritma Tomohiko Sakamoto (untuk mencara hari di minggu pertama)
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
