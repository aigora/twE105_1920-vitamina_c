#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define MAX_NO_PUERTOS_COM 9
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
void Serial_search (Serial *puertoserie);
