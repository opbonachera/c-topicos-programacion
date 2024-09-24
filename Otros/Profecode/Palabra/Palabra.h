#ifndef PALABRA_H
#define PALABRA_H

#include <stdbool.h>

#define TAM_PAL 31


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


void secPalCrear(SecPal* sec, const char* cad);
bool secPalLeer(SecPal* sec, Palabra* pal);
void secPalEscribir(SecPal* sec, const Palabra* pal);
void secPalEscribirCar(SecPal* sec, char c);
bool secPalFin(const SecPal* sec);
void secPalCerrar(SecPal* sec);
void palabraATitulo(Palabra* pal);

// bool esletra(char c);
// char aMayuscula(char c);
// char aMinuscula(char c);


#endif // PALABRA_H
