#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <string.h>
#include <stdbool.h>

#define TAM_PAL 30

typedef struct
{
    char* cursor;
    bool finSec;
}
SecPal;


typedef struct
{
    char pal[TAM_PAL];
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
void secPalEscribir(SecPal* sec, Palabra* pal);
void secPalEscribirCar(SecPal* sec, const char* c);
bool secPalFin(SecPal* sec);
void secPalCerrar(SecPal* sec);
void palabraATitulo(Palabra* pal);
void normalizarCadena();

#endif // STRING_H_INCLUDED
