/*
 * incrementpointer.c
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

const int MAX = 8;

int main(int argc, char **argv)
{
	int var[] = {10,100,200,25,19,22,41,451,5426,5001};
	int i, *ptr;
	/* let us have array address in pointer */
	ptr = var;
	for ( i = 0; i < MAX; i++)
	{
		printf("Address of var[%d] = %x\n", i, ptr );
		printf("Value of var[%d] = %d\n", i, *ptr );
		/* move to the next location */
		ptr++;
	}
	return 0;
}

