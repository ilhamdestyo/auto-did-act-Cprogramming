#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int datainput_1[99999],datainput_2[99999],datainput_3[99999];
extern int number_data;
static char *txtResult = NULL;
static char datain1[200],dataraw[999999][200];

typedef struct{
 char **Input1;
 char **Input2;
 char **Input3;
 int ndata;
} dataInput;

char* replaceWordInString(const char* s, const char* oldW, const char* newW);

char *trim(char *s);

char *shift_trim(char *s);

char *IntToStr(int x);

void read_file(char *namafile);

void get_data_from_rawdata();

void save_data_file(char *namafile, dataInput datatulis);

int c_round(double x);

double c_modulus(double a,double b);

int isGanjil(int num);
