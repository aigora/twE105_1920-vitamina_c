#include <stdio.h>

void progressbar (int progreso[], int iteracion); //Recibe el porcentaje de progreso y la iteraci�n en la que se encuentra el bucle en el que est� la funci�n.
void startprogressbar (char[]); //Imprime dos l�neas con los porcentajes de la barra de progresoy el t�tulo
void endprogressbar (_Bool hecho); //Muestra que la tarea se ha completado
void detenerporerror (char motivo []); //Detiene el programa entrando en un bucle infinito tras mostrar un aviso y el error que se ha producido
int calculaprogreso (int proceso, int totaldeprocesos); //Calcula el progreso reaizado y lo devuelve en tanto por ciento (Opcional)
void progressbar2 (int progreso); //Segundo tipo de barra de progreso. Recibe como argumento el porcentaje de progreso
