#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include"grafikeame.h"
#include "usuarios.h"
int main (){
	char c;
	char pswrd[12]; //Array de 13 caracteres
	int iter=0, i=0, j=0, x=0, y=0, z=0, contador=0;
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11];
	int U,D,C,comodin2[11], comodin3[11], comodin4[11];
	char in_file[150], out_file[150]; 
	inicio_normal();
	FILE *fichero1;
	FILE *fichero2;
	char *txtASCII;
	char respuesta;
	_Bool continuar = 0;
	funcion_espera();
	graf_logo();

	while (continuar==0){//El programa se ejecuta indefinidamente hasta que el usuario decide salir
		graf_logo();

	printf ("\nOPCIONES:\n	1.Encriptar un archivo.\n	2.Desencriptar un archivo.\n	3.Salir.\n\n");
	scanf("%i",&x);
	system("cls");
	system("clear");
	switch (x){
			case 1:
				printf("\n \nExcelente, comencemos con la encriptacion...\n");
				printf("\nIntroduzca la password (recomendamos una password de 12 caracteres para un mejor funcionamiento): \n	");				
				fpswrd (pswrd); //FUNCIÓN (Contraseña).
			        			  
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÓN (Pasamos ASCII a unidades,decenas y centenas)
					i++;
			    }
				
				ASCII_a_01(X,Y,Z);//FUNCIÓN (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //Iteración para hash
			    	i=0;
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
				    i++;
					}
			
					
					Func_Desplz(X,Y,Z,T);//(Valores de X en Y, Y en Z, Z en T y T en X)
			
				i=0;
				iter++;
				}
				system("cls");
				system("clear");
				printf ("\nIntroduce la ruta de acceso del archivo .txt que deseas encriptar.\
				\n[Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.]\n \n	");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
				system("cls");
				system("clear");
				printf ("\nAbriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a encriptar
					printf ("\tError en la apertura del fichero.\n");
					printf ("\n\nPrograma finalizado, pulse cualquier tecla seguida de intro para salir\n");
					fflush(stdin);
					scanf ("%c");
					return -1;
				}
				printf ("	Fichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nº caracteres
				contador++;
				}
				printf ("		El fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//Asignación dinámica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				printf ("\n \nIntroduce la ruta de acceso para el fichero de salida.\
						\n	ADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n\n	");
				//En el futuro puede añadirse una función que intente abrir el archivo especificado
				//y que si existe lo advierta y de opción a cambiar el nombre de archivo si se desea
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				system("cls");
				system("clear");				
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero encriptado
					printf ("\tError en la apertura del fichero.\n");
					printf ("\n\nPrograma finalizado, pulse cualquier tecla seguida de intro para salir\n");
					fflush(stdin);
					scanf ("%c");
					return -1;
				}
				printf ("\nEncriptando y guardando en el archivo de salida\n");
				i=0;
				while (fscanf(fichero1, "%c", (txtASCII+i))!=EOF){ //WHILE ARCHIVO+=HASH 
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
				printf ("	Fichero escrito, cerrando");
				fclose (fichero1);
				fclose (fichero2);
				free (txtASCII);
				fflush(stdin);
				printf("\n\nDesea continuar? [Pulse 'N' para salir]\n	");
				scanf("%c", &respuesta);
				if(respuesta=='N'){
					continuar=1;
				}
				system("cls");
				system("clear");
				
			break;
			case 2:
				printf("\n\nExcelente, vamos a ver de que trata ese mensaje...\n");
				printf("\nIntroduzca la password (recomendamos una password de 12 caracteres para un mejor funcionamiento): \n	");	
				fpswrd (pswrd); //FUNCIÓN (Contraseña).
			        			  
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÓN (Pasamos ASCII a unidades,decenas y centenas)
				i++;
			    }
				
				ASCII_a_01(X,Y,Z);//FUNCIÓN (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //Iteración para hash
			    	i=0;
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
				    i++;
					}
			
					
					Func_Desplz(X,Y,Z,T);//(Valores de X en Y, Y en Z, Z en T y T en X)
			
				i=0;
				iter++;
				}
				system("cls");
				system("clear");
				printf ("\nIntroduce la ruta de acceso del archivo .txt que deseas desencriptar.\
				\n[Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.]\n \n	");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
				system("cls");
				system("clear");	
				printf ("\nAbriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a desencriptar
					printf ("\tError en la apertura del fichero.\n");
					printf ("\n\nPrograma finalizado, pulse cualquier tecla seguida de intro para salir\n");
					fflush(stdin);
					scanf ("%c");
					return -1;
				}
				printf ("	Fichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nº caracteres
				contador++;
				}
				printf ("		El fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//Asignación dinámica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				printf ("\nIntroduce la ruta de acceso del fichero de salida.\
						\n	ADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n\n	");
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				system("cls");
				system("clear");
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero desencriptado
					printf ("\tError en la apertura del fichero.\n");
					printf ("\n\nPrograma finalizado, pulse cualquier tecla seguida de intro para salir\n");
					fflush(stdin);
					scanf ("%c");
					return -1;
				}
				printf ("\nDesencriptando y guardando en el archivo de salida\n");
				i=0;
				while (fscanf(fichero1, "%c", (txtASCII+i))!=EOF){ //WHILE ARCHIVO+=HASH 
					//Añadir el hash y
					//Operaciones para que no exceda los valores permitidos
					//c1 = c+1; //Con las debidas operaciones, esto es temporal
					if (j==12)
					j=0; //Vuelve a recorrer el hash cuando llega a su fin (12 posiciones)
					*(txtASCII+i) -= pswrdASCII[j];
					while (*(txtASCII+i)<0)
					*(txtASCII+i)+=255;
					fprintf (fichero2, "%c", *(txtASCII+i));
					j++;
					i++;
				}
				printf ("	Fichero escrito, cerrando");
				fclose (fichero1);
				fclose (fichero2);
				free (txtASCII);
				fflush(stdin);
				printf("\n\nDesea continuar? [Pulse 'N' para salir]\n	");
				scanf("%c", &respuesta);
				if(respuesta=='N'){
					continuar=1;
				}
				system("cls");
				system("clear");
				break;
			
			case 3:
				printf("\nMuy bien, hasta la proxima\n");
				continuar =1;
				break;
				
		    default:
		    	printf("\nParece que el viaje de regreso desde Vormir no le ha sentado muy bien...");
		    	fflush(stdin);
				printf("\n 		Desea continuar? [Pulse 'N'para salir]\n	");
				scanf("%c", &respuesta);
				if(respuesta=='N'){
					continuar=1;
				}
		}
	}
}

