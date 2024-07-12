/*
tabla.c muestra por pantalla (stdout) las filas pedidas, llamando a la función de
conversión. Use assert para poner precondiciones sobre los valores de los parámetros
recibidos.
*/
#include <stdio.h>
#include <assert.h>

void tabla(int inicio, int fin, int incremento) {
    assert(inicio >= 0 && fin >= inicio && incremento > 0);

    for (int i = inicio; i <= fin; i += incremento) {
        printf("%d nudos = %.2f km/h\n", i, conversion(i));
    }
}