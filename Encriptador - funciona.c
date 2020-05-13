#include <stdio.h>
#include <stdlib.h>

int main (){
	char c;
	char pswrd[12]; //Array de 13 caracteres
	int iter=0, i=0, j=0, x=0, y=0, z=0, contador=0;
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11];
	int U,D,C,comodin2[11], comodin3[11], comodin4[11];
	char in_file[150], out_file[150]; //Rutas de acceso a los archivos de entrada y salida
	
	//Primera parte del programa (ya comprobada y operativa)
	scanf("%12s", pswrd);//tomo la contraseÃƒÂ±a
	printf("password: %s \n", pswrd); //en un futuro metermos un bucle por si el usuario ha cometido un error
	while (i<12){
	    pswrdASCII[i]= pswrd[i]; //creamos una nueva cadena con los caracteres de la contraseÃƒÂ±a en ASCII
	    printf("%d \t", pswrdASCII[i]);// hay que revisar el bug del pswrd[9]=1 para valor null
		//guardamos en tres nuevos arrays las cifras de las unidades (Z), decenas(X) y centenas(Y) de los numeros ASCII de cada caracter
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
	while(i<12)
	{
		x=x*2+X[i];
		y=y*2+Y[i];
		z=z*2+Z[i];
		i++;
	}
	
	//Parte de manejo de ficheros
	//Lo primero que hago es pedir las rutas de acceso a los archivos.
	printf ("\nIntroduce la ruta de acceso al archivo que deseas encriptar. Si\
	\nel archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.\
	\nAdvertencia: los archivos deben ser txt\n");
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
