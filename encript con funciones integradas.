#include<stdio.h>

char fpswrd (char pswrd[12]);
int Char_a_ASCII(char pswrd[12] );
void UDC (int pswrdASCII[11]);
int ASCII_a_01(int X[11],int Y[11],int Z[11]);
int Func_Desplz(int X[11],int Y[11],int Z[11],int T[11]);
unsigned long int binarioADecimal(int *p, int longitud);


int main ()
{
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11], comodin2[11], comodin3[11], comodin4[11];
	int iter=0, i=0;
	char pswrd[12]; 
	 
	fpswrd (pswrd);//función--> contraseña.
	
	Char_a_ASCII(pswrd);//función--> paso de caracteres a ASCII.
	    
	while (i<12)
        {
		printf("%d \t", pswrdASCII[i]);
        i++;
		}
		
	UDC (pswrdASCII);//función--> unidades,centenas,decenas.
    while (i<12)
	{
	    printf("%d, %d, %d \t", X[i],Y[i],Z[i]);
	    i++;
    }
	
	
	ASCII_a_01(X, Y, Z);//función--> paso de ASCII(par o impar) a binario
	printf("\n");


    while(iter<6)
	{
    	i=0;
    	printf("\n Valor nueva cuarta componente \n");
	    while(i<12){ //vamos a crear un ultimo arrai que obtenga su valor dependiendo de comparar X,Y y Z; teniendo en cuenta permutaciones positivas y negativas
	    	if(i%2==0){
	    		if(X[i]==Z[i]){
	    			T[i]=1;
				}else{
					T[i]=0;
				}
	    	}else{
	    		if(Y[i]==Z[i]){
	    			T[i]=1;
				}else{
					T[i]=0;
				}
			}
			printf("%d \t", T[i]);
	    i++;
		}
		printf("\n aqui hay una iteracion \n");
		i=0;
	iter++;		
    }
			
	    Func_Desplz(X,Y,Z,T);	//función --> desplazamiento (X=Y,Y=Z,...)
	
        while (i<12)
		{
		printf("%d \t ", T[i]);	
	    i++;
		}
}








//
char fpswrd (char pswrd[12])
{
	scanf("%12s", pswrd);
		printf("password: %s \n", pswrd);
}
//
int Char_a_ASCII(char pswrd[12])
{
	int i,pswrdASCII[11];
	i=0;
	while(pswrd[i]!='\0')
	{
		pswrdASCII[i]=pswrd[i];
	}
	i++;
	return pswrdASCII[11];
}
//
void UDC (int pswrdASCII[11])
{
		int X[11], Y[11], Z[11];
		int i;
		
		while (pswrdASCII[i]='\0')
		{
				Z[i]= pswrdASCII[i]%10;
	            Y[i] = (pswrdASCII[i]-Z[i])%100;
	            X[i]= (pswrdASCII[i]-Z[i]-Y[i])/100;
	            Y[i] /= 10;
	        i++;    
		}
	return 	X[11], Y[11], Z[11];
		
}
//
int ASCII_a_01(int X[11],int Y[11],int Z[11])
{
  int i;
  i=0;
  while(i<=11)
  {
  	 if(X[i]%2==0)
  	 {
  	 	X[i]=0;
	 }
	 else
	 {
	 	X[i]=1;
	 }
	  if(Y[i]%2==0)
  	 {
  	 	Y[i]=0;
	 }
	 else
	 {
	 	Y[i]=1;
	 }
	  if(Z[i]%2==0)
  	 {
  	 	Z[i]=0;
	 }
	 else
	 {
	 	Z[i]=1;
	 }
  }
  i++;
  return 0;
}
//
int Func_Desplz(int X[11],int Y[11],int Z[11],int T[11])
{
	int comodin2[11], comodin3[11], comodin4[11];
	int i=0;
		while (i<=11)
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
		i=0;
		
		
}
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
//
