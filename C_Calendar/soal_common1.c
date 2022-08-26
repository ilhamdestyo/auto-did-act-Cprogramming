#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/********************************************Georgian Calendar algorithm programming*******************************************************/
//Declare array 
const char *months[]= {"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OKTOBER","NOVEMBER","DECEMBER"};//Mul-Dim Array
const char Days[7][20] = {"   Monday     ","Tuesday   ","Wednesday  ","Thursday    ","Friday    ","Saturday    ","Sunday"};//Mul-Dim Array
const int monthinDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

//Declare enum
enum state{FALSE, TRUE};//penggunaan value 0 untuk menunjukkan FALSE dan value 1 untuk menunjukkan TRUE

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
	}else {
		return monthinDays[month]; //bulan lainnya mengikuti array monthinDays[]
	}
}


//Function untuk menentukan hari pertama dalam suatu bulan
int day_of_the_week(int y,int m,int d){		/* 0 = Monday */
	m++; //menyesuaikan pada array months karna element januari berada di index 0
	d--; //menyesuaikan agar hari pertama adalah hari 
	
	//algoritma Tomohiko Sakamoto (untuk mencara hari di minggu pertama)
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

//Function jumlah baris
int countRow(int firstDay, int nDays){
	int row;
	int nRow = (firstDay-1)+ nDays;
	//jika February 28 hari dan dimulai hari senin maka dibuat 4 baris
	if (nRow < 29){ 
		row = 4;
	}else if (nRow > 35){
		row = 6;
	}else{
		row = 5;
	}
	return row;
}



/**************************************************TEMPLATE FUNCTION PROGRAM***********************************************************/

/**
 * pembuatan struct data berupa data print yang berisikan
 * char dataOutput, value banyaknya data dan value hari
 **/
typedef struct{
 char **dataOut;
 int ndata;
 int nDay;
} dataPrint;

/**
 * Pembuatan convert dari integer ke string dengan data berupa char
 **/
char *IntToStr(int x){
	/**
	 * size of char dikali 1 kemudian menunjukkan alokasi memori pada
	 * string untuk diambil bit-sizenya,
	 * kemudian di diambil nilai x ke str
	 **/
	char *str=(char *)malloc(1 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

/**
 * Function untuk mendapatkan string bit-size dari index
 **/
char *get_string_from_index(char *string, int in1, int in2){
	char *cr1 = (char*)malloc(strlen(string)); //ambil bit-size dari string untuk value cr1
	char *cr2 = (char*)malloc(strlen(string)); //ambil bit-size dari string untuk value cr2
	char *Result = (char*)malloc(strlen(string));  //ambil bit-size dari string untuk value Result
	
	strcpy(cr1,&string[in1]);//kemudian copy isi sting index1 ke cr1
	// kemudian dibuat penambahan string pada cr2 dari cr1 sebesar value dari index2+1- value index1
	strncat (cr2, cr1, (in2+1-in1));
	//kemudian masukkan cr2 ke Result
	strcat(Result, cr2);
	return Result; //kembali lakukan proses selanjutnya pada Result
}

/**
 * Pembuatan function untuk menggabungkan kata pada string
 **/
char* gabung_kata(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);//ambil bit-size string dari result sebesar bit-size s1+s2+1
    strcpy(result, s1);//isi result dengan s1
    strcat(result, s2);//gabungkan s2 pada result
    return result;//return value ke result
}

/**
 * ganti string awal(word) dengan string yang baru
 **/
char* replaceWordInString(const char* s, const char* oldW, const char* newW){ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
    //counting jumlah dari oldw
    //yang terdapat pada string
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++;
             // lompat ke index setelah oldWorld
            i += oldWlen - 1; 
        } 
    } 
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); //buat new string result dengan bit-size sebesar malloc
  
    i = 0; 
    while (*s) { 
		//compare substring dengan resultnya
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
}

/**
 * trim me-remove white-space string, yang tidak dibutuhkan
 * di awal string
 **/
char *trim(char *s) {
	int count = -1;
	for(int i=0;i<strlen(s)+1;i++){
		if(isspace(s[i])==0){//trim mengambil white space di i
			count = i;//sehingga counting diambil dari i
			break;
		}
	}
	//calloc akan mengalokasikan hasil kali length s dengan bit-size char
	//kemudian menyimpannya pada pointer result
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=count;i<strlen(s)+1;i++){
		count1++;
		result[count1] = s[i];
	}
	return result;
}

/**
 * remove white-space yang tidak dibutuhkan diantara string atau di belakang string
 * Counting length character yang terdapat pada variable s
 * Jika hasil dari count terdapat white-space char maka kurangi value range
 * kemudian masukkan hasil ke variable di function "trim(result)"
 **/
char *shift_trim(char *s) {
	int count;
	for(int i=1;i<strlen(s)+1;i++){
		count = strlen(s)-i;
		if(isspace(s[count])==0){//shift trim mengambil white space di count
			count = strlen(s)-i;//sehingga counting diambil dari length string - i
			break;
		}
	}
	//calloc akan mengalokasikan hasil kali length s dengan bit-size char
	//kemudian menyimpannya pada pointer result
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=0;i<count+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	result = trim(result);
	return result;
}


int c_round(double x){
	return x < 0 ? x - 0.5 : x + 0.5; //x - 0.5, jika x is lebih kecil dari nol; sebaliknya, it assigns x + 0.5 to x. 
}

/**
 * struct dataPrint diberi nama Process data yang berisi parameter integer data dan char data
 **/
dataPrint ProcessData(int DayBegin, int countHari, char *lineborderTop, char *lineborderVet, char *space, char *whitespace, char *dayName[], int nBaris){
	/**
	 * seluruh static value berisi variable dimana valuenya akan di scope, 
	 * sehingga nilai yang digunakan adalah perubahan dari nilai sebelumnya
	 **/
	static int TanggalDummy[50]; //buat data dummy untuk tanggal dengan bit-size 50
	static int nHari = 7; //data hari sebanyak 7
	static char *valBaris[200]; //buat data char untuk baris array dengan bit-size 200
	static int HitungHari=-1;
	static char *lineborderTop1; //untuk membuat bordir di top (pembatas antara hari dengan tanggalan)
	static int BatasMargin1,BatasMargin2;
	static char *txtResult = NULL;
	char **datain = calloc(9999,sizeof(char)); //susun datain dari bit-size ke kolom array 9999
	static int countBorder = 0;
	static char *tmpchar1 = "";
	static char *tmpchar = "";
	static char *sspace = " ";
	static char *space1[7],*space2[7];
	static int pt1[7],pt2[7];
	lineborderTop1 = gabung_kata("+",lineborderTop); //untuk memberi pembatas atau line bordir yang membentuk kalender
	datain[0] = "";
	
	//mengkondisikan agar kolom hanya sebanyak 7
	if(DayBegin<1 || DayBegin>7){printf("Error! Day coloumn must be between 1-7\n");exit(1);}
	
	for(int i=0;i<countHari;i++){TanggalDummy[i]=i+1;}//untuk mengisi tanggal dummy pada tiap tiap kolom
	
	//Penentuan kolom pada nama hari dibuat center
	for(int i=0;i<nHari;i++){
		space1[i]="";
		space2[i]="";
		pt1[i] = c_round((strlen(lineborderTop)+2-strlen(dayName[i]))/2);
		pt2[i] = strlen(lineborderTop)+1-(strlen(dayName[i])+pt1[i]);
		
		for(int s=0;s<pt1[i];s++){space1[i] = gabung_kata(sspace,space1[i]);}
		for(int s=0;s<pt2[i];s++){space2[i] = gabung_kata(sspace,space2[i]);}
	}
	
	//Gabungkan antara space dan nama hari supaya Center
	for(int i=0;i<nHari;i++){
		datain[0] = gabung_kata(datain[0],gabung_kata(gabung_kata(space1[i],dayName[i]),space2[i]));
	}
	
	//Penentuan baris yang membentuk tamplate tabel
	for(int k=0;k<nBaris+2;k++){
		countBorder++;
		datain[countBorder] = "";
		for(int i=0;i<nHari;i++){
			//memberikan batas "+" di ujung kanan tabel pada baris pembatas tabel
			txtResult = i<(nHari)-1 ? lineborderTop1 : gabung_kata(lineborderTop1,"+");
			datain[countBorder] = gabung_kata(datain[countBorder],txtResult); //banyak data input didapat dari gabung_kata
		}
		if(k<nBaris){
			for(int j=0;j<3;j++){
				txtResult=space;
				countBorder++;
				int ndata = (strlen(lineborderTop1)*(nHari+1));
				for(int i=0;i<ndata;i++){
					tmpchar1 = tmpchar;
					if(i%strlen(lineborderTop1) == 0 || i==0){
						BatasMargin1 = i+1;
						BatasMargin2 = i+2;
						if(j==1 && i<strlen(lineborderTop1)*(nHari)){
							if(k==0 && i>=(DayBegin-1)*strlen(lineborderTop1)){HitungHari++;}
							else if(k>0){HitungHari++;}
						}
						valBaris[i]=lineborderVet;
					}
					else{valBaris[i]=" ";} // menentukan tata letak baris dari tanggalan
					
					if(j==1 && i<=BatasMargin2 && i>BatasMargin1 && i<strlen(lineborderTop1)*(nHari)){
						valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),0,0);
					}
					
					tmpchar = shift_trim(get_string_from_index(valBaris[i],0,0));
					
					if(TanggalDummy[HitungHari] > 9 && TanggalDummy[HitungHari] < 20){
						if(atoi(tmpchar1)==1){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 19 && TanggalDummy[HitungHari] < 30){
						if(atoi(tmpchar1)==2){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 29 && TanggalDummy[HitungHari] < 40){
						if(atoi(tmpchar1)==3){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 39 && TanggalDummy[HitungHari] < 50){
						if(atoi(tmpchar1)==4){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}

					txtResult = gabung_kata(txtResult,valBaris[i]);
					for(int i=32;i<50;i++){
						if(strstr(txtResult, shift_trim(IntToStr(i))) != NULL){txtResult=replaceWordInString(txtResult,shift_trim(IntToStr(i)),"0 ");}
					}
					if(strstr(txtResult, gabung_kata(lineborderVet," 0")) != NULL){
						txtResult=replaceWordInString(txtResult,gabung_kata(lineborderVet," 0"),gabung_kata(lineborderVet,"  "));
					}
				}
				datain[countBorder] = shift_trim(txtResult);
				if(strstr(datain[countBorder], " ") != NULL){datain[countBorder]=replaceWordInString(datain[countBorder]," ",whitespace);}
			}
		}
	
	}
	
	dataPrint dataout;
	dataout.dataOut = calloc(9999,sizeof(char)); //susun dataOut dari bit-size ke kolom array 9999
	for(int i=0;i<countBorder;i++){
		dataout.dataOut[i] = gabung_kata(space,datain[i]);
	}
	dataout.ndata = countBorder;
	dataout.nDay = TanggalDummy[HitungHari] > 31 ? 31 : TanggalDummy[HitungHari];
	
	free(datain),datain=NULL;
	
	return dataout;
}

