#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <string.h>
#include <stdbool.h>

#define TAM_PAL 30

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define aMayuscula(c) ((c) >= 'a' && (c) <= 'z' ? (c) - ('a' - 'A') : (c))
#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a' - 'A') : (c))

bool esPalindromo(char* s1, char* s2);
int  valorNumerico(char* s1);
int  contarApariciones(char* texto, char* palabra);

#endif // STRING_H_INCLUDED
