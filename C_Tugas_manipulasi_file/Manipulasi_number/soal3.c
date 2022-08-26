#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "soal_common.c"

int main(int argc, char *argv[]){
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);
	
	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));
	int count1=0;
	int count2=0;
	for(int i=1;i<number_data+1;i++){
		//untuk manipulasi bilangan ganjil berada di kolom ke 2
		//ketika disiasati dengan memberikan count1
		if(isGanjil(datainput_1[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_3[i]);
		}
		
		//untuk manipulasi bilangan genap berada di kolom ke 1
		//ketika disiasati dengan memberikan count2
		if(isGanjil(datainput_1[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_3[i]);
		}
	}
	
	dataBaca.ndata = (count1 > count2 ? count1 : count2);
	
	for(int i=1;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}
		if(dataBaca.Input2[i]==NULL){dataBaca.Input2[i]="";}
		dataBaca.Input3[i]="";
	}
	
	save_data_file("data_copy3.txt",dataBaca);
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}
