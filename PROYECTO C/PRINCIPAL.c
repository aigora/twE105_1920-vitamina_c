#include <stdio.h>
#include "Funciones.h"

int main (){
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11],comodin2[11], comodin3[11], comodin4[11];
	int iter=0, i=0;
	char pswrd[12]; 
	
	fpswrd (pswrd); //FUNCIÓN (Contraseña).
    printf("P");    			  
	while (i<12)
	{
	    Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)
	        //pswrdASCII[i]= pswrd[i];
	        printf("%d \t", pswrdASCII[i]);	
	    
		UDC (pswrdASCII, X, Y, Z); //FUNCIÓN (Pasamos ASCII a unidades,decenas y centenas)
			printf("%d, %d, %d \t", X[i],Y[i],Z[i]);
	i++;
    }
	
	ASCII_a_01(X,Y,Z);//FUNCIÓN (X Y Z a binario)
	printf("\n");



    while(iter<6){
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
		
		//Func_Desplz(X,Y,Z,T); //(Valores de X en Y, Y en Z, Z en T y T en X)
		while (i<12){ //en este bucle desplazaremos los valores de las cadenas una posicion (Valores de X en Y, Y en Z, Z en T y T en X)
			comodin2[i]=Y[i];	
			Y[i]=X[i];			 
			comodin3[i]=Z[i];
			Z[i]=comodin2[i];
			comodin4[i]=T[i];
			T[i]=comodin3[i];	
			X[i]=comodin4[i];
			i++;	
		}
        //Func_Desplz(X,Y,Z,T); //(Valores de X en Y, Y en Z, Z en T y T en X)
        
        
		i=0;
		while (i<12){
		printf("%d \t ", T[i]);	
	    i++;}
	iter++;
	}
}
