#include <./conversion.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Error: Faltan argumentos. Uso: programa inicio fin [incremento]\n");
        return 1;
    }

    int inicio = atoi(argv[1]);
    int fin = atoi(argv[2]);
    int incremento = (argc == 4) ? atoi(argv[3]) : 1;

    //tabla(inicio, fin, incremento);
    printf("%d\n",inicio);
    printf("%d\n",fin);
    printf("%d\n",incremento);

    return 0;
}
