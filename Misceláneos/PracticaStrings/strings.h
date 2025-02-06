#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM_PAL 100

#define esLetra(c)( ((c) >= 'A' && (c) <= 'Z' )|| ((c) >= 'a' && (c) <= 'z'))
#define aMayuscula(c)((c)>='a' && (c)<='z' ? (c) - ('a'- 'A'): (c))
#define aMinuscula(c)((c)>='a' && (c)<='z' ? (c) - ('a'- 'A'): (c))

typedef struct
{
    char* cursor;
    bool finSec;
}SecuenciaPalabra;

typedef struct
{
    char vectorPalabra[TAM_PAL];
}Palabra;

char*   normalizar(const char* cadNormalizar, char* cadNormalizada);
void    secPalCrear(SecuenciaPalabra* secuencia, const char* cad);
bool    secPalLeer(SecuenciaPalabra* secuencia, Palabra* palabra);
void    secPalEscribirCaracter(SecuenciaPalabra* secuencia, char c);
void    secPalCerrar(SecuenciaPalabra* secuencia);
#endif

