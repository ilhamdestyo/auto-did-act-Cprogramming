/*
 * Assignment_opt.c
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
void main()
{
int a = 21;
int c ;
c = a;
printf("Line 1 - = Operator Example, Value of c = %d\n", c );
c += a;
printf("Line 2 - += Operator Example, Value of c = %d\n", c );
c -= a;
printf("Line 3 - -= Operator Example, Value of c = %d\n", c );
c *= a;
printf("Line 4 - *= Operator Example, Value of c = %d\n", c );
c /= a;
printf("Line 5 - /= Operator Example, Value of c = %d\n", c );
c = 200;
c %= a;
printf("Line 6 - %= Operator Example, Value of c = %d\n", c );
c <<= 2;
printf("Line 7 - <<= Operator Example, Value of c = %d\n", c );
c >>= 2;
printf("Line 8 - >>= Operator Example, Value of c = %d\n", c );
c &= 2;
printf("Line 9 - &= Operator Example, Value of c = %d\n", c );
c ^= 2;
printf("Line 10 - ^= Operator Example, Value of c = %d\n", c );
c |= 2;
printf("Line 11 - |= Operator Example, Value of c = %d\n", c );
}
