/* Programa que establece conexi�n con la placa Arduino - 4 de mayo de 2020
 *
 * Esta versi�n todav�a no puede recibir mensajes
 * Se utiliza un main a modo prueba, pero en la versi�n definitiva esa parte del c�digo tendr� que estar incluida en otras funciones
 * Este archivo deber� incluirse en el proyecto en forma de librer�a
 *
 * Hay un error con la condici�n de la l�nea 84. Solo funciona si se a�ade un car�cter a continuaci�n de "salir".
 * 
 * Hay una opci�n para establecer la conexi�n con una b�squeda autom�tica en todos los puertos
 * y otra opci�n para introducir manualmente la direcci�n, ya que si hay dos placas Arduino conectadas
 * la b�squeda autom�tica conectar� con el puerto con el n�mero m�s bajo, que puede no ser el deseado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define MAX_NO_PUERTOS_COM 10
#define TAM_BUFFER 110

typedef struct
{
    HANDLE handler;
    COMSTAT status;
    char *COM_number;
} Serial;

_Bool Serial_begin (Serial *link, char *COM_number);
_Bool Serial_write (Serial *link, char *mensaje);
void Serial_end (Serial *link);

main (){ //Hay que convertirlo en una funci�n, que puede incluirse en esta parte del programa o en otra
	Serial puertoserie;
	_Bool hay_conexion = 0; //Para dejar de buscar puertos una vez se establece conexi�n
	_Bool salir = 0;
	int i;
	char COM_no [5];
	char puertosCOM [MAX_NO_PUERTOS_COM][5]={ //5 por la longitud m�xima de los nombres de los puertos
	"COM1", "COM2", "COM3", "COM4", "COM5",
	"COM6", "COM7", "COM8", "COM9", "COM10"};
	printf ("Intentando establecer conexion\n"); //Lista de nombres de puertos para ir probando
    while (salir==0){ //Hasta que no se selecciona salir o no se establece la conexi�n no sale del bucle
		printf ("Si conoces el puerto al que se conecta la placa,\n");
		printf ("introducelo manualmente, ej: <<COM3>>. Si no lo conoces, puedes\n");
		printf ("introducir un cero para que se busque automaticamente\n");
		printf ("Para cancelar el procesoo, escribe <<salir>>\n\n\n");
		fflush(stdin); //Borra el buffer de entrada, para que siempre haya que volver
			//a introducir una nueva opci�n, ya que la anterior no era v�lida
		scanf ("%[^\n]s", COM_no);
		if (COM_no[0]=='0'){
			printf ("\nBuscando Arduino automaticamente...");
			//Dependiendo del programa de Arduino que se utilice,
			//podr�a identificarse uno concreto o el primero que
			//se localice, esto es el que tenga el n�mero de puerto
			//m�s bajo.
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
		}
		//Comprueba si el nombre del puerto es v�lido. Comprueba solo 4 car�cteres
		else if (COM_no[0]=='C'&&COM_no[1]=='O'&&COM_no[2]=='M'&&(COM_no[3])>='0'&&COM_no[3]<='9'){
			printf ("\nIntentando establecer conexion con el puerto %s.\n", COM_no);
			if (Serial_begin (&puertoserie, COM_no)==0){
				printf ("Error estableciendo conexion!!!\n");
				printf ("Asegurate de que esta bien conocido y de que el puerto es ");
				printf ("el %s.\nOpciones:\n1.Busqueda automatica\n2.Vovler al menu", COM_no);
				COM_no==NULL;
			}
			else{
				hay_conexion=1;
				salir=1;
			}
		}
		else if (strcmp(COM_no, "salir")){
			salir=1;
			printf ("Proceso cancelado, no se ha establecido ninguna conexion.\nSaliendo...\n");
		}
		else{
			printf ("Ese puerto no existe. Error.\n");
			printf ("El nombre no es correcto.\n");
			printf ("Introduce COM seguido del numero de puerto.");
		}
    }
	printf ("\n\n\n\n_________\nProceso terminado.\n<Fin del programa>");
	return 0;
}

_Bool Serial_begin (Serial *link, char *COM_number){
	link->COM_number=COM_number;
	link->handler = CreateFileA ((COM_number),
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
	if (link->handler == INVALID_HANDLE_VALUE){
		printf ("Imposible realizar la conexion.\n");
		printf ("Puede que la placa Arduino no este conectada.\n");
		return 0;
	}
	else{
		printf ("Obteniendo parametros de conexion...\n");
		DCB parametros = {0};
		if (!GetCommState(link->handler, &parametros)){
			printf ("No es posible leer los parametros la conexion.\n");
			printf ("No se puede establecer conexion con el puerto serie.\n");
		}
		else{ //Establece los par�metros de la conexi�n
		//Recuerda que la velocidad en Arduino debe ser la misma, 9600bps
			parametros.BaudRate = CBR_9600;
			parametros.ByteSize = 8;
			parametros.StopBits = ONESTOPBIT;
			parametros.Parity = NOPARITY;
			parametros.fDtrControl = DTR_CONTROL_ENABLE;
			if (!SetCommState(link->handler, &parametros)){
				printf ("Error configurando los parametros de la conexion.\n");
				printf ("Imposible conectar");
				return 0;
			}
			else{
				printf ("Conexion establecida con exito.\n");
				printf ("Listo para la transferencia de informacion.\n");
				printf ("Recuerda que debes indicar al programa  desde el menu principal si quieres\n");
				printf ("recibir o enviar datos.\n\n");
				PurgeComm(link->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				return 1;
			}
		}
	}
}

void Serial_end(Serial *link){ //Finaliza la conexi�n de un puerto abierto. Debe ejecutarse cuando se elija salir del programa.
	CloseHandle (link->handler);
    printf ("Conexion con Arduino finalizada.\n");
}

_Bool Serial_write (Serial *link, char *mensaje){
	if (!WriteFile(link->handler, (void*) mensaje, TAM_BUFFER, 0, 0)){
		printf ("Error enviando el mensaje.\nDebe reiniciarse la transmision del mensaje.\n");
		return 0;
	}
	return 1;
}

//AQU� FUNCIONES PARA EL ENV�O Y RECEPCI�N DE MENSAJES.

//Para escribir este programa, se ha consultado c�mo realizar la conexi�n con la placa Arduino por el puerto
//serie en un proyecto del a�o pasado, consultado en https://github.com/aigora/twA109-Codigo_Morse/blob/master/Morse_C/SerialPort.c

