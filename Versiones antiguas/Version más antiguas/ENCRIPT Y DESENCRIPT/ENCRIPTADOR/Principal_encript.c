#include <stdio.h>
#include <stdlib.h>
#include "Funciones_encript.h"

int main (){
	char c;
	char pswrd[12]; //Array de 13 caracteres
	int iter=0, i=0, j=0, x=0, y=0, z=0, contador=0;
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11];
	int U,D,C,comodin2[11], comodin3[11], comodin4[11];
	char in_file[150], out_file[150]; 
	
	fpswrd (pswrd); //FUNCIÓN (Contraseña).
        			  
	while (i<12){
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
		
		Func_Desplz(X,Y,Z,T);//(Valores de X en Y, Y en Z, Z en T y T en X)

		i=0;
		while (i<12){
		printf("%d \t ", T[i]);	
	    i++;}
	iter++;
	}
	
	
	
	
	//Parte de manejo de ficheros
	//Lo primero que hago es pedir las rutas de acceso a los archivos.
	printf ("\nIntroduce la ruta de acceso al archivo que deseas encriptar. Si\
	\nel archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.\n");
	fflush (stdin); //Limpio el buffer de entrada
	scanf ("%[^\n]s", in_file);
	FILE *fichero1;
	FILE *fichero2;
	
	printf ("\nAbriendo el fichero de lectura %s\n", in_file);
	fichero1 = fopen (in_file, "r");
	if (fichero1==NULL){
		printf ("Error en la apertura del fichero.\n");
		return -1;
	}
	printf ("Fichero abierto correctamente.\n");
	while (fscanf(fichero1, "%c", &c)!=EOF){
		contador++;
	}
	printf ("El fichero tiene %i caracteres.\n", contador);
	rewind (fichero1);
	
	//Asignación dinámica de memoria para crear un vector de la misma longitud que el fichero
	char *txtASCII;
	txtASCII = malloc (sizeof(char)*contador);
	
	printf ("Crear/abrir el fichero de salida:\
	\nIntroduce la ruta de acceso.\
	\nADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n");
	//En el futuro puede añadirse una función que intente abrir el archivo especificado
	//y que si existe lo advierta y de opción a cambiar el nombre de archivo si se desea
	fflush(stdin);
	scanf ("%[^\n]s", out_file);
	fichero2 = fopen (out_file, "w");
	if (fichero2 == NULL){
		printf ("Error en la apertura/creacion del fichero de salida.\n");
	}
	
	printf ("Encriptando y guardando en el archivo de salida...\n");
	i=0;
	while (fscanf(fichero1, "%c", (txtASCII+i))!=EOF){
		//Añadir el hash y
		//Operaciones para que no exceda los valores permitidos
		//c1 = c+1; //Con las debidas operaciones, esto es temporal
		if (j==12)
			j=0; //Vuelve a recorrer el hash cuando llega a su fin (12 posiciones)
		*(txtASCII+i) += pswrdASCII[j];
		while (*(txtASCII+i)>255)
			*(txtASCII+i)-=255;
		fprintf (fichero2, "%c", *(txtASCII+i));
		j++;
		i++;
	}
	printf ("Fichero escrito, cerrando...");
	
	fclose (fichero1);
	fclose (fichero2);
	free (txtASCII);
	return 0;
}
