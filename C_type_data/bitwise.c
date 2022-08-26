/*
 * bitwise.c
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
int main()
{
unsigned int a = 60; /* 60 = 0011 1100 */
unsigned int b = 13; /* 13 = 0000 1101 */
int c = 0;
c = a & b;
/* 12 = 0000 1100 */
printf("Line 1 - Value of c is %d %x\n", c, c );
c = a | b;
/* 61 = 0011 1101 */
printf("Line 2 - Value of c is %d %x \n", c, c );
c = a ^ b;
/* 49 = 0011 0001 */
printf("Line 3 - Value of c is %d\n", c );
c = ~a;
/*-61 = 1100 0011 */
printf("Line 4 - Value of c is %d\n", c );
c = a << 2;
/* 240 = 1111 0000 */
printf("Line 5 - Value of c is %d\n", c );
c = a >> 2;
/* 15 = 0000 1111 */
printf("Line 6 - Value of c is %d\n", c );
}
