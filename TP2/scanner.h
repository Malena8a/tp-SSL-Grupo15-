#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum{
    IDENTIFICADOR,
    CONSTANTE,
    PALABRARESERVADA,
    OPERADOR,
    ASIGNACION,
    CARACTER_PUNTUACION,
    ERROR_COMUN,
    ERROR_ASIGNACION
} cod_op;


typedef struct 
{
    char* lexema;
    cod_op codigo;
} Lexema;

Lexema* escaner(FILE* f);

void crearTabla();

void mostrar_tabla_transiciones();