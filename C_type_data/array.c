/*
 * array.c
 * 
 * Copyright 2022 lime <lime@lime-ThinkPad-T450>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

int main (){
	/*array dengan 5 element*/
	double balance[5] = {1000.0, 2.0, 3.4, 17.0, 50.0};
	double *p;
	int i;
	
	p = balance;
	
	/*nilai dari output elemen array*/
	printf("Array value using pointer\n");
	for ( i = 0; i < 5; i++ ){
		printf("*(p + %d) : %f\n",i, *(p + i) );
		}
	printf( "Array values using balance as address\n");for ( i = 0; i < 5; i++ ){
		printf("*(balance + %d) : %f\n",i, *(balance + i) );
		}
	return 0;
}
		 
