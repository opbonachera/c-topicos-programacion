#include "Palabra.h"


char* normalizar(const char* cadANormalizar, char* cadNormalizada, int cantPal)
{
    SecPal secLect, secEscr;
    int cantPalProc = 0;
    secPalCrear(&secLect, cadANormalizar);
    secPalCrear(&secEscr, cadNormalizada);

    Palabra pal;
    secPalLeer(&secLect, &pal);
    while(!secPalFin(&secLect) && cantPalProc < cantPal)
    {
        palabraATitulo(&pal);
        secPalEscribir(&secEscr, &pal);
        cantPalProc++;
        
        if(cantPalProc < cantPal && secPalLeer(&secLect, &pal))
        {
            secPalEscribirCar(&secEscr, ' ');
        }
    }
    
    secPalCerrar(&secEscr);

    return cadNormalizada;
}
