#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "Usuarios.h"
#include "Serial.h"
//#include "Graficos.h"
#define MAX_ENVIO 90 //El valor mÃ¡ximo que acepta Arduino estÃ¡ especificado en el programa de Arduino
					//dicho mÃ¡ximo es ligeramente superior al utilizado aquÃ­
int main (){
	graf_logo();
	inicio_normal();
	char olvidalo; //Para funciones en la que se necesita leer un dato pero que no vamos a utilizar
	int x, j1, bloque_no=0, longitud_mensaje;
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
	graf_logo();
	printf ("\n\n OPCIONES:\n1.Encriptar un archivo.\n2.Desencriptar un archivo.\
	\n3.Enviar un archivo por radio - Se requiere Arduino y haber realizado primero la conexion (ver opcion 4)\
	\n4.Establecer conexion con Arduino - Se requiere Arduino\n5.Salir\n\n");
	fflush(stdin); //Limpia el buffer de entrada
	scanf("%i",&x);
	switch (x){
			case 1:
				graf_logo();
				printf ("Introduce la clave de encriptado:\n\t\t");
				fpswrd (pswrd); //FUNCIÃ“N (ContraseÃ±a).
				
				//Simula "tapar" la contraseÃ±a con asteriscos
        		graf_logo();
				printf ("Introduce la clave de encriptado:\n\t\t");
				printf ("***********"); 
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÃ“N (Pasar la contraseÃ±a de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÃ“N (Pasamos ASCII a unidades,decenas y centenas)
					i++;
    			}
				
				ASCII_a_01(X,Y,Z);//FUNCIÃ“N (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //IteraciÃ³n para hash
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
				
				
				//AquÃ­ se comienza a trabajar con el archivo realmente. Hasta ahora era el manejo de la contraseÃ±a y la creaciÃ³n del hash
				
				printf("Excelente,comencemos con la encriptacion\n");
				printf ("\nIntroduce la ruta de acceso del archivo .txt que deseas encriptar.\
				\n[Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.]\n \n	");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
				printf ("\n Abriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a encriptar
					printf ("\tError en la apertura del fichero.\n");
					graf_error("Se ha producido un error con la lectura del fichero.\nReinicia el programa.");
					return -1;
				}
				printf ("\tFichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nÂº caracteres
				contador++;
				}
				printf ("\t\tEl fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//AsignaciÃ³n dinÃ¡mica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				if(txtASCII==NULL)
				{
					graf_error("Error en la asignacion de memoria");
					exit(-1);
				}
				printf ("Crear/abrir el fichero de salida:\
						\nIntroduce la ruta de acceso.\
						\nADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n");
				//En el futuro puede aÃ±adirse una funciÃ³n que intente abrir el archivo especificado
				//y que si existe lo advierta y de opciÃ³n a cambiar el nombre de archivo si se desea
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero encriptado
				    graf_error("Error en la apertura del archivo");
					return -1;
				}
				printf ("Encriptando y guardando en el archivo de salida\n");
				i=0;
				while (fscanf(fichero1, "%c", (txtASCII+i))!=EOF){ //WHILE ARCHIVO+=HASH 
					//AÃ±adir el hash y
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
				graf_logo();
				printf ("Introduce la clave de encriptado:\n\t\t");
				fpswrd (pswrd); //FUNCIÃ“N (ContraseÃ±a).
				
				//Simula "tapar" la contraseÃ±a con asteriscos
        		graf_logo();
				printf ("Introduce la clave de encriptado:\n\t\t");
				printf ("***********"); 
				while (i<12){ //ASCII Y UDC
					Char_a_ASCII(pswrd,pswrdASCII); //FUNCIÃ“N (Pasar la contraseÃ±a de caracteres a ASCII)   
					UDC (pswrdASCII, X, Y, Z); //FUNCIÃ“N (Pasamos ASCII a unidades,decenas y centenas)
					i++;
    			}
				
				ASCII_a_01(X,Y,Z);//FUNCIÃ“N (X Y Z a binario)
				printf("\n");
			
				while(iter<6){ //IteraciÃ³n para hash
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
				
				//AquÃ­ se comienza a desencriptar el archivo. Hasta ahora era el manejo de la contraseÃ±a y la creaciÃ³n del hash
				printf("Excelente,vamos a ver de que trata ese mensaje...\n");
				printf ("\nIntroduce la ruta de acceso al archivo .txt que deseas desencriptar.\
				\n Si el archivo se encuentra en la misma carpeta que este programa solo tendras que poner el nombre del archivo.\n");
				fflush (stdin); //Limpio el buffer de entrada
				scanf ("%[^\n]s", in_file);
	
				printf ("\n Abriendo el fichero de lectura %s\n", in_file);
				fichero1 = fopen (in_file, "r");
				if (fichero1==NULL){ //If error apertura de archivo a desencriptar
					graf_error("Error en la apertura del fichero");
					return -1;
				}
				printf ("Fichero abierto correctamente.\n");
				while (fscanf(fichero1, "%c", &c)!=EOF){ //while contador nÂº caracteres
					contador++;
				}
				printf ("El fichero tiene %i caracteres.\n", contador);
				rewind (fichero1);
				//AsignaciÃ³n dinÃ¡mica de memoria para crear un vector de la misma longitud que el fichero
				txtASCII = malloc (sizeof(char)*contador);
				if(txtASCII==NULL)
				{
					graf_error("Error en la asignacion de memoria");
					exit(-1);
				}
				printf ("Crear/abrir el fichero de salida:\
						\nIntroduce la ruta de acceso.\
						\nADVERTENCIA: si eliges un archivo que ya existe se sobreescribira y se perderan los datos guardados en el.\n");
				fflush(stdin);
				scanf ("%[^\n]s", out_file);
				fichero2 = fopen (out_file, "w");
				if (fichero2 == NULL){ //If error creacion de fichero desencriptado
					graf_error("Error en la apertura del fichero de destino");
					return -1;
				}
				printf ("Desencriptando y guardando en el archivo de salida\n");
				i=0;
				while (fscanf(fichero1, "%c", (txtASCII+i))!=EOF){ //WHILE ARCHIVO+=HASH 
					//AÃ±adir el hash y
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
					graf_error ("Ohh! Se ha producido un error en la apertura del fichero. Reinicia el programa y asegurate de introducir bien la ruta de acceso\
					\n\n\n\n-------------------------------------------------");
					return -1;
				}
				else{
					printf ("Fichero abierto correctamente\n\n");
				}
				
				//Compruebo la longitud del mensaje, con el fin de informar al usuario del tiempo que puede tardar o del nÃºmero de bloques que deben enviarse
				longitud_mensaje=0;
				while (fscanf(fichero, "%c", &olvidalo)!=EOF)
					longitud_mensaje++;
				printf ("El mensaje tiene %i caracteres.\nVamos a dividirlo en %i bloques para enviarlo.\n", longitud_mensaje, (longitud_mensaje/90)+1);
				//Una vez el fichero ha sido abierto, hay que leerlo y dividirlo en bloques que se deben ir enviando poco a poco
				//(el tiempo de espera entre el envio de bloques consecutivos esta incluido en la libreria serial)
				//Durante la espera se mostrarÃ¡ al usuario una barra de progreso. (en realidad representa el tiempo de espera y no el de envio, el envÃ­o es instantÃ¡neo)
				
				//Hago una asignaciÃ³n de memoria para hacer hueco al puntero que va a ir almacenando todos los caracteres de cada bloque
				mensaje_salida = malloc(sizeof(char)*MAX_ENVIO+2);//Dejo dos huecos extra para los signos del final de cada bloque
				if(mensaje_salida==NULL)
				{
					graf_error("Error en la asignacion de memoria");
					exit(-1);
				} 
				unsigned int cont=0;
				rewind(fichero);
				while (fscanf(fichero, "%c", (mensaje_salida+cont))!=EOF){
					//printf ("%c", *(mensaje_salida+cont));
					cont++;
					if (cont==(MAX_ENVIO-3)){
						cont=0;
						bloque_no++;
						printf ("Enviando el bloque no. %i de %i bloque(s)", bloque_no, (longitud_mensaje/90)+1);
						*(mensaje_salida+(MAX_ENVIO-2))='#';
						*(mensaje_salida+(MAX_ENVIO-1))='·';
						if (!Serial_write(&puertoserie, mensaje_salida)){
							graf_error ("Se ha producido un error con el envio");
						}
						else{
							printf ("El envio se ha realizado correctamente");
						}
					}
				}
				//Ahora tengo que enviar el bloque que ha quedado al final siguiendo el mismo procedimiento que en el bucle
				*(mensaje_salida+(MAX_ENVIO-2))='#';
				*(mensaje_salida+(MAX_ENVIO-1))='·';
				for (cont=cont;cont<MAX_ENVIO;cont++) //Borra el bloque
					*(mensaje_salida+cont)=NULL;
				printf ("Enviando el ultimo bloque del mensaje");
				if (!Serial_write(&puertoserie, mensaje_salida)){
							printf ("Se ha producido un error con el envio");
						}
						else{
							printf ("El envio se ha realizado correctamente");
						}
				printf ("\nLectura finalizada\n");
				fclose(fichero);
				free(mensaje_salida);
			break;
			
			case 4:
				//Toda esta parte originalmente se encontraba en la librerÃ­a Serial.h
				//pero debido a los problemas pasando el puntero de unas funciones a otras desde el programa
				//principal y desde algunas de las funciones de la librerÃ­a a otras, se incluye aquÃ­ toda esta parte:
				printf ("Accediendo al menu de configuracion...\n");
				_Bool hay_conexion = 0; //Para dejar de buscar puertos una vez se establece conexiÃ³n
				_Bool salir = 0;
				int i;
				char COM_no [5];
				char puertosCOM [MAX_NO_PUERTOS_COM][5]={ //5 por la longitud mÃ¡xima de los nombres de los puertos
				"COM1", "COM2", "COM3", "COM4", "COM5",
				"COM6", "COM7", "COM8", "COM9"}; //Lista de nombres de puertos para ir probando
    			while (salir==0){ //Hasta que no se selecciona salir o no se establece la conexiÃ³n no sale del bucle
    				printf ("\n\n\n");
    				for (i=0;i<70;i++)
    					printf ("%c", 219); //LÃ­nea gruesa de separaciÃ³n
    				printf ("\n\nCONEXION DEL PUERTO SERIE:\n");
					printf ("Si conoces el puerto al que se conecta la placa,\n");
					printf ("introducelo manualmente, ej: <<COM3>>. Si no lo conoces, puedes\n");
					printf ("introducir un cero para que se busque automaticamente\n");
					printf ("Para cancelar el procesoo, escribe ''salir''\n\n\n");
					fflush(stdin); //Borra el buffer de entrada, para que siempre haya que volver
						//a introducir una nueva opciÃ³n, ya que la anterior no era vÃ¡lida
					scanf ("%[^\n]s", COM_no);
					if (COM_no[0]=='0'){
						printf ("\nBuscando Arduino automaticamente...");
						//Dependiendo del programa de Arduino que se utilice,
						//podrÃ­a identificarse uno concreto o el primero que
						//se localice, esto es el que tenga el nÃºmero de puerto
						//mÃ¡s bajo.
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
					//Comprueba si el nombre del puerto es vÃ¡lido. Comprueba solo 4 carÃ¡cteres
					else if (COM_no[0]=='C'&&COM_no[1]=='O'&&COM_no[2]=='M'&&(COM_no[3])>='0'&&COM_no[3]<='9'){
						printf ("\nIntentando establecer conexion con el puerto %s.\n", COM_no);
						if (Serial_begin (&puertoserie, COM_no)==0){
							printf ("Error estableciendo conexion!!!\n");
							printf ("Asegurate de que esta bien conectado y de que el puerto es ");
							printf ("el %s.\nPuedes:\nHacer una busqueda automatica, escribir otro puerto o vovler al menu\n", COM_no);
							COM_no==NULL; //Olvida el puerto que habÃ­a introducido el usuario (que era incorrecto)
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
				funcion_espera();
				continuar =1;
				break;
				
		    default:
		    	printf("Revisa tu seleccion...");
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
