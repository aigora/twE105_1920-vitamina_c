#include <stdio.h>
void main ()
{
	Datos Uyc;
	pedirDatos(Uyc);
	int x;
	//El programa se ejecuta indefinidamente hasta que el usuario decide salir
	_Bool continuar = 0;
	while (continuar==0){
		printf("Bienvenido me llamo Jarvis , que desea hacer?\n");//Le doy la bienvenida y le pregunto que desea hacer
		printf("1.Encriptar\n");
		printf("2.Desencriptar\n");
		printf("3.Enviar\n");
		printf("4.Recibir\n");
		printf("5.Salir\n");//Le presento las opciones a seleccionar
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
				printf("Muy bien ...,hasta la proxima\n");
				continuar =1;
				break;
		    default:
		    	printf("Parece que el viaje de regreso desde Vormir no le ha sentado muy bien ...");
		}
	}
}
