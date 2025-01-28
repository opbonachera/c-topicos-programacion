#ifndef EJERCICIOS_STRINGS_INCLUDED
#define EJERCICIOS_STRINGS_INCLUDED

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define TAM_PAL 30

typedef struct
{
    char* cursor;
    bool finSec;
}
SecPal;


typedef struct
{
    char vPal[TAM_PAL];
}
Palabra;

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a' - 'A') : (c))
#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a' - 'A') : (c))

bool esPalindromo(char* s1, char* s2);
int  valorNumerico(char* s1);
int  contarApariciones(char* texto, char* palabra);

void secPalCrear(SecPal* sec, const char* cad);
bool secPalLeer(SecPal* sec, Palabra* pal);
void secPalEscribir(SecPal* sec, const Palabra* pal);
void secPalEscribirCar(SecPal* sec, char c);
bool secPalFin(SecPal* sec);
void secPalCerrar(SecPal* sec);
void palabraATitulo(Palabra* pal);

#endif // EJERCICIOS_STRINGS_INCLUDED
