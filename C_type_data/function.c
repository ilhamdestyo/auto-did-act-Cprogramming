#include <stdio.h>
/* function declaration */
void swap(int *x, int *y){
	int temp;
	
	temp = *x;
	*x=*y;
	*y= temp;
}


/* function declaration */
void swap(int *x, int *y);
int main ()
{
/* local variable definition */
int a = 100;
int b = 200;
printf("Before swap, value of a : %d\n", a );
printf("Before swap, value of b : %d\n", b );
/* calling a function to swap the values.
* &a indicates pointer to a i.e. address of variable a and
* &b indicates pointer to b i.e. address of variable b.
*/
swap(&a, &b);
printf("After swap, value of a : %d\n", a );
printf("After swap, value of b : %d\n", b );
return 0;
}
