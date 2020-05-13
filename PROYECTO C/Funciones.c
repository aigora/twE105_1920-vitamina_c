#include "Funciones.h"
char fpswrd (char pswrd[12])
{
	scanf("%12s", pswrd);
	printf("password: %s \n", pswrd);
}
//
int Char_a_ASCII(char pswrd[12], int ASCII[11])
{
	int i=0;
	while(i<12)
	{
		ASCII[i]= pswrd[i];
	i++;	
	}		
}
//
int UDC (int pswrdASCII[11],int X[11],int Y[11],int Z[11])
{
		int i;
		while (i<12)
		{
				Z[i]= pswrdASCII[i]%10;
	            Y[i] = (pswrdASCII[i]-Z[i])%100;
	            X[i]= (pswrdASCII[i]-Z[i]-Y[i])/100;
	            Y[i] /= 10;
	    i++;    
		}		
}
//
int ASCII_a_01(int X[11],int Y[11],int Z[11])
{
  int i=0;
    while(i<12)
        {
  	        if(X[i]%2==0)
  	            X[i]=0;
        	else
     	        X[i]=1;
	        
	          
			if(Y[i]%2==0)
  	            Y[i]=0;
	        else
	            Y[i]=1;
	        
	  
	        if(Z[i]%2==0)
  	            Z[i]=0;
	        
	        else
	            Z[i]=1;
	        
	    i++;
        }
  return 0;
}

//
int Func_Desplz(int X[11],int Y[11],int Z[11],int T[11])
{
	printf("hola");
	int comodin2[11], comodin3[11], comodin4[11];
	int i=0;
		while (i<11)
		{ 
			comodin2[i]=Y[i];	
			Y[i]=X[i];			
			comodin3[i]=Z[i];
			Z[i]=comodin2[i];
			comodin4[i]=T[i];
			T[i]=comodin3[i];	
			X[i]=comodin4[i];
			i++;	
		}
		
	printf("hola");
	return 0;
}
//
unsigned long int binarioADecimal(int *p, int longitud)
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

