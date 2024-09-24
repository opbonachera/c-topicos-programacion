#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cadena.h"

#define TAM_CAD 501


// bmpmanipuleitor unlam.bmp --aumentar-brillo=30

// Palabra #$%@#esTa@#$eS$#%^uNA$%^&^(())cAdenA@#$PaRa#$%nORmalIZar@#$@ --cant-pal=3

int main(int argc, char* argv[])
{
//    char cadANormalizar[] = "#$%@#esTa@#$eS$#%^uNA$%^&^(())cAdenA@#$PaRa#$%nORmalIZar@#$@#";
    char cadNormalizada[TAM_CAD];

    printf("Nombre del programa: %s\n", argv[0]);

    char* igual = strchr(argv[2], '=');

    if(!igual)
        return 1;

    int cantPal = atoi(igual+1);

    normalizar(argv[1], cadNormalizada, cantPal);

    puts(cadNormalizada);


    // char cad[14];
    // char cad2[31] = "Hola que tal?";

    // strcpy(cad, cad2);

    // printf("cad: %s\n", cad);

    // strcat(cad2, "Todo bien.");

    // printf("cad2 concatenada: %s\n", cad2);

    // printf("cad: %s\n", cad);

    // char* q = strchr(cad2, 'q');

    // printf("Desde la q: %s\n", q);

    // char* signoPreg = strchr(cad2, '?');
    // *signoPreg = '\0';

    // printf("Desde la q: %s\n", q);

    return 0;
}
