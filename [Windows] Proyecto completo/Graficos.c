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
	printf ("\nUps! Parece que se ha producido un error en el programa :(\n");
	printf ("\n\nERROR: %s\nEl programa no continuara ejecutandose, detenga el programa cerrando esta ventana e inicielo de nuevo.", motivo);
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
