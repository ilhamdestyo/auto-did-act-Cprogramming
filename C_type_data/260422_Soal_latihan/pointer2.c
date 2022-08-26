#include <stdio.h>

//function untuk menunjukkan penggunaan pointer untuk print address
//dan variable yang di pointer
void Data(){
	int tools[5]={12,4341,515,61,15}; //data array
	
	int * ptr;//inisialisasi pointer
	
	ptr = tools;
	
	for (int i=0;i<5; i++){
		printf("at ptr = %p\n",ptr);
		printf("at ptr = %d\n",*ptr);
		ptr++;
	}
}

int main(){
	Data();
} 
