/*
 * Soal Pemrograman bahasa C
 * Soal 2
 */


#include <stdio.h>

void main()
{
	char p1 ={
		.x = 1, y=7
	};
	
	FILE* in;
	FILE* out;
	
	char buffer_in[256], buffer_out[256];
	
	fopen_s(&out, "data_copy2.txt","w");
	if (out==NULL){
		return 1;
	}
	
	sprintf_s(buffer_out,256, "%d, %d\n",p1.x,p1.y);
	fwrite(buffer_out,sizeof(char),strlen(buffer_out),out);
	fclose(out);
	
	if (bytes_wrote !=strlen(buffer_out)){
		return 1;
	}
	
	return 0;
