/*
 * struct.c
 * 
 * Copyright 2022 lime <lime@lime-ThinkPad-T450>
 * 
 * akses data struct
 * 
 */


#include <stdio.h>
#include <string.h>

struct Books{
	char title[50];
	char author[50];
	char subject[100];
	int book_id;
};
//deklarasi fungsi print book pointer
void printBook(struct Books *book);

int main(int argc, char **argv)
{
	struct Books Book1; //deklarasi buku jenis 1
	struct Books Book2; //deklarasi buku jenis 2
	
	//spesifikasi buku 1
	strcpy(Book1.title, "C Programming");
	strcpy(Book1.author, "Ilham Destyo");
	strcpy(Book1.subject, "C Programming Tutorial");
	Book1.book_id = 649587;
	
	//spesifikasi buku 2
	strcpy(Book2.title, "Paper Line");
	strcpy(Book2.author, "Mat Dog");
	strcpy(Book2.subject, "Write Book");
	Book2.book_id = 649500;
	
	/* print Book1 info */
	printBook(&Book1);
	
	/* print Book2 info */
	printBook(&Book2);
	
	return 0;
}

void printBook( struct Books *book )
{
printf( "Book title : %s\n", book->title);
printf( "Book author : %s\n", book->author);
printf( "Book subject : %s\n", book->subject);
printf( "Book book_id : %d\n", book->book_id);
}


