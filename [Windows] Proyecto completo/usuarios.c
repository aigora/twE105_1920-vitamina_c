/*Programa con funciones para pedir una constraseña
 * comparar los datos introducidos con los ya existentes
 * crear nuevos usuarios
 * guardar los datos de los usuarios existentes en un fichero
 * (idea de futuro: encriptar el archivo de los nombres de usuario y contraseña utilizando el propio encriptador y con una contraseña fija que solo conoce el programa).
 */
#include "usuarios.h"
#include <stdio.h>
#include "Graficos.h"
int inicio_normal (char password[]){ //Prueba. Todo lo que aquí aparece deberá aparecer en el programa principal. (El resto son funciones que se incluirán en la librería).
	FILE *users_file;
	int i;
	int ultimo_registro, intentos = 0;
	users_file = fopen ("usuarios.txt", "r"); //Abro en formato de lectura porque lo primero es
	usuarios lista [MAX_USERS]={0}; //Crea el vector en el que almacenar los datos y borra todo lo que haya.
	ultimo_registro = consulta_numero_registros(users_file, lista)+1;
	while (iniciar_sesion (users_file, lista, ultimo_registro)!=1){ //Intenta iniciar sesión hasta que lo hace correctamente
		espera (intentos); //Espera cada vez más tiempo entre intentos para iniciar sesion
		intentos++;
	}
	fclose (users_file);
	printf ("Sesion iniciada correctamente, accediendo al programa...\n\n\n");
	printf ("\n\n");
	return 0;
}

int consulta_numero_registros (FILE *fichero, usuarios vector[]){
	_Bool j = 0; //Booleana porque solo hay dos registros (0 usuario, 1 clave de acceso)
	int i = 0, k = 0; //i controla el número de registro, la j controla si es usuario o contraseña lo que se está leyendo, la k controla la posicion dentro de cada cadena de texto
	_Bool salida =0;
	char x;
	while(fscanf (fichero, "%c", &x)!=EOF&&salida==0){
		//printf ("%c", x);
		if (x == ';'){ //Si llega al fin del "campo", reincia el contador de la posicion dentro de la cadena de texto y pasa al siguiente "campo"
			j=1;
			k=0;
		}
		else if (x == '\n'){ //Si llega al salto de línea, es decir, el final del registro...
			j=0; //Vuelve al primer "campo"
			k=0; //Vuelve al comienzo de la cadena de caracteres<
			i++; //Pasa al siguiente registro
		}
		else {
			//Finalizada la parte de comprobación de los carácteres "especiales" que separan datos, etc ahora guardo los datos debidamente
			if (j==0){ //Parte del usuario
				vector[i].user[k] = x;
				k++;
			}
			else{ //Parte de la contraseña
				vector[i].password[k] = x;
				k++;
			}
		}
		if (i==(MAX_USERS-1)){ //Si llega al máximo de usuarios permitidos, sale del bucle de lectura (lo tiene que detectar una vez antes de que se supere el límite, de ahí el -1).
			salida = 1;
		}
	}
	rewind (fichero); //Vuelve al comienzo del fichero por si acaso se quiere volver a leer en otro momento desde esta librería sin que se vuelve a abrir el fichero.
	return i; //Devuelve el número de registros que ha leído (más uno), el número se refiere a posición del último registro dentro de un vector.
}

void nuevo (FILE *fichero, usuarios *new_user, int ultimo_registro, usuarios lista[]){
	int i;
	fclose (fichero);
	_Bool salida = 0;
	char clave2 [TAM_PASSWORD] = {0};
	while (salida==0){
		fflush(stdin);
		printf ("Introduce el nombre de usuario:\n");
		scanf ("%[^\n]s", new_user->user);
		fflush (stdin);
		printf ("Introduzca clave de acceso. (Esta clave no se utiliza para encriptar/desencriptar): \n");
		scanf ("%[^\n]s", new_user->password);
		fflush (stdin);
		printf ("Confirme la clave de acceso: \n");
		scanf ("%[^\n]s", &clave2);
		if (comparar_cadenas(new_user->password, clave2, TAM_PASSWORD)==1){
			salida = 1;
			printf ("Se ha creado el nuevo usuario.\n");
		}
		else {
			printf ("Error en la clave de acceso. No coinciden.\n");
		}
	}
	
	//Reescribe todo el fichero y a�ade los nuevos datos
	fclose (fichero);
	fichero = fopen ("usuarios.txt", "w");
	rewind (fichero); //Se posiciona al comienzo del fichero (por si no lo estaba).
	for (i=0;i<ultimo_registro-1;i++){
		fprintf (fichero, "%s;%s\n", lista[i].user, lista[i].password);
	}
	fprintf (fichero, "%s;%s\n", new_user->user, new_user->password);
	fclose (fichero);
	fichero = fopen ("usuarios.txt", "r");
}


_Bool comparar_cadenas (char *cadena1, char *cadena2, int l1){
	int i;
	_Bool son_iguales = 1; //(Es cierto que son iguales hasta que se encuentre una letra que lo desmienta).
	for (i=0;i<l1;i++){
		if (*(cadena1+i)!=*(cadena2+i))
			son_iguales = 0;
	}
	return son_iguales;
}


_Bool iniciar_sesion (FILE *fichero, usuarios usuarios_existentes[], int ultimo_registro){
	int opcion, i;
	usuarios temp = {0};
	_Bool salida = 0;
	printf("\n\n\n\n\n\n\t\tINICIO DE SESION\n\n\tSeleccione una opcion:\n");
	printf ("\t1. - Iniciar sesion como un usuario ya registrado.\n\t2. - Crear un nuevo usuario. (Limite de usuarios 100).\n");
	scanf ("%i", &opcion);
	if (opcion==2){
		nuevo(fichero, &usuarios_existentes[ultimo_registro], ultimo_registro, usuarios_existentes);
		return 1; //No se pide introducir usuario y contraseña si se acaba de crear el usuario
	}
	else{ //Si no se ha elegido la opcion de crear un nuevo usuario entra automáticamente en esta, es la forma de evitar
		//tiempos de espera como si se hubiese cometido un error al introducir usuario y contraseña
		printf ("Usuario: ");
		fflush (stdin);
		scanf ("%[^\n]s", &temp.user);
		printf ("Clave de acceso (no es la que se utiliza para la encriptacion): ");
		fflush (stdin);
		scanf ("%[^\n]s", &temp.password);
		for (i=0;i<ultimo_registro;i++){
			if(comparar_cadenas (usuarios_existentes[i].user, temp.user, TAM_USER)){
				if (comparar_cadenas(usuarios_existentes[i].password, temp.password, TAM_PASSWORD)){
					salida = 1;
				}
			}
		}
		return salida;
	}
}


void espera (int intentos){
	int i = 0;
	printf ("Espere para poder volver a intentarlo.\n");
	for (i=0;i<intentos*intentos;i++){ //El tiempo de espera es exponencial
		funcion_espera();
	}
	system("cls");
}




/*NOTAS______________________________
 * El fichero en el que se guardan los nombres de usuario y las contraseñas tiene la siguiente forma:
 * nombre de usuario de ejemplo; contraseña de ejemplo 1
 * nombre del usuario ejemplo 2; contraseña de ejemplo 2
 * ...
 * (El usuario se separa de la contraseña por punto y coma y los registros se separan por saltos de línea.
 */
