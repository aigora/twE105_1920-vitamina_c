//Funciones que podremos utilizar para la representación de pequeños gráficos, como barras de progreso y otros que puede que utilicemos
//Nota: a lo mejor alguna de las funciones se descarta más adelante

/*Nota símbolos ASCII:
	Este programa utiliza los siguientes caracteres:
	37 --> % (Se utiliza como número porque da problemas al utilizarlo directamente)
	08 --> Retroceso (No imprimible - Caracteres de control)
	219 --> (Símbolo de un rectángulo, forma parte del ASCII extendido)
	250 --> · (Forma parte del ASCII extendido, no se reconoce directamente)
*/
/*
#include <stdio.h>

#define TAM 100000 //Solo para el ejemplo

void progressbar (int progreso[], int iteracion); //Recibe el porcentaje de progreso y la iteración en la que se encuentra el bucle en el que está la función.
void startprogressbar (char[]); //Imprime dos líneas con los porcentajes de la barra de progresoy el título
void endprogressbar (_Bool hecho); //Muestra que la tarea se ha completado
void detenerporerror (char motivo []); //Detiene el programa entrando en un bucle infinito tras mostrar un aviso y el error que se ha producido
int calculaprogreso (int proceso, int totaldeprocesos); //Calcula el progreso reaizado y lo devuelve en tanto por ciento (Opcional)
void progressbar2 (int progreso); //Segundo tipo de barra de progreso. Recibe como argumento el porcentaje de progreso
			*/
#include "Graficos.h"					  
//#include <stdio.h>							  
								  
								  
//TODO EL MAIN ES UNA PRUEBA, UN EJEMPLO
/*
void main (){ //Ejemplo de cómo utilizar las funciones - Prueba de las funciones
	int i, j;
	int porcentaje [TAM];
	porcentaje [0] = 0;
	startprogressbar("Nombre de la barra de progreso");
	for (i=0;i<TAM;i++){
		porcentaje [i] = calcularprogreso(i, TAM);
		progressbar(porcentaje, i);
		for (j=0;j<50000;j++){} //Sirve a modo de delay para probar el código - Ajustar el valor para obtener la velocidad deseada en la prueba
	}
	endprogressbar(1);
	printf ("\nBarra de progreso, segundo tipo:");
	progressbar2 (73);
}
*/

int calcularprogreso (int proceso, int totaldeprocesos){return (proceso*100/totaldeprocesos);}


//Con esta función se puede ir representando el avance de una tarea en un bucle. ¡Esta función solo tiene sentido dentro de un bucle!
//No sirve si se van a mostrar más cosas en la pantalla en ese mismo bucle.
void progressbar (int porcentaje[], int iteracion){
	if (porcentaje[iteracion]>porcentaje[iteracion-1]&&porcentaje[iteracion]<=100){
		if (porcentaje[iteracion]<=10)
			printf ("%c%c%c%i%c", 8, 8, 219, porcentaje[iteracion], 37);
		else
			printf ("%c%c%c%c%i%c",8, 8, 8, 219, porcentaje[iteracion], 37);
	}
	else if (porcentaje[iteracion]>100){
		endprogressbar(0);
		detenerporerror("El porcentaje no debe ser mayor que 100");
	}
	
	
}

//Muestra el nombre de la barra de progreso y la escala con los porcentajes de progreso
void startprogressbar (char titulo[]){
	printf ("\n%s\n", titulo);
	printf ("0%c\t\t\t25%c\t\t\t50%c\t\t\t75%c\t\t\t100%c\n%c0%c", 37, 37, 37, 37, 37, 219, 37);
}

//Muestra un mensaje de completado o de interrupción en función de si el parámetro es 0 ó 1
void endprogressbar (_Bool hecho){
	if (hecho==0)
		printf ("\tINTERRUMPIDO/ERROR\n");
	else
		printf ("%c%c%cCOMPLETADO\n", 8, 8, 8); //8 es el retroceso en la tabla ASCII
}

//Detiene el programa en caso de error y dice la causa que recibe como parámetro
void detenerporerror (char motivo []){
	graf_error ("Se ha producido un error, cierre la ventana y reinicie el programa");
	while (1==1){}
}

//Sirve para cuando no se puede utilizar la otra función porque en ese mismo bucle se imprimen datos en la pantalla
//También es para usarla cuando se quiere mostrar el progreso y no hace falta actualizar cada momento el progreso
void progressbar2 (int progreso){
	int i;
	printf ("\nProgreso de la tarea:\n");
	for (i=0;i<=progreso;i++){
		printf ("%c", 219);
	}
	for (i=i;i<=100;i++){
		printf ("%c", 250); //Muestra el resto de la barra vacía
	}
	printf ("\t %i%c", progreso, 37);
}

void funcion_espera (){
	int i, j, k;
	for (k=0;k<3;k++){
		for (i=0;i<70;i++){
			for (j=0;j<40;j++){
				printf ("%c%c", 220, 8);
			}
			printf (".");
		}
		for (i=0;i<70;i++){
			for (j=0;j<90;j++){
				printf ("%c%c", 220, 8);
			}
			printf ("%c%c", 8, 8);
		}
		for (i=0;i<71;i++){
			for (j=0;j<30;j++){
				printf ("%c%c", 220, 8);
			}
				printf (" ");
		}
		for (i=0;i<71;i++)
			printf("%c", 8);
	}
}

void graf_error (char mensaje_de_error[]){
	const char g_error [] = {
	'\n',
	9,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9, 32, 32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9,'\n',
	9,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9, 32, 32,219,219,'V','i','t','a','m','i','n','a', 32,'C', 32, 95, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32,'E','R','R','O','R', 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,177,177,177,177,177,177,177,177,177,177,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32,'E','R','R','O','R', 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,177,177,177,177,177,177,177,177,177,177,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,220,220,220,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,220,220,220,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32,'E','R','R','O','R', 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,177,177,177,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32,'E','R','R','O','R', 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,219,219,219,219,219,219,219,219,219,219,219,219,219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32, 32,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32,220,219,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,219,220,9,'\n',
    9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32,219,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,219,9,'\n',
	9,9,219,219,219,219,219,219,219,219,219,219,219,219,219,219,9, 32,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,9, '\n'
	};
	system ("cls");
	printf ("Ohh!\nSe ha producido un error :(\n");
	printf ("%s\n", g_error);
	printf ("\n\n%s", mensaje_de_error);
	printf ("Pulsa cualquier tecla seguida de intro para salir");
	scanf ("%i");
}

void graf_logo(){
	const char g_logo [] = {
	219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,178,178,177,177,176,176,176,176,176,123, 65, 98, 76, 87, 76, 43, 43, 56, 78,154,189,230,131,132,133,234,235,237,121,123,122,124, 65, 66, 61,'\n',
	219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,' ','V','I','T','A','M','I','N','A',' ','C',' ',219,219,219,219,219,178,178,178,177,176,176,190,210,230,254, 65, 78, 98, 76,234,235, 45, 85,131,130, 76, 89, 90, 91, 31, 32, 27, 87, 45, 46, 49, 50, 41, 32,131,145,150,'\n',
	219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,178,178,177,177,177,177,176,176,131,130, 76, 89,123, 65, 98, 76, 87, 76, 69, 90, 91, 31, 32, 34, 43, 45, 46,110,100,120,130,140,150,160,170,190,180,200,'\n'
	};
	system("cls");
	printf ("%s", g_logo);
	printf ("\tVersion completa para Windows\n\n");
}
