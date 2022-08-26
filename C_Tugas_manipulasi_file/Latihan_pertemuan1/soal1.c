/*
 * Soal Pemrograman bahasa C
 * Soal 1 
 */


#include <stdio.h>
#include <stdlib.h>

void main()
{
	char buff[255];//buffer untuk data yang dibaca
	char text[255];//buffer untuk data yang dituis
	FILE *fptr; //pointer
	
	//open file untuk menulis ditandai dengan command w atau write
	fptr = fopen("data_copy1.txt","w");
	
	for (int i=0; i<4;i++){
		//input text
		printf("isi baris ke-%d: ",i);
		fgets(text, sizeof(text),stdin);
		
		//input text ke file
		fputs(text,fptr);
	}
	
	printf("File berhasil di input\n");
	fclose(fptr);
		
	// membuka file
	if ((fptr = fopen("data_copy1.txt","r")) == NULL){
		printf("Error: File tidak ada!");
		// Jika file not found maka exit
		exit(1);
		}
		
	// baca isi file dengan gets lalu simpan ke buff
	printf("Output data:\n");
	while(fgets(buff, sizeof(buff), fptr)){
        printf("%s", buff);
    }
	// tutup file
	fclose(fptr);
}

