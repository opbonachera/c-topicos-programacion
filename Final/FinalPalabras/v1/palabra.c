#include "palabra.h"

void tSecPalCrear(tSecPal* sPal, char* linea)
{
    sPal->cursor=linea;
    sPal->finSec=0;
}

void tSecPalCerrar(tSecPal* sPal)
{
    sPal->finSec=1;
}

int  tSecPalFin(tSecPal* sPal)
{
    return sPal->finSec;
}

int  tSecPalLeer(tSecPal* sPal, tPalabra* pal)
{
    while( *(sPal->cursor) != '\0' && !ES_LETRA( *(sPal->cursor)) )
        sPal->cursor++;

    if(*(sPal->cursor) == '\0' )
    {
        sPal->finSec=1;
        return 0;
    }

    char* actPal=pal->palabra;
    while( *(sPal->cursor) != '\0' && ES_LETRA(*(sPal->cursor)) )
    {
       *actPal = *sPal->cursor;
       actPal++;
       sPal->cursor++;
    }

    *actPal='\0';

    return 1;
}
