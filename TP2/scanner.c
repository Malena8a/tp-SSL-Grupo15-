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
int estadosTerminales[14] = {2,4,5,6,7,8,9,10,11,12,13,15,16,17};

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
    if (c == EOF) return FDT;

    if( c == '\n')
    {
        //printf("Soy un salto de linea\n");
    }

    //printf("llegue a este punto en el cual el caracter no es identificado\n");
    return OTRO;  // Otros 
}

int funcionDeTransicion(int estadoActual, char c)
{
    if( c == '\r' || c == '\n' || c == '\t' )
    {
        c = ' ';
    }
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

bool tipoDeError(cod_op estadoViejo, cod_op estadoActual, char c, cod_op* tipoError)
{
    //Si el estado viejo es 14 y el actual no es 15, error de asignacion
    if( estadoViejo == 14 && estadoActual != 15 )
    {
        *tipoError = ERROR_ASIGNACION;
        return true;
    }

    /*
    if( estadoViejo == 1 && estadoActual == 17 )
    {
        *tipoError = ERROR_COMUN;
        return true;
    }
    */

    if( estadoViejo == 0 && estadoActual == 17 )
    {
        if( c == '=' )
        {
            *tipoError = ERROR_ASIGNACION;
            //printf("Error de asignacion\n");
        }
        else
        {
            *tipoError = ERROR_COMUN;
            //printf("Error comun\n");
        }
        return true;
    }
    return false;
}

Lexema* escaner(FILE* f)
{
    //printf("Inicio.\n");

    //leer programa
    bool error = false;
    cod_op* tipoError = malloc(sizeof(cod_op));
    int estadoActual = 0;
    char* lexema = malloc(200);
    lexema[0] = '\0';  // buffer esté vacío al principio

    while( !esEstadoFinal(estadoActual) && !error )
    {
        // Obtenemos caracter
        char c;
        c = fgetc(f);

        // Leemos caracter y aplicamos funcion
        //printf("lei el caracter %c\n",c);
        int estadoViejo = estadoActual;
        estadoActual = funcionDeTransicion(estadoActual,c);

        // Aplicamos error
        error = tipoDeError(estadoViejo, estadoActual, c, tipoError);

        //printf("El estado actual es %d\n",estadoActual);
        
        //aplicamos comportamiento dependiendo del estado
        aplicarAccionSegunEstado(f, estadoActual, c);

        // Contatenamos para la devolucion
        char* ptr = malloc(sizeof(char));
        *ptr = c;
        if( !esCaracterDeEspacio(c) && estadoActual != 2 )
        {
            strncat(lexema,ptr,1);
        }
        
        free(ptr);

        //printf("Llegué hasta el fin\n");
    }


    //Devolucion

    Lexema* to_ret = malloc(sizeof(Lexema));
    to_ret->lexema = malloc(strlen(lexema)+1);
    to_ret->codigo = tipoDeToken(estadoActual,*tipoError);
    //printf("RETORNARÉ EL CODIGO %d\n", to_ret->codigo);
    strcpy(to_ret->lexema,lexema);

    //to_ret->codigo = 1;
    free(lexema);
    free(tipoError);
    return to_ret;
}

cod_op tipoDeToken(int estado, cod_op tipoDeError)
{
    if( tipoDeError == ERROR_COMUN)
    {
        //printf("We are gonna send a ERROR_COMUN\n");
        return 6;
    }
    else
    {
        if( tipoDeError == ERROR_ASIGNACION )
        {
            //printf("We are gonna send a ERROR_ASIGNACION\n");
            return 7;
        }    
    }

    if( estado == 2)//identificador
    {
        return 1;
    }
    else if(estado == 4) //Constante
    {
        return 2;
    }
    else if( estado == 5 || estado == 6 ||  estado == 7 || estado == 8 || estado == 9) //operador
    {
        return 4;
    }
    else if ( estado == 10 || estado == 11 ||  estado == 12 || estado == 13) //puntuacion
    {
        return 3;
    }
    else if ( estado ==15) //asignación
    {
        return 5;
    }
    else if( estado == 16) //fdt
    {
        return 0;
    }
    
}



void aplicarAccionSegunEstado(FILE* f, int estadoActual, char c)
{
    if( estadoActual == 2 )
    {
        ungetc(c,f);
    }
}

bool esCaracterDeEspacio(char c)
{
    return (c == '\n' || c == '\r' || c == '\t' || c == ' ');
}


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