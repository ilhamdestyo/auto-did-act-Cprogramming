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

int main(void) {
	
	system("color 5F");
	//declare variable
    int year = 0;
    int day = 1;
	
	//Mengambil data tahun dan bulan dari user
    year = get_int("Year :\n");
    month.num = get_int("Month :\n");
	month.num--;
	
	int dow			= day_of_the_week(year, month.num, day); //inisialisasi dow dengan function mencari hari
	int num_days	= get_days_in_month(year, month.num); //inisialisasi num_days dengan return function get_days_in_month

	strcpy(month.str, months[month.num]); //copy monts ke month string
	printf("%38s\t %d\n\n", month.str, year); //display nama bulan dan tahun (center)
	
	
	//Penentuan display Hari untuk dimuat pada tiap tiap kolom tabel
	for (int i = 0; i < 7; i++){
		printf("%s",Days[i]);
	}
	//display batas kolom hari dan tanggal
	printf("\n");
	printf("+----------+----------+----------+----------+----------+----------+----------+\n");

	//penentuan tanggal 1 diletakkan pada display hari
    for (int i=0; i<dow; ++i)
       printf("|          ");

	//Penempatan Tanggal
    while (day <= num_days) {
        printf("|%10d",day++);
        dow = ( dow + 1 ) % 7;
        if (!dow)
        //display bentuk table saat dow dengan value 0
        printf("|\n|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "+----------+----------+----------+----------+----------+----------+----------+\n");
           
    }
    
	//display bentuk table saat dow dengan value 1
    if (dow){
        printf("|\n|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "|          |          |          |          |          |          |          |\n"
                  "+----------+----------+----------+----------+----------+----------+----------+\n");
	}
	
	
	while ((getchar()) != '\n'); //flush buffer agar dapat menerima input user kembali
    //Membuat prompt untuk lanjut atau tidak
    char ch; 
	printf("Press 1 to continue or 0 to close : ");
	ch = getchar();
	while(1){
		if((ch != '1') && (ch != '0')){ //looping terus hingga mendapatkan value char '1' atau '0'
			while ((getchar()) != '\n'); //flush
			printf("\nPress 1 to continue or 0 to close : ");
			ch = getchar();
		}else if(ch == '1'){
			return main(); //kembali ke atas 
		}else {
			return 0; //program selesai
		}
	}

}
