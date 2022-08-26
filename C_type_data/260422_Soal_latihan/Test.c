/*******************************************************************************
*
* Program: enum1.c
* 
* Description: Example of using enum in C. 
*
* Author: ilham destyo
*
*******************************************************************************/
#include <stdio.h>

/* penggunaan enum untuk membuat 'new type' Day yang berisi dari Day Monday - Sunday.
 * sehingga digunakan nilai yang menunjukkan Monday, Tuesday, dst, untuk program.
 * nilai dimulai dari 0 increment sebanyak 1 kali sampai seterusnya,
 * Monday=0, Tuesday=1, Wednesday=3, dan seterusnya.
 * pada enum dapat mengganti dan mengatur value seperti pada Tuesday dan Friday di bawah ini.
 * enum sebenarnya bukan tipe baru tetapi merupakan cara untuk 
 * mendefinisikan kumpulan nilai konstanta terkait.*/
enum Day { Monday, Tuesday = 9, Wednesday, Thursday, Friday = 20, 
          Saturday, Sunday};

// deklarasi typedef yang merepresentasikan enum
typedef enum button { ON, OFF } Button;

// function dan parameter untuk enum
Button press(Button current);
void print_button(Button current);

int main(void)
{
  //deklarasi tipe data Day dengan hari yang diinginkan
  enum Day today = Tuesday;
  enum Day yesterday = Monday;
  enum Day tomorrow = Wednesday;

  // print out enum %d sebagai pengganti integer
  printf("Yesterday: %d\n", yesterday);
  printf("Today: %d\n", today);
  printf("Tomorrow: %d\n", tomorrow);
  printf("Friday: %d\n", Friday);

  // deklarasi dan inisalisasi button
  Button power = ON;

  // memanggil fungsi dengan button
  print_button(power);
  power = press(power);
  print_button(power);
  power = press(power);
  power = press(power);
  print_button(power);

  return 0;
}

// membalik status tombol dengan mengembalikan kebalikan dari value saat ini
Button press(Button current)
{
  if (current == ON) return OFF;
  else return ON;
}

// prints a string ON or string OFF untuk keterangan button
void print_button(Button current)
{
  if (current == ON) printf("ON\n");
  else if (current == OFF) printf("OFF\n");
}
