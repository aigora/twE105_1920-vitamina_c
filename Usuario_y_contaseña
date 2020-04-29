#include <stdio.h>
typedef struct
{
	char contrasena[30];
	char usuario [30];
}Datos;
void pedirDatos(Datos *p)
{
  printf("Introduzca Usuario\n");
  scanf("%s",p->usuario);
  printf("Introduzca Contaseña\n");
  scanf("%s",p->contrasena);
}
void ImprimirDatos(Datos c)
{
	printf("%s\n%s",c.usuario,c.contrasena);
}
void main ()
{
	Datos r;
	pedirDatos(&r);
	ImprimirDatos(r);
}
