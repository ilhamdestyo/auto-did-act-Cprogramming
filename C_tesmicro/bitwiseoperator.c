// C Program to demonstrate use of bitwise operators
#include <stdio.h>
int main(int argc, char *argv[])
{
	// a = 5(00000101), b = 9(00001001)
	unsigned char a = 5, b = 9;

	
	printf("a = %d, b = %d\n", a, b);
	
	// AND operator// The result is 00000001 = 1 in decimal. The result of AND is 1 only if both bits are 1
	printf("a&b = %d\n", a & b);

	// OR operator// The result is 00001101 = 13 in decimal. The result of OR is 1 if any of the two bits is 1
	printf("a|b = %d\n", a | b);

	// XOR operator// The result is 00001100 = 12 in decimal. The result of XOR is 1 if the two bits are different
	printf("a^b = %d\n", a ^ b);

	// NOT operator// The result is 11111010 = 250 in decimal. The result is inverts all bits
	printf("~a = %d\n", a = ~a);

	// LEFT SHIFT operator// The result is 00010010 = 18 in decimal
	printf("b<<1 = %d\n", b << 1);
	
	// LEFT SHIFT operator// The result is 00010010 = 18 in decimal
	printf("1<<0 = %d\n", 1 << 0);
	printf("1<<1 = %d\n", 1 << 1);
	printf("1<<2 = %d\n", 1 << 2);
	printf("1<<3 = %d\n", 1 << 3);
	printf("1<<4 = %d\n", 1 << 4);
	printf("1<<5 = %d\n", 1 << 5);
	printf("1<<6 = %d\n", 1 << 6);
	printf("1<<7 = %d\n", 1 << 7);

	// RIGHT SHIFT operator// The result is 00000100 = 4 in decimal
	printf("b>>1 = %d\n", b >> 1);

	return 0;

}
