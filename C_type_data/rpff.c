/*
 * rpff.c
 * 
 * Copyright 2022 lime <lime@lime-ThinkPad-T450>
 * 
 * Representation of Return Pointer from Function code
 * 
 */


#include <stdio.h>
#include <time.h>

/*function to generate and return random number */
int *getRandom(){
	static int r[10];
	int i;
	
	/*set the seed*/
	srand ( (unsigned) time ( NULL ) );
	for(i=0;i<10;++i){
		r[i]=rand();
		printf("%d %x\n",r[i],r[i]);
	}
	
	return r;
}

/* main function to call above defined function */
int main ()
{
	/* a pointer to an int */
	int *p;
	int i;
	p = getRandom();
	
	for ( i = 0; i < 10; i++ )
	{
		printf("*(p + [%d]) : %d %x\n", i, *(p + i), i );
	}
	
	return 0;
}

