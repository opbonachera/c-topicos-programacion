#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#define TAM_MAX_PALABRA 30
#define TAM_LINEA 100

#define ES_LETRA(c)( ((c)>='a' && c<='z') ||  ((c)>='A' && c<='Z'))

#include <stdio.h>
#include <string.h>

typedef struct
{
    char* cursor;
    int   finSec;
}tSecPal;

typedef struct
{
    char palabra[TAM_MAX_PALABRA];
}tPalabra;

void tSecPalCrear(tSecPal* sPal, char* linea);
void tSecPalCerrar(tSecPal* sPal);
int  tSecPalFin(tSecPal* sPal);
int  tSecPalLeer(tSecPal* sPal, tPalabra* pal);

#endif // PALABRA_H_INCLUDED
