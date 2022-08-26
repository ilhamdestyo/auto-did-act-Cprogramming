// Header file berisi function
#include "Common.c"

// Program Main
int main(void) {
    enum state x ;	// enum variabel x
    
    char *garisbatasHorizontal = "---------";//bisa diubah, posisi tanggal menyesuaikan secara otomatis
	char *garisbatasVertikal = "|";//bisa diubah
	char *latarTanggal[] = {" ",".","*","#"};//index bisa dipilih dari 0-3 (untuk merubah tampilan kalender)
	char *spasiAwalKalender = "   ";//bisa diubah
	char *Hari[] = {"senin","selasa","rabu","kamis","jum'at","sabtu","minggu"};//bisa diubah, posisi string menyesuaikan panjang string secara otomatis
	int JumlahBarisKalender;
	dataPrint dataoutprint;	// Function dataPrint variabel baru
    
    int year;
    int day = 1; // 1-based day
        
    month.num = get_int("Month : ");	// Input Bulan
    
    if (month.num > 0 && month.num <= 12){	// Jika nilai lebih besar dari 0 dan lebih kecil sama dengan 12
		x = True;	// variabel x = True atau x = 1
	}else {
		x = False;	// x = False atau x = 0
		printf("Bulan Salah\n");
	}
	
	if( x == 1){	// jika nilai x = 1 atau True
    	month.num-=1;			// month0 - 1
    	year = get_int("Year  : ");	// Input Tahun
    
		int dow      = get_startingDays(year, month.num, day);	// Variabel dow diisi dengan memanggil function get_startingDays(year,month.num,day)
		dow++;	// dow + 1
		int KolomMulaiHari = dow;	// Variabel berisi nilai dari variabel dow
		int num_days = get_days_in_month(year, month.num);	// Variabel num_days diisi dengan memanggil function get_days_in_month(year,month.num)
		int cek,cek1;
		printf("# Tampilan Baris #\n");
		printf("  - Otomatis = 1\n");
		printf("  - Manual   = 2\n");
		printf("Pilih Baris : ");
		scanf("%d", &cek);	// input nilai
		
		if (cek ==1){	// kondisi jika cek = 1
			JumlahBarisKalender = JumlahBaris(KolomMulaiHari,num_days);	// isi variabel dengan Function JumlahBaris(KolomMulaiHari,num_day);
		}else if (cek == 2){	// kondisi lain jika cek = 2
			printf("Jumlah Baris 1 - 6 : \n");
			scanf("%d", &cek1);	// input nilai
			// Kondisi jika nilai cek1 lebih kecil dari 1 atau lebih besar dari 6 akan print error dan program berhenti
			if(cek1<1 || cek1>6){printf("\nError , Input Tidak Sesuai");exit(0);}
			JumlahBarisKalender = cek1;	// nilai JumlahBarisKalender sama dengan nilai cek1
		}else { // kondisi salah print error dan program berhenti
			printf("\nError , Input Tidak Sesuai");
			exit(0);		// keluar program
		}
		
		strcpy(month.str, months[month.num]); //assign month.str dengan nama bulan dari array months[]
		printf("%41s %d\n\n", month.str, year);//display bulan dan tahun
		
		// Parameter dataoutprint diisi Function ProcessData
		dataoutprint = ProcessData(KolomMulaiHari,num_days,garisbatasHorizontal,garisbatasVertikal,spasiAwalKalender,latarTanggal[0],Hari,JumlahBarisKalender);
		
		// Display kalender
		for(int i=0;i<dataoutprint.ndata;i++){	// Pengulangan sebanyak i < dataoutprint.ndata
			printf("%s\n",dataoutprint.dataOut[i]);	// print dataoutprint.dataOut sesuai data [i]
		}
		// kondisi jika dataoutprint.nDay = 0
		if (dataoutprint.nDay == 0 ){
			dataoutprint.nDay = num_days;	// nilai dataoutprint.nDay =  data num_days
		}
		printf("\n\n  Jumlah hari yang ditampilkan = %d",dataoutprint.nDay);
		printf("\n  Jumlah hari total = %d\n\n",num_days);
	
		free(dataoutprint.dataOut),dataoutprint.dataOut=NULL;	// Membebaskan memory
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
		}else {
			return 0;
		}
	}
	
	system("./Kalender"); //kembali ke atas
}
