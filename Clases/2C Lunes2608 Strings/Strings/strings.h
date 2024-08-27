#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#define TAM_PAL 31

typedef struct
{
    char* cursor;
    bool  finSec;
}SecPal;

typedef struct
{
    char vPal[TAM_PAL];
}Palabra;

int normalizar(cadANormalizar, cadNormalizada);

#endif // STRINGS_H_INCLUDED
