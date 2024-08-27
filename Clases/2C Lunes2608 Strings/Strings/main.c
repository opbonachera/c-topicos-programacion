#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /*char cad[32];
    char cad2[32] = "Hola como estas? ";

    strcpy(cad, cad2);

    strcat(cad2, " Todo bien.");

    char cadBusq[30] = "achicar=10";

    char *busqIgual = strchr(cadBusq, '=');
    printf("Caracter (%c) encontrado en: %p\n", *busqIgual, (void*)busqIgual);


    char *busqIgualA = strchr(cadBusq, '=');
    if (busqIgualA != NULL) {
        printf("Cadena desde '=': (%s)\n", busqIgualA);
    } else {
        printf("No se encontró '=' en la cadena.\n");
    }*/

    // Hacer las funciones más basicas de la biblioteca ctype
    // Hacer las funciones más basicas de la biblioteca strchar
    char cadANormalizar[] = "$#%#$&Hola%$#%$#esTa$##eS$#Una cadena.";
    char cadNormalizada[];

    normalizar(cadANormalizar, cadNormalizada);

    printf("Cadena original: (%s)");
    printf("Cadena normalizada: (%s)");

    return 0;
}

