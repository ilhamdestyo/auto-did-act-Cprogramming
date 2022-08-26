#include<stdio.h>
int main()
{
	int i,j,k;
	int a[3][3];                    //deklarasi 2D array pertama
	int b[3][3];					//deklarasi 2D array kedua
	printf("enter the elements in array a: \n");        //input elemen 'a'   
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("element at [%d][%d]: ",i,j);
			scanf("%d",&a[i][j]);
		}
	}
	printf("\nprinting 2D array a\n");                 //print array 'a'
	for(i=0;i<3;i++)                        
	{   
		for(j=0;j<3;j++)
		{
			printf("%d ",a[i][j]);	
		}
		printf("\n");
	}
	printf("\nenter the elements in array b: \n");     //input elemen 'b' 
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("element at [%d][%d]: ",i,j);
			scanf("%d",&b[i][j]);
		}
	}
	printf("\nprinting 2D array b\n");                 //print array 'b'
	for(i=0;i<3;i++)                        
	{   
		for(j=0;j<3;j++)
		{
			printf("%d ",b[i][j]);	
		}
		printf("\n");
	}
	int arr[3][3][3];                                  //deklarasi 3D array
	printf("\ncopying values in 3D array: \n");
	for(i=0;i<2;i++)
	{   
		for(j=0;j<3;j++)                 
		{
			for(k=0;k<3;k++)
			{
				if(i==0)
				{
					arr[i][j][k]=a[j][k];              //copy elemen 2D ke 3D
				}
				else
				{
					arr[i][j][k]=b[j][k];
				}
			}
		}
	}
	printf("\nprinting elements in 3D array: \n");    //print elemen 3D
	for(i=0;i<2;i++)
	{   
		for(j=0;j<3;j++)                 
		{
			for(k=0;k<3;k++)
			{
			printf("%d ",arr[i][j][k]);
			if(k==2)
			{
			printf("\n");
			}
			}
		}
		printf("\n");
	}
	return 0;				
}
