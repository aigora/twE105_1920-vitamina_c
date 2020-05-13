#include <stdio.h>
#include "Usuarios.h"
void config ();
void main ()
{
	inicio_normal();
	int x;
	//El programa se ejecuta indefinidamente hasta que el usuario decide salir
	_Bool continuar = 0;
	while (continuar==0){
		printf("Bienvenido me llamo Jarvis , que desea hacer?\n");//Le doy la bienvenida y le pregunto que desea hacer
		printf ("OPCIONES:\n1.Encriptar un archivo.\n2.Desencriptar un archivo.\n3.Enviar un archivo por radio (se necesita Arduino y configurar puerto serie).\
		\n4.Recibir un archivo (se necesita Arduino y configurar el puerto serie).\n5.Opciones de configuracion. *Se necesita para utilizar Arduino.\
		\n6.Salir.\n\n");
		scanf("%i",&x);
		switch (x)
		{
			case 1:
				printf("Excelente,comencemos con la encriptacion\n");
				break;
			case 2:
				printf("Excelente,vamos a ver de que trata ese mensaje...\n");
				break;
			case 3:
				printf("Excelente,que le quiere transmitir al Sr.Stark?\n");
				break;
			case 4:
				printf("Excelente,veamos que tiene para usted el Sr.Stark\n");
				break;
			case 5:
				printf("Abriendo el menu de configuracion...\n");
				config();
			case 6:
				printf("Muy bien ...,hasta la proxima\n");
				continuar =1;
				break;
		    default:
		    	printf("Parece que el viaje de regreso desde Vormir no le ha sentado muy bien ...");
		}
	}
}

void config (){
	int x;
	while (x!=1){
		printf ("OPCIONES DE CONFIGURACION:\n1. - Salir\n2. - Seleccionar el puerto serie.\n3. - Cambiar el puerto serie (cierra las\
		\nconexiones existentes).\n"); //Tal vez se añadan más funciones más adelante.
		scanf ("%i", &x);
		switch (x){
			case 2:
				printf ("Iniciando la creacion de conexion con la placa Arduino via puerto serie. Conecta la placa y selecciona\
				\nla opcion que desees. (Si tienes dudas, selecciona la opcion de busqueda automatica)\n");
				//Serial_search(); //Función que se creará a partir del bucle main del archivo Serial.c, una vez modificado todo para funcionar como librería de funciones.
				break;
				
			case 3:
				printf ("Cerrando las conexiones existentes y creando una nueva.");
				//Serial_end(puerto_serie); //Comprobar que el argumento de la función es correcto (dependerá de la forma crear la librería y de dónde se declare la variable Serial).
				printf ("Iniciando la creacion de conexion con la placa Arduino via puerto serie. Conecta la placa y selecciona\
				\nla opcion que desees. (Si tienes dudas, selecciona la opcion de busqueda automatica)\n");
				//Serial_search(); //Función que se creará a partir del bucle main del archivo Serial.c, una vez modificado todo para funcionar como librería de funciones.
				break;
			
			case1:
				printf ("Cerrando configuracion...\n\n");
				break;
			
			default:
				printf ("Opcion no valida.\nRevisa tu seleccion.\n");
				break;		
		}
	}
}
