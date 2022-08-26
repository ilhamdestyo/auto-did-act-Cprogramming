#include <stdio.h> //mendefinisikan fungsi input dan output inti
#include <stdlib.h> //mendefinisikan fungsi konversi numerik, pseudo-random network generator, dan alokasi memori
#include <string.h> //mengaktifkan fungsi handling string
#include <ctype.h> //digunakan untuk testing dan mapping character
#include "soal_common1.c" //pemanggilan function yang ada pada "soal_common1.c"


int main(int argc, char *argv[]){
	
	enum state x ;	// enum variabel x
	
	char *garisbatasHorizontal = "---------";//bisa diubah, posisi tanggal menyesuaikan secara otomatis
	char *garisbatasVertikal = "|";//bisa diubah
	char *latarTanggal[] = {" ",".","*","#"};//index bisa dipilih dari 0-3 (untuk merubah tampilan kalender)
	char *spasiAwalKalender = "   ";//bisa diubah
	int JumlahBarisKalender;//bisa diubah //penentuan baris kalender yang ditampilkan
	dataPrint dataoutprint; //struct dari dataPrint diberi nama dataoutprint
		
	char *Hari[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};//bisa diubah, posisi string menyesuaikan panjang string secara otomatis
		
	//declare variable
    int year, day = 1; //1-based day
	
	//Mengambil data tahun dan bulan dari user
	month.num = get_int("Month :\n"); //input bulan
	if(month.num >= 1 && month.num <= 12){// Jika nilai lebih besar dari 0 dan lebih kecil sama dengan 12
		x = TRUE;	// variabel x = True atau x = 1
	}else{
		x = FALSE;
		printf("Bulan Salah\n");
	}
	
	// jika x = 1
	if(x == 1){
		month.num--;//month.num decrement
		year = get_int("Year :\n"); //input tahun
		
		int x = day_of_the_week(year,month.num,day);//penentuan variable x menjadi day_of_the_week yang diambil dari fungsi di common file
		int kolomMulaiHari = x ; //untuk penentuan mulai hari pada tiap tiap bulan
		kolomMulaiHari++; //increment untuk kolomMulaiHari
		int dayInMonth = get_days_in_month(year,month.num);//penentuan data hari dalam satu bulan (28,29,30,atau 31)
		int type0, type1;
		printf("# Select your Row Mode #\n"); //pilih mode row
		printf("  - AUTO = 1\n"); //otomatis
		printf("  - SPECIFY = 2\n"); //menentukan row sendiri
		printf("Set your Rows : ");
		scanf("%d", &type0);
	
		//Untuk type0 = 1
		if (type0 ==1){
		JumlahBarisKalender = countRow(kolomMulaiHari,dayInMonth);
		//Untuk type0 = 2
		}else if (type0 == 2){
			printf("row is for 1 - 6 : \n");
			scanf("%d", &type1);
		//Exit ketika baris tidak sesuai kondisi if
		//Jika type1 lebih kecil dari 1 atau lebih besar dari 6
			if(type1<1||type1>6){printf("\nYour input is dissonant!!! \nMaybe you can try again with rows is less than 1 or more than 6");
				exit(0);
			}
			JumlahBarisKalender = type1; // value JumlahBarisKalender sama dengan type1
		}else{
				//print Error
				printf("\nError!!! \tfault input!!!");
				exit(0);// keluar program
		}
	
		strcpy(month.str, months[month.num]); //copy monts ke month string
		printf("%38s\t %d\n\n", month.str, year); //display nama bulan dan tahun (center)
		dataoutprint = ProcessData(kolomMulaiHari,dayInMonth,garisbatasHorizontal,garisbatasVertikal,spasiAwalKalender,latarTanggal[0],Hari,JumlahBarisKalender);//isi dari struct dataoutprint yaitu PocessData dengan parameter-parameter yang ada didalamnya
	
		/*
		* Menentukan display kalender
		* Untuk increment i lebih kecil dari ndata pada dataoutprunt,
		* kemudian lakukan print string dataOut yang berasal dari array i
		*/
		for(int i=0;i<dataoutprint.ndata;i++){
			printf("%s\n",dataoutprint.dataOut[i]);
		}
		/*
		 * ambil nDay dari dayInMonth
		 */
		if (dataoutprint.nDay == 0 ){
			dataoutprint.nDay = dayInMonth;
		}
	
		printf("\n\n  Jumlah hari = %d\n",dataoutprint.nDay);
		printf("\n  Jumlah hari dalam sebulan = %d\n\n",dayInMonth);
	
		free(dataoutprint.dataOut),dataoutprint.dataOut=NULL;//clear memory
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
			break;
		}else{
			return 0; //program selesai
		}
	}
	system("./caltemplate");
}
