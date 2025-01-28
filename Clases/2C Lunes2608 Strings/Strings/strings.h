#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAM_PALABRA 31

#define esLetra(c)(((c)>= 'A' && (c) <= 'z') || ((c) >='a' && (c) <= 'z'))
#define aMayuscula(c)( (c) >= 'a' && (c) <= 'z' ? (c) - ('a' - 'A') : (c))
#define aMinuscula(c)( ((c) >= 'A' && (c) <= 'Z') ? ((c) + ('a' - 'A')) : (c))


typedef struct
{
    char* cursor;
    bool  finSec;
}
SecuenciaPalabra;

typedef struct
{
    char vectorPalabra[TAM_PALABRA];
}
Palabra;

char* normalizar(const char* cadenaANormalizar, const char* cadenaNormalizada);
void secPalCrear(SecuenciaPalabra* sec, Palabra *palabra);
bool secPalLeer(SecuenciaPalabra* sec, Palabra *palabra);
void secPalEscribir(SecuenciaPalabra* sec, const Palabra* pal);
void secPalEscribirCar(SecuenciaPalabra* sec, char c);
void secPalCerrar(SecuenciaPalabra* sec);
void palabraATitulo(Palabra* palabra);

int  obtenerParametro(char* argumento);
bool validarRango(int limiteInferior, int limiteSuperior, int valor);

// bool esLetra(char c);
// char aMayuscula(char c);
//char aMinuscula(char c);


#endif // STRINGS_H_INCLUDED
