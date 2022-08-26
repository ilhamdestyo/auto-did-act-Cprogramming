#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int datainput_1[99999],datainput_2[99999],datainput_3[99999];
int number_data;
char *txtResult = NULL;
char datain1[200],dataraw[999999][200];

typedef struct{
 char **Input1;
 char **Input2;
 char **Input3;
 int ndata;
} dataInput;

char* replaceWordInString(const char* s, const char* oldW, const char* newW){ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++; 
            i += oldWlen - 1; 
        } 
    } 
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) { 
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0';
    //~ free(result),result=NULL; 
    return result; 
}

char *trim(char *s) {
	int count = -1;
	for(int i=0;i<strlen(s)+1;i++){
		if(isspace(s[i])==0){
			count = i;
			break;
		}
	}
	
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=count;i<strlen(s)+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	return result;
}

char *shift_trim(char *s) {
	int count;
	for(int i=1;i<strlen(s)+1;i++){
		count = strlen(s)-i;
		if(isspace(s[count])==0){
			count = strlen(s)-i;
			break;
		}
	}
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=0;i<count+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	//~ result = trim(result);
	return result;
}

char *IntToStr(int x){
	char *str=(char *)malloc(10 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

void read_file(char *namafile){
	FILE *fileinput = fopen(namafile, "r");
    
    char *tmptxt,*tmptxt1,*tmptxt2;
	int i = 0;
	int j = 0;
	while(!feof(fileinput)){
		i++;
		fgets(datain1,200,fileinput);
		tmptxt = shift_trim(datain1);
		tmptxt2 = trim(tmptxt);
		strcpy(dataraw[i], tmptxt2);
		if(strlen(dataraw[i])>=0){
			tmptxt1 = shift_trim(datain1);
			j++;strcpy(dataraw[j], tmptxt1);
			free(tmptxt1),tmptxt1=NULL;
		}
		
		free(tmptxt),tmptxt=NULL;
		free(tmptxt2),tmptxt2=NULL;
	}
	
	fclose(fileinput);
	number_data = j;

	if(strlen(dataraw[number_data]) == strlen(dataraw[number_data-1])){number_data=j-1;}
	else{number_data = j;}
}

void get_data_from_rawdata(){
	char *datain1,*datain2,*datain3;
	datain1 = calloc(100,sizeof(char));
	datain2 = calloc(100,sizeof(char));
	datain3 = calloc(100,sizeof(char));
	for(int i=1;i<number_data+1;i++){
		txtResult = replaceWordInString(dataraw[i],","," ");
		sscanf(txtResult,"%s  %s  %s ",datain1,datain2, datain3);
		datainput_1[i] = atoi(datain1);
		datainput_2[i] = atoi(datain2);
		datainput_3[i] = atoi(datain3);
		free(txtResult),txtResult=NULL; 
	}
	free(datain1),datain1=NULL;
	free(datain2),datain2=NULL; 
	free(datain3),datain3=NULL;
}

void save_data_file(char *namafile, dataInput datatulis){
	FILE *fileoutput = fopen(namafile, "w"); 
    for (int i = 1;i < (datatulis.ndata+1);i++){
		fprintf(fileoutput, "%s %s %s \n",  datatulis.Input1[i], datatulis.Input2[i],datatulis.Input3[i]);
	}
    fclose(fileoutput);
}

int c_round(double x){
	return x < 0 ? x - 0.5 : x + 0.5;
}

double c_modulus(double a,double b){
	double tempres;
	tempres = c_round(b*((double)(a/b)-(int)(a/b)));
	return tempres;
}

int isGanjil(int num)
{
	if (num == 0 || num == 1)
		return 1;
	else
		return (c_modulus(num,2) == 0 ? 0 : 1) ;
}
