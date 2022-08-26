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
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = count;
	for(int i=1;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input2[i]="";}
		dataBaca.Input2[i]="";
		dataBaca.Input3[i]="";
	}
	
	save_data_file("data_copy4.txt",dataBaca);
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}
