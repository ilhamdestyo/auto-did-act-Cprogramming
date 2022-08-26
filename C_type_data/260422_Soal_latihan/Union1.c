/*******************************************************************************
*
* Program: Union1.C
*
*******************************************************************************/
#include <stdio.h>
#include <string.h>

// definisi union Data dengan 3 variable... 
// semua variable menempati ruang yang SAMA dalam memori, 
// jadi menugaskan ke salah satu dari variable akan berpengaruh (mengubah) yang lain
union Data
{
  int x;
  double y;
  char z[32];
};

// karena union menggunakan memory yang sama, maka akan terlihat lebih sedikit daripada struct Data
struct Data2
{
  int x;
  double y;
  char z[32];
};

// Karena seringkali hanya satu variable union yang dapat digunakan
// secara efektif pada waktu tertentu, salah satu polanya adalah membungkus union dalam a
// struct di mana struct memiliki anggota (dalam hal ini tipe) yang menandakan
// variable union yang mana yang sedang 'digunakan'. Jadi jika ketik == 0 bisa
// menandakan bahwa anggota buffer x sedang digunakan, jika ketik == 1 itu bisa menandakan
// anggota buffer y sedang digunakan, dan seterusnya...
typedef struct
{
  int type;
  union {
    char x[1024];
    float y[1024];
    double z[1024];
  } buffer;
} Info;

int main()
{
  // deklarasi variable union
  union Data mydata;
  
  // inisialisasi nilai variable
  mydata.x = 10;
  mydata.y = 20.5;
  strcpy(mydata.z, "test 123");
  
  // mydata.x and mydata.z tidak mengeluarkan ouput 10 dan 20.5 karena union members
  // semua inisialisasi berada dalam satu memori
  // ketika menulis "test 123" ke mydata.z
  // maka memori yang sebelumnya akan diubah dengan hal itu (20.5)
  printf("mydata.x = %d\n", mydata.x);
  printf("mydata.y = %f\n", mydata.y);
  printf("mydata.z = %s\n", mydata.z);
  
  // jika set dan output variable secara bersamaan, maka di dapat output valuenya: 
  mydata.x = 10;
  printf("mydata.x = %d\n", mydata.x);

  mydata.y = 20.5;
  printf("mydata.y = %f\n", mydata.y);

  strcpy(mydata.z, "test 123");
  printf("mydata.z = %s\n", mydata.z);

  // union membutuhkan alokasi memori yang cukup untuk besarnya size yang di buat, 
  // dalam kasus ini 32 byte character array z
  printf("mydata size: %d\n", sizeof(mydata));
  printf("char size: %d\n", sizeof(char));
  
  // sebuah struct mengalokasikan cukup ruang untuk menyimpan SEMUA Data, dan struct dengan
  // Data yang sama akan mengambil lebih banyak space (meskipun semua Data dapat digunakan
  // secara bersamaan tanpa masalah)
  struct Data2 mydata2;
  printf("mydata2 size: %d\n", sizeof(mydata2));
  
  // akses data di union dapat dilakukan dengan pointer pada union
  // menggunakan arrow notation -> sama halnya seperti structs
  union Data *ptr = &mydata;
  printf("ptr->z = %s\n", ptr->z);
  
  // struct info memiliki banyak Data
  Info info;

  // set ke '0' untuk signify x var buffer 
  info.type = 0;
  
  // write all 't' characters ke buffer.x 
  memset(info.buffer.x, 't', 1024);
  
  // kemudian cek sebelum melakukan apapun
  //if (info.type == 0)
  //{
    //for (int i = 0; i < 1024; i++)
      //printf("info.buffer.x[%d] = %c\n",
             //i, info.buffer.x[i]);
  //}
  
  return 0;
}
