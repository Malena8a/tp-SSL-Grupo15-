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

bool tipoDeError(cod_op estadoViejo, cod_op estadoActual, char c, cod_op* tipoError);

bool esCaracterDeEspacio(char c);

void aplicarAccionSegunEstado(FILE* f, int estadoActual, char);

void mostrar_tabla_transiciones();
cod_op tipoDeToken(int estado, cod_op tipoDeError);