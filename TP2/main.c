#include "scanner.h"

int main()
{
    // Abrir el archivo
    

    FILE* file = fopen("entrada.txt","r+b");
    //escaner(file);
    crearTabla();
    mostrar_tabla_transiciones();

    bool fDT = false;

    while( !fDT )
    {

        Lexema* lexema = escaner(file);
        //recibir codigo de operacion
        // Manejo del token
        
        switch (lexema->codigo) {
            case 0: // Estado inicial
                break;
            case 1: // Identificador
                // Manejo de identificador
                //printf("Llego el siguiente lexema: %s\n",lexema->lexema);
                printf("Identificador '%s'\n",lexema->lexema);
                break;
            case 2: // Constante
                // Manejo de constante
                printf("Constante '%s'\n",lexema->lexema);
                break;
            case 3: // Palabra reservada
                // Manejo de palabra reservada
                break;
            case 4: // Operador
                // Manejo de operador
                break;
            case 5: // Asignación
                // Manejo de asignación
                break;
            case 6: // Carácter de puntuación
                // Manejo de carácter de puntuación
                break;
            case 7: // Comentario
                // Manejo de comentario
                break;
            case 8: // Error
                // Manejo de error
                break;
        }
        free(lexema);
    }
    return 0;

}