#include<stdio.h>
int main (){
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11], comodin2[11], comodin3[11], comodin4[11];
	int iter=0, i=0;
	char pswrd[12]; //creo un arrai de 13 numeros
	scanf("%12s", pswrd);//tomo la contraseÃ±a
	printf("password: %s \n", pswrd); //en un futuro metermos un bucle por si el usuario ha cometido un error
	while (i<12){
	    pswrdASCII[i]= pswrd[i]; //creamos una nueva cadena con los caracteres de la contraseÃ±a en ASCII
	    	printf("%d \t", pswrdASCII[i]);// hay q revisar el bug del pswrd[9]=1 para valor null
		//guardamos en tres nuevos arrais las cifras de las unidades (Z), decenas(X) y centenas(Y) de los numeros ASCII de cada caracter
		Z[i]= pswrdASCII[i]%10;
	    Y[i] = (pswrdASCII[i]-Z[i])%100;
	    X[i]= (pswrdASCII[i]-Z[i]-Y[i])/100;
	    Y[i] /= 10;
	  		printf("%d, %d, %d \t", X[i],Y[i],Z[i]);
		//Voy ahora a comparar los valores en ascii y dar valor 1 a los pares y 0 a los impares.
	if(X[i]%2==0){
		    X[i]=0;
	    }else{
		    X[i]=1;
		}
	if(Y[i]%2==0){
		    Y[i]=0;
	    }else{
		    Y[i]=1;
	}if(Z[i]%2==0){
		    Z[i]=0;
	    }else{
		    Z[i]=1;
	}
	    i++;
    }
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
		while (i<12){ //en este bucle desplazaremos los valores de las cadenas una posicion (Valores de X en Y, Y en Z, Z en T y T en X)
			comodin2[i]=Y[i];	//guardamos componentes de Y
			Y[i]=X[i];			//en 
			comodin3[i]=Z[i];
			Z[i]=comodin2[i];
			comodin4[i]=T[i];
			T[i]=comodin3[i];	
			X[i]=comodin4[i];
			i++;	
		}
		i=0;
		while (i<12){
		printf("%d \t ", T[i]);	
	    i++;}
	iter++;
	}

}

//una vez pasemos por todas las iteraciones tendremos tres cadenas UDC en binario,
//vamos a reunir los parámetros y pasarlos de binario a decimal
//FUNCION PASAR DE BINARIO A DECIMAL
i=0;x=0;y=0;z=0;
j=pow(10,12);
while(i<12){
	x=x*2+X[i];
	y=y*2+Y[i];
	z=z*2+Z[i];
	i++;
}
 //una vez hecho vamos a abrir el archivo, esta parte tenemos que tratarla todavía
FILE *txt;

int *txtASCII;
 txt=fopen ("encript.txt", "r"); //abrir archivo
char p;
i=0;
 while (!fscanf(txt, &p) == EOF){
 	i++;
 }
 cont=i;
 txtASCII=malloc(sizeof(int)*cont); 	//malloc, punteros
 if (txtASCII==NULL){
 	printf("ERROR");
 	exit(-1);
 }
 i=0;
  while (!fscanf(txt, &p) == EOF){
  	*txtASCII= &p; //Si buscas asignar cada valor leido en char a ASCII->*(txtASCII+i)=p
 	i++;           //si has visto una mejor manera para hacerlo evita mi comentario.
 }
 fclose(txt);