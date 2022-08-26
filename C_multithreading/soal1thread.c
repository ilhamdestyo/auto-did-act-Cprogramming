#include "soal_common.c"
#include <pthread.h>
	int i,j,k;
	
typedef struct{
	dataInput data;
	int ndata;
}cobaThreadParams;

void *processThread(void *arg) {
	cobaThreadParams *readParams = arg;
	dataInput data = readParams->data;
    int count = readParams->ndata;
    /************* Batas Fungsi *************/
    char *tmpdata1[100],*tmpdata2[100],*tmpdata3[100];
    
    for(i=1;i<count+1;i++){
		tmpdata1[i]=IntToStr(datainput_1[i]);
		tmpdata2[i]=IntToStr(datainput_2[i]);
		tmpdata3[i]=IntToStr(datainput_3[i]);
		
		data.Input1[i]=tmpdata1[i];
		data.Input2[i]=tmpdata2[i];
		data.Input3[i]=tmpdata3[i];
		
	}
	data.ndata = count;
		
	save_data_file("data_copy1.txt",data);
	
	for(j=1;j<count+1;j++){
		free(tmpdata1[j]),tmpdata1[j]=NULL;
		free(tmpdata2[j]),tmpdata2[j]=NULL;
		free(tmpdata3[j]),tmpdata3[j]=NULL;
	}
	/************* Batas Fungsi *************/
	return NULL;
}

void processData(int ncore){
	pthread_t pth[ncore];
	cobaThreadParams readParams0;
	/************* Batas Fungsi *************/
	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999999,sizeof(char));
	dataBaca.Input2 = calloc(9999999,sizeof(char));
	dataBaca.Input3 = calloc(9999999,sizeof(char));
	
	readParams0.data = dataBaca;
	readParams0.ndata = number_data;
	
	for(int idx=0;idx<ncore;idx++){
		pthread_create(&pth[idx], NULL, processThread, &readParams0);
		//Need to wait until first thread finishes
		pthread_join(pth[idx], NULL);
	}
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
	/************* Batas Fungsi *************/
}

int main(int argc, char *argv[]){
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);
	
	for(k=0;k<1000000;k++){
		printf("iterasi ke - %d\n",k);
		processData(4);
	}
}
