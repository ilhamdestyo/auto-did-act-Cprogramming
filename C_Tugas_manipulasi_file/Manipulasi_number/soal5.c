#include "soal_common.c"

int main(int argc, char *argv[]){
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);
	
	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));
	
	int count=0;
	for(int i=1;i<number_data+1;i++){
		count++;//pindah data di kolom ke baris sesuai dengan nomor kolom
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);//input baris satu
		count++;//pindah data di kolom ke baris sesuai dengan nomor kolom
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);//input baris2
		count++;//pindah data di kolom ke baris sesuai dengan nomor kolom
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);//input baris3
	}
	dataBaca.ndata = count;
	for(int i=1;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}
		dataBaca.Input2[i]="";//Ubah kolom ke 2 menjadi whitespace
		dataBaca.Input3[i]="";//mengubah kolom ke 3 menjadi whitespace
		
		//Jika data input tidak habis dibagi modulus hasilnya = 1 dan lebih besar dari 5 maka print ganjil
		if(isGanjil(atoi(dataBaca.Input1[i]))==1 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="ganjil > 5";}
		//Jika data input tidak habis dibagi modulus hasilnya = 0 dan lebih besar dari 5 maka print genap
		else if(isGanjil(atoi(dataBaca.Input1[i]))==0 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="genap > 5";}
		//Jika tidak, maka output nilai dari hasil count sebelumnya ditampilkan
		else{dataBaca.Input1[i]=dataBaca.Input1[i];}
	}
	
	save_data_file("data_copy5.txt",dataBaca);
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}
