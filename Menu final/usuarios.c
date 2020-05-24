/*Programa con funciones para pedir una constraseña
 * comparar los datos introducidos con los ya existentes
 * crear nuevos usuarios
 * guardar los datos de los usuarios existentes en un fichero
 * (idea de futuro: encriptar el archivo de los nombres de usuario y contraseña utilizando el propio encriptador y con una contraseña fija que solo conoce el programa).
 */
#include "usuarios.h"
int inicio_normal (){ //Prueba. Todo lo que aquí aparece deberá aparecer en el programa principal. (El resto son funciones que se incluirán en la librería).
	FILE *users_file;
	int ultimo_registro, intentos = 0;
	//printf ("Esta parte del programa solo es una prueba y se integrara en el resto del programa en forma de libreria.\n");
	users_file = fopen ("usuarios.txt", "r"); //Abro en formato de lectura porque lo primero es
	usuarios lista [MAX_USERS]={0}; //Crea el vector en el que almacenar los datos y borra todo lo que haya.
	ultimo_registro = consulta_numero_registros(users_file, lista)+1;
	while (iniciar_sesion (users_file, lista, ultimo_registro)!=1){ //Intenta iniciar sesión hasta que lo hace correctamente
		espera (intentos); //Espera cada vez más tiempo entre intentos para iniciar sesion
		intentos++;
	}
	fclose (users_file);
	printf ("Sesion iniciada correctamente, accediendo al programa...");
	return 0;
}

int consulta_numero_registros (FILE *fichero, usuarios vector[]){
	//printf ("\n\nConsultando archivo de usuarios y claves de acceso...\n \n");
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
		printf ("Introduce el nombre de usuario:\n	");
		scanf ("%[^\n]s", new_user->user);
		fflush (stdin);
		printf ("Introduzca clave de acceso: \n	");
		scanf ("%[^\n]s", new_user->password);
		fflush (stdin);
		printf ("Confirme la clave de acceso:\n	");
		scanf ("%[^\n]s", &clave2);
		if (comparar_cadenas(new_user->password, clave2, TAM_PASSWORD)==1){
			salida = 1;
			printf ("Se ha creado el nuevo usuario.\n");
		}
		else {
			printf ("Error en la clave de acceso. No coinciden.\n");
		}
	}
	printf ("Guardando el nuevo usuario en la lista de usuarios \n");
	/*CONTIENE ERRORES - NO ESCRIBE BIEN EN EL ARCHIVO
	fichero = open ("usuarios.txt", "w");
	if (fichero == NULL){
		printf ("Error abriendo el fichero para guardar el nuevo usuario.");
		return -1;
	}
	fseek (fichero, 0, SEEK_END);
	fprintf (fichero, "\n%s;%s", new_user->user, new_user->password);
	//En esta parte no funciona, no consigo poder escribir en el archivo en la posicion final
	fclose (fichero); //Cierro el fichero
	fichero = fopen ("usuarios.txt", "r");
	
	*/
	
	//OPCIÓN QUE REESCRIBE TODO EL FICHERO, FUNCIONA
	printf ("\n Reescribiendo el fichero completo...\n");
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
	printf ("\nINICIAR SESION: \n[Si es la primera vez que inicia el programa seleccione la opc. 2]\n");
	printf ("	1. - Iniciar sesion como un usuario ya registrado.\n	2. - Crear un nuevo usuario. (Limite de usuarios 100). \n");
	scanf ("%i", &opcion);
	system("cls");
	system("clear");
	if (opcion==2){
		nuevo(fichero, &usuarios_existentes[ultimo_registro], ultimo_registro, usuarios_existentes);
		return 1; //No se pide introducir usuario y contraseña si se acaba de crear el usuario
	}
	else{ //Si no se ha elegido la opcion de crear un nuevo usuario entra automáticamente en esta, es la forma de evitar
		//tiempos de espera como si se hubiese cometido un error al introducir usuario y contraseña
		printf ("\nUsuario:\n	");
		fflush (stdin);
		scanf ("%[^\n]s", &temp.user);
		printf ("Clave de acceso:\n	");
		fflush (stdin);
		scanf ("%[^\n]s", &temp.password);
		for (i=0;i<ultimo_registro;i++){
			if(comparar_cadenas (usuarios_existentes[i].user, temp.user, TAM_USER)){
				if (comparar_cadenas(usuarios_existentes[i].password, temp.password, TAM_PASSWORD)){
					printf ("Usuario y clave de acceso correctos.\n");
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
	for (i=0;i<3000*intentos*intentos*intentos;i++) { //El tiempo de espera es exponencial
		printf (" %c", 8); //8 es el retroceso en la tabla ASCII. De esta forma se pierde tiempo pero no se llena la pantalla de nuevos carácteres
	}
	printf ("\n-------------------\n");
}




/*NOTAS______________________________
 * El fichero en el que se guardan los nombres de usuario y las contraseñas tiene la siguiente forma:
 * nombre de usuario de ejemplo; contraseña de ejemplo 1
 * nombre del usuario ejemplo 2; contraseña de ejemplo 2
 * ...
 * (El usuario se separa de la contraseña por punto y coma y los registros se separan por saltos de línea.
 */
