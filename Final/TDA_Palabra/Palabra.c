#include "Palabra.h"

int  secuenciaCrear(secPalabra* s, const char* cadena)
{
    s->cursor=cadena;
    s->finSec=0;
    return OK;
}

int  leerPalabra(secPalabra* sLect, tPalabra* palabra)
{
    while (*(sLect->cursor) != '\0' && !esLetra(*(sLect->cursor)))
        sLect->cursor++;

    if(*(sLect->cursor) == '\0')
    {
        sLect->finSec=1;
        return ERROR_LECTURA_PALABRA;
    }

    char* actPal = palabra->vPalabra;
    while(*(sLect->cursor) != '\0' && esLetra(*(sLect->cursor)))
    {
        *actPal = *(sLect->cursor);
        actPal++;
        sLect->cursor++;
    }

    *actPal = '\0';

    return OK;
}

int  secuenciaFin(const secPalabra* s)
{
    return s->finSec;
}

int  mostrarPalabra(const tPalabra* pal)
{
    char* i = pal->vPalabra;
    while(*i != '\0')
    {
        putchar(*i);
        i++;
    }

}

int  escribirCarecter(secPalabra* sEsc, char* c)
{
    *sEsc->cursor=c;
    sEsc->cursor++;

}
int  palabraEscribir(secPalabra* sEsc, tPalabra* palabra)
{
    const char* actPal = palabra->vPalabra;
    while(*actPal)
    {
        *sEsc->cursor = *actPal;
        sEsc->cursor++;
        actPal++;
    }
    return OK;
}

void secuenciaCerrar(secPalabra* s)
{
    *s->cursor='\0';
}

void palabraATitulo(tPalabra* palabra)
{
    char* actPal = palabra->vPalabra;
    *actPal = aMayuscula(*actPal);
    actPal++;

    while(*actPal)
    {
        *actPal = aMinuscula(*actPal);
        actPal++;
    }
}
