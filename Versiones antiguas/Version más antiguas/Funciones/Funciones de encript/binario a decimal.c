//Es una prueba para ver si funcionaba
#include <stdio.h>
unsigned long int binarioADecimal(int *p, int longitud);
void main ()
{
 int i ,n,T[11],decimal;
 scanf("%i",&n);
 for(i=0;i<n;i++)
 scanf("%i",&T[i]);
 decimal=binarioADecimal(T,n);
 printf("%i",decimal);
}
//Aqui acaba la prueba
unsigned long int binarioADecimal(int *p, int longitud)//Funcion
{
  unsigned long long decimal = 0;
  int multiplicador = 1,i,numeroActual;
  for ( i = longitud-1; i >= 0; i--) 
  {
    numeroActual = *(p+i);
    if (numeroActual ==1) 
	{
      decimal+= multiplicador;
    }
    multiplicador = multiplicador * 2;
  }
  return decimal;
}
