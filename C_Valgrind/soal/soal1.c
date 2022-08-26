#include "soal_common.c"

int main(int argc, char *argv[]){
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);
	char *tmpdata1[100],*tmpdata2[100],*tmpdata3[100];
	int i,j,k;
	
	for(k=0;k<1000000;k++){
		printf("iterasi ke - %d\n",k);
		get_data_from_rawdata();
		dataInput dataBaca;
		dataBaca.Input1 = calloc(9999999,sizeof(char));
		dataBaca.Input2 = calloc(9999999,sizeof(char));
		dataBaca.Input3 = calloc(9999999,sizeof(char));
		
		for(i=1;i<number_data+1;i++){
			tmpdata1[i]=IntToStr(datainput_1[i]);
			tmpdata2[i]=IntToStr(datainput_2[i]);
			tmpdata3[i]=IntToStr(datainput_3[i]);
			
			dataBaca.Input1[i]=tmpdata1[i];
			dataBaca.Input2[i]=tmpdata2[i];
			dataBaca.Input3[i]=tmpdata3[i];
			
		}
		dataBaca.ndata = number_data;
		
		save_data_file("data_copy1.txt",dataBaca);
		
		for(j=1;j<number_data+1;j++){
			free(tmpdata1[j]),tmpdata1[j]=NULL;
			free(tmpdata2[j]),tmpdata2[j]=NULL;
			free(tmpdata3[j]),tmpdata3[j]=NULL;
		}
		
		free(dataBaca.Input1),dataBaca.Input1=NULL;
		free(dataBaca.Input2),dataBaca.Input2=NULL;
		free(dataBaca.Input3),dataBaca.Input3=NULL;
	}
}
