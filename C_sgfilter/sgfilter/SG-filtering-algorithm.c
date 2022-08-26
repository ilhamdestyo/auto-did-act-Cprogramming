#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TWOPI (2.0*3.141592653589793)

float gauss(float x, float w, float xa) {
   return(exp(-pow(((x-xa)/w),2)));
}

float func(float x) {
   float retval=gauss(x,0.007,0.2); /* $x_1=0.2$, $w_1=0.007$ */
   retval+=gauss(x,0.01,0.4);       /* $x_2=0.4$, $w_2=0.01$ */
   retval+=gauss(x,0.02,0.6);       /* $x_3=0.6$, $w_3=0.02$ */
   retval+=gauss(x,0.04,0.8);       /* $x_4=0.8$, $w_4=0.04$ */
   retval*=4.0;
   retval+=cos(3.0*x)*pow(sin(pow(x,3)),2);
   return(retval);
}

int main(int argc, char *argv[]) {
   int k, mm=1024;
   float var=1.0,xmax=2.5, x1, x2, u, v, f, z;
   if (argc>1) sscanf(argv[1],"%f",&var); /* Read first argument as variance */
   srand((unsigned)time(NULL)); /* Initialize random number generator */
   for (k=0;k<mm-1;k+=2) {
      x1=xmax*k/((double)mm-1);
      x2=xmax*(k+1)/((double)mm-1);
      u=((float)rand())/RAND_MAX; /* Uniformly distributed over $[0,1]$ */
      v=((float)rand())/RAND_MAX; /* Uniformly distributed over $[0,1]$ */
      if (u>0.0) { /* Apply the Box--Muller algorithm on |u| and |v| */
         f=sqrt(-2*log(u));
         z=TWOPI*v;
         u=f*cos(z); /* Normally distributed with E(|u|)=0 and Var(|u|)=1 */
         v=f*sin(z); /* Normally distributed with E(|u|)=0 and Var(|u|)=1 */
         fprintf(stdout,"%1.8f %1.8f\n",x1,func(x1)+var*u); /* $f(x_1)$ */
         fprintf(stdout,"%1.8f %1.8f\n",x2,func(x2)+var*v); /* $f(x_2)$ */
      }
   }
   return(0);
}
