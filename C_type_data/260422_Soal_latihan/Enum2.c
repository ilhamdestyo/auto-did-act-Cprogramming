/*******************************************************************************
*
* Program: enum1.c
* 
* Description: Example of using enum in C. 
*
* Author: ilham destyo
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum {CRITICAL, NOMINAL, OFFLINE} status_t;

status_t siaga1_status = CRITICAL;

int main(){
	status_t siaga2_status = NOMINAL;
	
	switch(siaga2_status)
	{
		case OFFLINE:
		puts("Zona Hijau, Aman!!!");
		break;
		case NOMINAL:
		puts("Zona Kuning, Waspada!!!");
		break;
		case CRITICAL:
		puts("Zona Merah, BAHAYA!!!");
		break;
		default:
		puts("Cek Status...");
		break;
	}
}
