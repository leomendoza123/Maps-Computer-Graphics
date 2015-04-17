#include "bresemham.h"
#include "mainG.h"
#include "plot.h"


void *algoritmoBresemham (int X1, int Y1, int X2, int Y2)

{
    struct ColorCap blanco = {1,1,1};
    int e,ax,ay,temp;
    int s1,s2,intercambio,i,x,y;
   x=X1;
   y=Y1;
   ax=abs(X2-X1);
   ay=abs(Y2-Y1);
   s1=signo(X2-X1);
   s2=signo(Y2-Y1);
   if(ay>ax)
   {       temp=ax;
         ax=ay;
         ay=temp;
         intercambio=1;
   }
   else   {
       intercambio=0;
   }
   e=2*ay-ax;
   for(i=1;i<=ax;i++)   {
      plot(x,y, blanco);
      if(e>=0)      {
         if (intercambio==1)
         {
            x=x+s1;
         }
         else
         {
             y=y+s2;
         }
            e=e-(2*ax);
      }
      if (intercambio==1)      {
          y=y+s2;
      }
      else
      {
          x=x+s1;
      }
      e=e+2*ay;
   }

}

int signo(int num)
{
    int resultado;
    if(num<0)
       resultado=-1;
   if(num>0)
       resultado=1;
   if(num==0)
       resultado=0;
   return(resultado);

}
