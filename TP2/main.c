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
                
                fDT = true;
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
            case 3: // // Carácter de puntuación
                // Manejo de carácter de puntuación
                if (strcmp(lexema->lexema, "(") ==0) {printf("Parentesis que abre '%s'\n",lexema->lexema);}
                if (strcmp(lexema->lexema, ")") ==0) {printf("Parentesis que cierra '%s'\n",lexema->lexema);}
                if (strcmp(lexema->lexema, ",") ==0) {printf("Coma '%s'\n",lexema->lexema);} 
                if (strcmp(lexema->lexema, ";") ==0) {printf("Punto y coma '%s'\n",lexema->lexema);}
                
                break;
            case 4: // Operador
                // Manejo de operador
                
                //printf("El operador que llego es %s\n",lexema->lexema);
                if (strcmp(lexema->lexema, "+") ==0) {printf("Mas '%s'\n",lexema->lexema);}
                if (strcmp(lexema->lexema, "-") ==0) {printf("Menos '%s'\n",lexema->lexema);}
                if (strcmp(lexema->lexema, "*") ==0) {printf("Multiplicacion '%s'\n",lexema->lexema);} 
                if (strcmp(lexema->lexema, "%%") ==0) {printf("Resto '%s'\n",lexema->lexema);} 
                if (strcmp(lexema->lexema, "/") ==0) {printf("Division '%s'\n",lexema->lexema);}
                
                break;
            case 5: // Asignación
                // Manejo de asignación
                if (strcmp(lexema->lexema, ":=") ==0) {printf("Asignacion '%s'\n",lexema->lexema);}
                break;
            case 6: // Error general
                // Manejo de comentario
                printf("Error general '%s'\n",lexema->lexema);
                break;
            case 7: // Error en asigancion
                // Manejo de error
                //printf("El lexema que tenemos es %s\n",lexema->lexema);
                if (strcmp(lexema->lexema, ":") ==0) {printf("Error en asignacion por : solo  '%s'\n",lexema->lexema);}
                if (strcmp(lexema->lexema, "=") ==0) {printf("Error en asignacion por = solo  '%s'\n",lexema->lexema);}

                break;
        }
        free(lexema);
    }
    return 0;

}