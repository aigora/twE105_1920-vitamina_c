//constantes con los tamaños de algunos elementos del programa. Modificar según necesidades:
#define MAX_USERS 100
#define TAM_USER 30
#define TAM_PASSWORD 30
#include<stdio.h>
typedef struct{
	char user[TAM_USER];
	char password[TAM_PASSWORD];
}usuarios;
void nuevo (FILE *fichero, usuarios *new_user, int ultimo_registro, usuarios lista[]);
_Bool iniciar_sesion (FILE *fichero, usuarios usuarios_existentes[], int ultimo_registro); //El fichero es solo por si se elige crear un usuario
int consulta_registros(FILE *fichero, usuarios vector[]); //Lee el fichero para averiguar el número de registros existentes (requiere como argumento el puntero al archivo) y además lee y guarda los datos en un vector dado
_Bool comparar_cadenas (char *cadena1, char *cadena2, int l1);
void espera (int intentos);
int inicio_normal();
