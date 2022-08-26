#include "soal_common.c"

int main(int argc, char *argv[]){
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);
	
	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));
	
	for(int i=1;i<number_data+1;i++){
		dataBaca.Input1[i]=IntToStr(datainput_1[i]);
		dataBaca.Input2[i]=",";
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = number_data;
	
	save_data_file("data_copy2.txt",dataBaca);
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}
