/*
 * arraypointer.c
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

const int MAX = 4;

int main ()
{
	char *names[] = {
		"Zara Ali",
		"Hina Ali",
		"Bully Ali",
		"Sara Ali",
	};
	
	int i = 0;
	for ( i = 0; i < MAX; i++){
		printf("Value of names[%d] = %s\n", i, names[i] );
	}
return 0;
}
