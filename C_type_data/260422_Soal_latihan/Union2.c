#include <stdio.h>

union Kerja {
   float gaji;
   int workerNo;
} j;

int main() {
   j.gaji = 12.3;
   // ketika j.workerNo diberi nilai,
   // j.salary tidak akan lagi memberi output 12.3
   j.workerNo = 100;

   printf("sebelum berurutan:\n Salary = %.1f\n", j.gaji);
   printf("Number of workers = %d\n", j.workerNo);
   
   
   //akan tetapi jika berurutan
   j.gaji = 12.3;
   printf("Setelah berurutan:\n Salary = %.1f\n", j.gaji);
   j.workerNo = 100;
   printf("Number of workers = %d\n", j.workerNo); 
   return 0;
}
