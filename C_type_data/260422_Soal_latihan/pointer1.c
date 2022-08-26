/* Display a software timer. */ 
   #include <stdio.h> 
   #define DELAY 128000
struct new_timer { int hr; int min; int sec; 
}; 
void display(struct new_timer *t); void update(struct new_timer *t); void delay(void); 
   int main(void)
   {
struct new_timer curtime; 
curtime.hr = 0; curtime.min = 0; curtime.sec = 0; 
     for(;;) {
       update(&curtime);
       display(&curtime);
} 
return 0; } 
void update(struct new_timer *t) { 
t->sec++; if(t->sec==60) { 
t->sec = 0; 
t->min++; } 
if(t->min==60) { t->min = 0; t->hr++; 
} 
if(t->hr==24) t->hr = 0; 
delay(); } 
void display(struct new_timer *t) { 
printf("%02d:", t->hr); printf("%02d:", t->min); printf("%02d\n", t->sec); 
} 
   void delay(void)
   {
    long int t; 
     /* can be changed as per need */
     for(t=1; t<DELAY; ++t) ;
   }
