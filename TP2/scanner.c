#include "scanner.h"
#define L 0
#define D 1
#define MAS 2
#define MENOS 3
#define ASTERISCO 4
#define BARRA 5
#define PORCIENTO 6
#define PARENT_ABRE 7
#define PARENT_CIERRA 8
#define COMA 9
#define PUNTO_COMA 10
#define DOS_PUNTOS 11
#define IGUAL 12
#define FDT 13
#define ESP 14
#define OTRO 15

int tabla[18][16];
int estadosTerminales[13] = {2,4,5,6,7,8,9,10,11,12,13,15,16};

int tipoDeCaracter(char c)
{
    if (isalpha(c)) return L;  // Letras
    if (isdigit(c)) return D;  // Dígitos
    if (c == ':') return DOS_PUNTOS;
    if (c == '+' ) return MAS;
    if (c == '-') return MENOS;
    if (c == '*' ) return ASTERISCO;
    if  (c == '/') return BARRA;
    if (c == '%') return PORCIENTO;
    if (c == '(') return PARENT_ABRE;
    if (c == ')') return PARENT_CIERRA;
    if (c == ',') return COMA;
    if (c == ';') return PUNTO_COMA;
    if (c == ' ') return ESP;
    if (c == '=') return IGUAL;

    if( c == '\n')
    {
        printf("Soy un salto de linea\n");
    }

    printf("llegue a este punto en el cual el caracter no es identificado\n");
    return OTRO;  // Otros
}

int funcionDeTransicion(int estadoActual, char c)
{
    int caracter = tipoDeCaracter(c);
    return tabla[estadoActual][caracter];
}

bool esMiembro(int arr[], int tamaño, int elemento) {
    for (int i = 0; i < tamaño; i++) {
        if (arr[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool esEstadoFinal(int estadoActual)
{
    return esMiembro(estadosTerminales,13,estadoActual);
}

Lexema* escaner(FILE* f)
{
    printf("Inicio.\n");

    //leer programa
    int estadoActual = 0;
    char* lexema = malloc(200);
    lexema[0] = '\0';  // Asegúrate de que el buffer esté vacío al principio
    
    while( !esEstadoFinal(estadoActual) )
    {
        //leer valor
        char c;
        c = fgetc(f);
        while( c == '\r' || c == '\n' || c == '\t' )
        {
            c = fgetc(f);
        }

        printf("lei el caracter %d\n",c);
        estadoActual = funcionDeTransicion(estadoActual,c);

        printf("El estado actual es %d\n",estadoActual);

        char* ptr = malloc(sizeof(char));
        *ptr = c;

        strncat(lexema,ptr,1);
        free(ptr);
    }

    Lexema* to_ret = malloc(sizeof(Lexema));
    to_ret->lexema = malloc(strlen(lexema)+1);
    strcpy(to_ret->lexema,lexema);
    to_ret->codigo = 1;
    return to_ret;
}

/*
estado := INICIAL;
 while not debo_parar(estado)
    Leer caracter
    estado := T[estado][caracter]; // otras acciones como contar líneas Armar lexema, et
 end while;
 if aceptor(estado) then
    if centinela(estado) then
        unput(caracter);
    accept(estado); // retornar token 
 else
    error; //devolver token de error o invocar rutina de manejor de error 
 end if;

*/

/*
Token get_next_token() {
    Token token;
    char c;
    int column;

    // Inicializa el token
    token.type = TOKEN_ERROR;
    token.lexema[0] = '\0';

    // Leer carácter
    c = getchar();
    if (c == EOF) {
        token.type = TOKEN_FDT;
        return token;
    }

    column = get_column_index(c);
    current_state = transition_table[current_state][column];

    // Manejo del token
    switch (current_state) {
        case 0: // Estado inicial
            break;
        case 1: // Identificador
            // Manejo de identificador
            break;
        case 2: // Constante
            // Manejo de constante
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

    return token;
}
*/


void crearTabla()
{
    //[fila][columna]
    //Estado cero
    tabla[0][0] = 1; //L
    tabla[0][1] = 3; //D
    tabla[0][2] = 5; //+
    tabla[0][3] = 6; //-
    tabla[0][4] = 7; //*
    tabla[0][5] = 8; // /
    tabla[0][6] = 9; // %
    tabla[0][7] = 10; // (
    tabla[0][8] = 11; // )
    tabla[0][9] = 12; // ,
    tabla[0][10] = 13; // ;
    tabla[0][11] = 14; // :
    tabla[0][12] = 17; // =
    tabla[0][13] = 16; // FDT
    tabla[0][14] = 0; // ESPACIO
    tabla[0][15] = 17; // OTRO

    //Estado uno
    tabla[1][0] = 1;
    tabla[1][1] = 1;
    for(int j = 2; j < 16; j++)
    {
        tabla[1][j]=2;
    }
    
    //Estado dos
    for(int j = 0; j < 16; j++)
    {
        tabla[2][j]=99;
    }
    
    //Estado tres
    for(int j = 0; j < 16; j++)
    {
        if( j == 1 )
        {
            tabla[3][j]=3;
        }
        else
        {
            tabla[3][j]=4;
        }
    }

    //Estado cuatro al trece
    for (int i = 4; i <= 13; i++) {
        for (int j = 0; j < 16; j++) {
            tabla[i][j] = 99; // Estado de error para todos los caracteres
        }
    }

    //Estado catorce
    for(int j = 0; j < 16; j++)
    {
        if( j == 12)
        {
            tabla[14][j] = 15;
        }
        else
        {
            tabla[14][j]=17;
        }
    }   

    //Estado quince a 17
    for (int i = 15; i <= 17; i++) {
        for (int j = 0; j < 16; j++) {
            tabla[i][j] = 99; // Estado de error para todos los caracteres
        }
    }

}

// Función para mostrar la tabla (opcional)
void mostrar_tabla_transiciones() {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%2d ", tabla[i][j]);
        }
        printf("\n");
    }
}