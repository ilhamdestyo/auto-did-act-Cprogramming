/*
 * program melakukan penambahan 2 kolom lalu,
 * menjadikan file sebagai file binary
 * compile: gcc -Wall -o soal_biner soal_biner.c -lm
 * ./soal_biner 
 */


#include "soal_common_binary.c"


int main(int argc, char **argv)
{
	read_file("data_binary.txt");
	printf("jumlah data = %d\n",number_data);
	
	//ambil data
	get_data_from_rawdata();
	dataInput readDatanya;
	readDatanya.Input1 = calloc(9999,sizeof(char));
	readDatanya.Input2 = calloc(9999,sizeof(char));
	readDatanya.Input3 = calloc(9999,sizeof(char));
	readDatanya.Input4 = calloc(9999,sizeof(char));
	readDatanya.Input5 = calloc(9999,sizeof(char));
	
	for(int i=1;i<number_data+1;i++){
		datainput_1[i]=convert(datainput_1[i]);
		datainput_2[i]=convert(datainput_2[i]);
		datainput_3[i]=convert(datainput_3[i]);
		datainput_4[i]=convert(datainput_4[i]);
		datainput_5[i]=convert(datainput_5[i]);
	}
	
	for(int i=1;i<number_data+1;i++){
		readDatanya.Input1[i]=IntToStr(datainput_1[i]);
		readDatanya.Input2[i]=IntToStr(datainput_2[i]);
		readDatanya.Input3[i]=IntToStr(datainput_3[i]);
		readDatanya.Input4[i]=IntToStr(datainput_4[i]);
		readDatanya.Input5[i]=IntToStr(datainput_5[i]);
	}
	readDatanya.ndata = number_data;
	
	save_data_file("data_copy_biner.txt",readDatanya);
	
	free(readDatanya.Input1),readDatanya.Input1=NULL;
	free(readDatanya.Input2),readDatanya.Input2=NULL;
	free(readDatanya.Input3),readDatanya.Input3=NULL;
	free(readDatanya.Input4),readDatanya.Input4=NULL;
	free(readDatanya.Input5),readDatanya.Input5=NULL;
	
	
	return 0;
}

