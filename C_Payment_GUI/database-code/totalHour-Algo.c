#include <stdio.h>
float rate(char,int,int);

int main()
{
	int jamMasuk, jamKeluar;
	float r;
	char type;

	printf("UID check: ");
	scanf("%c", &type);
	
	printf("\n");
	// check for type of vehicle
	if (type == 'A' || type == 'a' || type == 'b' || type == 'B')
	{
		printf("Jam Masuk ( from 0 to 24):");
		scanf("%d", &jamMasuk);
		printf("\n");

		printf("Jam Keluar ( from 0 to 24):");
		scanf("%d", &jamKeluar);
		printf("\n");

		r = rate(type, jamMasuk, jamKeluar);
		printf("The parking fee =%.2f $\n", r);
		
	}
	else
	{
		printf("Input UID Failed\n");
		return 0;
	}
	
	
	return 0;
}

// Kalkulasi Tarif
float rate(char tarif,int x, int y){
	float rate = 0;
	switch (tarif)
	{
	case 'A':
	case 'a':if (y - x <= 3)
		{
		 rate = 0;
		 break;
		}
		 else
		{
		    rate = ((y - x)*1.50);
		    break;
		 }
	case 'B':
	case'b' :
	    if (y - x <= 2)
		{
		    rate = (y - x);
		    break;
		}
		 else
		 {
			 rate = ((y - x)*2.30);
			 break;
		}
	default:
	    break;
	}
	return rate;
}
