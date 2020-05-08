#include <stdio.h>
#include "Funciones.h"

int main (){
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11],U,D,C,comodin2[11], comodin3[11], comodin4[11];
	int iter=0,j=0,i=0,x=0,y=0,z=0,cont;
	char pswrd[12],p;
	
	fpswrd (pswrd); //FUNCIÓN (Contraseña).
   			  
	while (i<12)
	{
	    Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)
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
	
	
	while(i<12)
	{
		x=x*2+X[i];
		y=y*2+Y[i];
		z=z*2+Z[i];
		i++;
	}

 //una vez hecho vamos a abrir el archivo, esta parte tenemos que tratarla todavÃ­a
	FILE *txt,*txt2;

	int *txtASCII;
 	txt=fopen ("encript.txt", "r");
 	if(txt==NULL)
 	{
   	printf("Error");
   	return(-1);
	}                     

	txtASCII=malloc(sizeof(txt));
	if (txtASCII==NULL){
 		printf("Error en asignacion malloc");
 		exit(-1);
 	}
 	txt2=fopen("encript2.txt","w");
	if(txt2==NULL)
	{
	printf("Error txt2");
	}
	printf("procediendo a leer por segunda vez");//Rewind
  	while ((p=fgetc(txt))!=EOF){
  	printf("pq no funcionas");
  	if(j==12)
  	j=0;
  	*(txtASCII+i)=p;
	*(txtASCII+i)+=pswrdASCII[j];
	while(*(txtASCII+i)>255){                                 //Lo que estamos haciendo es acotar el numero obtenido para que sea positivo y [0,255]
	*(txtASCII+i)-=255;
	}
	 	fprintf(txt2,"%c",*(txtASCII+i));  //Se puede asignar char a ascii //se imprime el valor entero como char
	i++;                                   
	j++;                                  
	}
	printf("hola");
 	fclose(txt2);
 	fclose(txt);
 	free(txtASCII);
 	return 0;
	}
		
