#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "Usuarios.h"
#include "Serial.h"
#include "Graficos.h"
#define MAX_ENVIO 90 //El valor máximo que acepta Arduino está especificado en el programa de Arduino
					//dicho máximo es ligeramente superior al utilizado aquí
int main (){
	inicio_normal();
	char olvidalo; //Para funciones en la que se necesita leer un dato pero que no vamos a utilizar
	int x, j1, bloque_no=0;
	Serial puertoserie;
	FILE *fichero;
	FILE *fichero1;
	FILE *fichero2;
	char *txtASCII;
	char y, *mensaje_salida;
	char respuesta=0;
	_Bool continuar = 0;
	while (continuar==0){//El programa se ejecuta indefinidamente hasta que el usuario decide salir
	char c;
	char pswrd[12]; //Array de 13 caracteres
	int iter=0, i=0, j=0, x=0, y=0, z=0, contador=0;
	int pswrdASCII[11], X[11], Y[11], Z[11],T[11];
	int U,D,C,comodin2[11], comodin3[11], comodin4[11];
	char in_file[150], out_file[150], send_file[150];
	
	funcion_espera();
	//graf_error("Mensaje de error de prueba");
	system ("cls");
	printf ("\t\t\t\t----------VITAMINA C----------\n");
	printf ("\t\t\t\t______________________________\n\n\n");
	printf ("\t\t\t     version completa - solo para Windows\n\n\n");
	printf ("\n OPCIONES:\n1.Encriptar un archivo.\n2.Desencriptar un archivo.\
	\n3.Enviar un archivo por radio - Se requiere Arduino y haber realizado primero la conexion (ver opcion 4)\
	\n4.Establecer conexion con Arduino - Se requiere Arduino\n5.Salir\n\n");
	fflush(stdin); //Limpia el buffer de entrada
	scanf("%i",&x);
	switch (x){
			case 1:
				system ("cls");
				printf ("\t\t\t\t----------VITAMINA C----------\n");
				printf ("\t\t\t\t______________________________\n\n\n");
				printf ("Introduce la clave de encriptado:\n\t\t");
				fpswrd (pswrd); //FUNCIÓN (Contraseña).
				
				//Simula "tapar" la contraseña con asteriscos
        		system ("cls");
				printf ("\t\t\t\t----------VITAMINA C----------\n");
				printf ("\t\t\t\t______________________________\n\n\n");
				printf ("Introduce la clave de encriptado:\n\t\t");
				printf ("***********"); 
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÓN (Pasamos ASCII a unidades,decenas y centenas)
					i++;
    			}
				
				ASCII_a_01(X,Y,Z);//FUNCIÓN (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //Iteración para hash
    				i=0;
	    			while(i<12){ //vamos a crear un ultimo array que obtenga su valor dependiendo de comparar X,Y y Z; teniendo en cuenta permutaciones positivas y negativas
	    				if(i%2==0){
	    					if(X[i]==Z[i])
	    						T[i]=1;
							else
								T[i]=0;
	    				}
						else{
	    					if(Y[i]==Z[i])
	    						T[i]=1;
								else
								T[i]=0;
						}
	    				i++;
					}
			
					Func_Desplz(X,Y,Z,T);//(Valores de X en Y, Y en Z, Z en T y T en X)
					i=0;
					iter++;
				}
				
				
				//Aquí se comienza a trabajar con el archivo realmente. Hasta ahora era el manejo de la contraseña y la creación del hash
				
				printf("Excelente,comencemos con la encriptacion\n");
				printf ("\nIntroduce la ruta de acceso del archivo .txt que deseas encriptar.\
				\n[Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.]\n \n	");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
				printf ("\n Abriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a encriptar
					printf ("\tError en la apertura del fichero.\n");
					return -1;
				}
				printf ("\tFichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nº caracteres
				contador++;
				}
				printf ("\t\tEl fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//Asignación dinámica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				printf ("Crear/abrir el fichero de salida:\
						\nIntroduce la ruta de acceso.\
						\nADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n");
				//En el futuro puede añadirse una función que intente abrir el archivo especificado
				//y que si existe lo advierta y de opción a cambiar el nombre de archivo si se desea
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero encriptado
					printf ("Error en la apertura/creacion del fichero de salida.\n");
				}
				printf ("Encriptando y guardando en el archivo de salida\n");
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
				printf ("\t\tFichero escrito, cerrando");
	
				fclose (fichero1);
				fclose (fichero2);
				free (txtASCII);
				fflush(stdin);
				printf("\n 		Desea continuar? No [N]\tSi [cualquier tecla + intro]\n");
				scanf("%c", &respuesta);
				if(respuesta=='N'){
					continuar=1;
				}
				else{
					continuar = 0;
				}
			break;
			
			case 2:
				system ("cls");
				printf ("\t\t\t\t----------VITAMINA C----------\n");
				printf ("\t\t\t\t______________________________\n\n\n");
				printf ("Introduce la clave de encriptado:\n\t\t");
				fpswrd (pswrd); //FUNCIÓN (Contraseña).
				
				//Simula "tapar" la contraseña con asteriscos
        		system ("cls");
				printf ("\t\t\t\t----------VITAMINA C----------\n");
				printf ("\t\t\t\t______________________________\n\n\n");
				printf ("Introduce la clave de encriptado:\n\t\t");
				printf ("***********"); 
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÓN (Pasar la contraseña de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÓN (Pasamos ASCII a unidades,decenas y centenas)
					i++;
    			}
				
				ASCII_a_01(X,Y,Z);//FUNCIÓN (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //Iteración para hash
    				i=0;
	    			while(i<12){ //vamos a crear un ultimo array que obtenga su valor dependiendo de comparar X,Y y Z; teniendo en cuenta permutaciones positivas y negativas
	    				if(i%2==0){
	    					if(X[i]==Z[i])
	    						T[i]=1;
							else
								T[i]=0;
	    				}
						else{
	    					if(Y[i]==Z[i])
	    						T[i]=1;
								else
								T[i]=0;
						}
	    				i++;
					}
			
					Func_Desplz(X,Y,Z,T);//(Valores de X en Y, Y en Z, Z en T y T en X)
					i=0;
					iter++;
				}
				
				//Aquí se comienza a desencriptar el archivo. Hasta ahora era el manejo de la contraseña y la creación del hash
				printf("Excelente,vamos a ver de que trata ese mensaje...\n");
				printf ("\nIntroduce la ruta de acceso al archivo .txt que deseas desencriptar.\
				\n Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.\n");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
	
				printf ("\n Abriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a desencriptar
					printf ("Error en la apertura del fichero.\n");
					return -1;
				}
				printf ("Fichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nº caracteres
					contador++;
				}
				printf ("El fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//Asignación dinámica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				printf ("Crear/abrir el fichero de salida:\
						\nIntroduce la ruta de acceso.\
						\nADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n");
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero desencriptado
					printf ("Error en la apertura/creacion del fichero de salida.\n");
				}
				printf ("Desencriptando y guardando en el archivo de salida\n");
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
				printf ("Fichero escrito, cerrando");
	
				fclose (fichero1);
				fclose (fichero2);
				free (txtASCII);
			break;

			case 3:
				printf ("Vamos a proceder con el envio del mensaje.\nNecesitaremos una ruta de acceso al archivo o su nombre si el archivo esta en la carpeta del programa:\n\t");
				fflush(stdin); //Borra el buffer de entrada
				scanf("%[^\n]s", send_file);
				printf ("\nAccediendo a %s...\n\n", send_file);
				fichero = fopen (send_file, "r"); //Abro el fichero en modo de lectura
				if (fichero==NULL){
					printf ("Ohh! Se ha producido un error en la apertura del fichero. Reinicia el programa y asegurate de introducir bien la ruta de acceso\
					\n\n\n\n-------------------------------------------------\
					\nPulsa cualquier tecla + intro para salir");
					fflush (stdin);
					scanf ("%c", &olvidalo); //Para cuando solo se ejecuta un archivo .exe que no se cierre la consola sin informar al usuario
					return -1;
				}
				else{
					printf ("Fichero abierto correctamente\n\n");
				}
				
				//Una vez el fichero ha sido abierto, hay que leerlo y dividirlo en bloques que se deben ir enviando poco a poco
				//(el tiempo de espera entre el envio de bloques consecutivos esta incluido en la libreria serial)
				//Durante la espera se mostrará al usuario una barra de progreso. (en realidad representa el tiempo de espera y no el de envio, el envío es instantáneo)
				
				//Hago una asignación de memoria para hacer hueco al puntero que va a ir almacenando todos los caracteres de cada bloque
				mensaje_salida = malloc(sizeof(char)*MAX_ENVIO+5); //Hago hueco de sobra
				unsigned int cont=0;
				while (fscanf(fichero, "%c", (mensaje_salida+cont))!=EOF){
					//printf ("%c", *(mensaje_salida+cont));
					cont++;
					if (cont==(MAX_ENVIO-3)){
						cont=0;
						bloque_no++;
						printf ("Enviando el bloque no. %i", bloque_no);
						*(mensaje_salida+(MAX_ENVIO-2))='#';
						*(mensaje_salida+(MAX_ENVIO-1))='·';
						if (!Serial_write(&puertoserie, mensaje_salida)){
							printf ("Se ha producido un error con el envio");
						}
						else{
							printf ("El envio se ha realizado correctamente");
						}
					}
				}
				//Ahora tengo que enviar el bloque que ha quedado al final siguiendo el mismo procedimiento que en el bucle
				*(mensaje_salida+(MAX_ENVIO-2))='#';
				*(mensaje_salida+(MAX_ENVIO-1))='·';
				printf ("Enviando el ultimo bloque del mensaje");
				if (!Serial_write(&puertoserie, mensaje_salida)){
							printf ("Se ha producido un error con el envio");
						}
						else{
							printf ("El envio se ha realizado correctamente");
						}
				printf ("\nLectura finalizada\n");
			break;
			
			case 4:
				//Toda esta parte originalmente se encontraba en la librería Serial.h
				//pero debido a los problemas pasando el puntero de unas funciones a otras desde el programa
				//principal y desde algunas de las funciones de la librería a otras, se incluye aquí toda esta parte:
				printf ("Accediendo al menu de configuracion...\n");
				_Bool hay_conexion = 0; //Para dejar de buscar puertos una vez se establece conexión
				_Bool salir = 0;
				int i;
				char COM_no [5];
				char puertosCOM [MAX_NO_PUERTOS_COM][5]={ //5 por la longitud máxima de los nombres de los puertos
				"COM1", "COM2", "COM3", "COM4", "COM5",
				"COM6", "COM7", "COM8", "COM9"}; //Lista de nombres de puertos para ir probando
    			while (salir==0){ //Hasta que no se selecciona salir o no se establece la conexión no sale del bucle
    				printf ("\n\n\n");
    				for (i=0;i<70;i++)
    					printf ("%c", 219); //Línea gruesa de separación
    				printf ("\n\nCONEXION DEL PUERTO SERIE:\n");
					printf ("Si conoces el puerto al que se conecta la placa,\n");
					printf ("introducelo manualmente, ej: <<COM3>>. Si no lo conoces, puedes\n");
					printf ("introducir un cero para que se busque automaticamente\n");
					printf ("Para cancelar el procesoo, escribe ''salir''\n\n\n");
					fflush(stdin); //Borra el buffer de entrada, para que siempre haya que volver
						//a introducir una nueva opción, ya que la anterior no era válida
					scanf ("%[^\n]s", COM_no);
					if (COM_no[0]=='0'){
						printf ("\nBuscando Arduino automaticamente...");
						//Dependiendo del programa de Arduino que se utilice,
						//podría identificarse uno concreto o el primero que
						//se localice, esto es el que tenga el número de puerto
						//más bajo.
						for (i=0;i<MAX_NO_PUERTOS_COM;i++){
							if (hay_conexion==0){
								printf ("Intentando establecer conexion con el puerto %s\n", puertosCOM[i]);
								if (!Serial_begin(&puertoserie, puertosCOM[i])){
									printf ("Puerto no conectado, comprobando el siguiente...\n\n\n");
								}
								else{
									hay_conexion=1;
									printf ("Conexion establecida.\n");
									printf ("La placa Arduino esta conectada al puerto %s.\n", puertosCOM[i]);
									printf ("No se comprobaran mas puertos. Si la conexion no se ha\n");
									printf ("establecido con tu placa, tendras que desconectar el resto\n");
									printf ("de dispositivos que utilicen puertos serie o teclear manualmente\n");
									printf ("la direccion de la placa.\n\n\n");
									salir=1;
								}
							}
						}
						if (hay_conexion==0){
							printf ("No hay puertos COM disponibles (comprobados del 1 al 9)");
							printf ("Revisa que la placa este conectada. Si esto no funciona, prueba a\
							\nteclear manualmente la direccion.");
						}
					}
					//Comprueba si el nombre del puerto es válido. Comprueba solo 4 carácteres
					else if (COM_no[0]=='C'&&COM_no[1]=='O'&&COM_no[2]=='M'&&(COM_no[3])>='0'&&COM_no[3]<='9'){
						printf ("\nIntentando establecer conexion con el puerto %s.\n", COM_no);
						if (Serial_begin (&puertoserie, COM_no)==0){
							printf ("Error estableciendo conexion!!!\n");
							printf ("Asegurate de que esta bien conocido y de que el puerto es ");
							printf ("el %s.\nPuedes:\nHacer una busqueda automatica\nO vovler al menu\n", COM_no);
							COM_no==NULL;
						}
						else{
							hay_conexion=1;
							salir=1;
						}
					}
					else if (strcmp(COM_no, "sali")){
						salir=1;
						printf ("Proceso cancelado, no se ha establecido ninguna conexion.\nSaliendo...\n");
					}
					else{
						printf ("Ese puerto no existe. Error.\n");
						printf ("El nombre no es correcto.\n");
						printf ("Introduce COM seguido del numero de puerto.");
					}
    			}
				printf ("\n\nFin de la configuracion\n\n");
				break;
			case 5:
				printf("Muy bien, hasta la proxima\n");
				continuar =1;
				break;
				
		    default:
		    	printf("Parece que el viaje de regreso desde Vormir no le ha sentado muy bien ...");
		    	fflush(stdin);
				printf("\n 		Desea continuar? No [N] - Si [Cualquier tecla]\n");
				scanf("%c", &respuesta);
				if(respuesta=='N'){
					continuar=1;
				}
				else{
					continuar=0;
				}
		}
	}
}
