Resultados:

1. Muestre un comando que permita compilar todo el proyecto (sin el makefile) de acuerdo a los lineamientos del curso (adherir estrictamente al estándar).
gcc main.c tabla.c conversion.c -o programa


2. Compile con el comando anterior pero modifque tabla.c de modo que no incluya conversion.h, copie el resultado y coméntelo.

    $ gcc main.c tabla.c conversion.c -o programa
    tabla.c: In function 'tabla':
    tabla.c:10:5: warning: implicit declaration of function 'assert' [-Wimplicit-function-declaration]
    10 |     assert(inicio >= 0 && fin >= inicio && incremento > 0);
        |     ^~~~~~
    tabla.c:1:1: note: 'assert' is defined in header '<assert.h>'; did you forget to '#include <assert.h>'?
    +++ |+#include <assert.h>
        1 | /*
    tabla.c:12:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    12 |     printf(" |     Nudos|      Km/h|\n");
        |     ^~~~~~
    tabla.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
    +++ |+#include <stdio.h>
        1 | /*
    tabla.c:12:5: warning: incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
    12 |     printf(" |     Nudos|      Km/h|\n");
        |     ^~~~~~
    tabla.c:12:5: note: include '<stdio.h>' or provide a declaration of 'printf'
    tabla.c:15:48: warning: implicit declaration of function 'conversion' [-Wimplicit-function-declaration]
    15 |         printf(" |         %d|    %.2f|\n", i, conversion(i));
        |                                                ^~~~~~~~~~
    C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\lucas\AppData\Local\Temp\cce7A3Ms.o:tabla.c:(.text+0x35): undefined reference to `assert'
    collect2.exe: error: ld returned 1 exit status

Al no incluir el encabezado conversion.h entonces no contariamos con la capacidad de utilizar las funciones: conversion, printf y assert. Conversion forma parte de los archivos conversion.c y conversion.h y las bibliotecas que incluyen las funciones printf y assert están incluídas en dicho archivo.

3. De un comando que compile todos los fuentes menos tabla.c, ejecútelo, muestre el resultado y coméntelo.

    $ gcc main.c conversion.c -o programa_sin_tabla
    C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\lucas\AppData\Local\Temp\cc0XXatS.o:main.c:(.text+0x8e): undefined reference to `tabla'
    collect2.exe: error: ld returned 1 exit status

Al no ejecutar tabla.c junto con el resto del programa, cuando en main.c se quiere referenciar a la función tabla no podrá encontrarla y finalmente arrojará un error.

4. Copie el comando necesario para obtener conversion.i, el archivo ya preprocesado de conversion.c

gcc -E conversión.c -o conversión.i

Nota: comentar significa analizar el resultado, ver que tipo de error es, donde se produce, etc.
