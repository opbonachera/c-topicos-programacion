#include <stdio.h>
#include <stdlib.h>

#include "Palabra.h"
int main()
{
    char cadANormalizar[50] = ".\'ornella ?paula., bonachera¿?03";
    char cadNormalizada[50] = "";

    secPalabra secLect;
    secPalabra secEscr;

    secuenciaCrear(&secLect, cadANormalizar);
    secuenciaCrear(&secEscr, cadNormalizada);

    tPalabra palabra;
    leerPalabra(&secLect, &palabra);

    while(!secuenciaFin(&secLect))
    {
        palabraATitulo(&palabra);
        palabraEscribir(&secEscr, &palabra);
        escribirCarecter(&secEscr, ' ');
        leerPalabra(&secLect, &palabra);
    }

    secuenciaCerrar(&secEscr);
    secuenciaCerrar(&secLect);

    printf("Cadena normalizada: [%s]\n", cadNormalizada);
    return 0;
}
