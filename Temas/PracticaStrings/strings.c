#include "strings.h"

char* normalizar(const char* cadNormalizar, char* cadNormalizada)
{
    SecuenciaPalabra secLectura, secEscritura;
    Palabra palabra;

    secPalCrear(&secLectura, cadNormalizar);
    secPalCrear(&secEscritura, cadNormalizada);

    secPalLeer(&secLectura, &palabra);
    while(!secPalLeer(&secLectura, &palabra))
    {
        palabraATitulo(&palabra);
        secPalEscribir(&secEscritura, &palabra);
        secPalEscribirCaracter(&secEscritura, ' ');
        secPalLeer(&secLectura, &palabra);
    }

    secPalCerrar(&secEscritura);
    return cadNormalizada;
}

void secPalCrear(SecuenciaPalabra* secuencia, const char* cad)
{
    secuencia->cursor = cad;
    secuencia->finSec = false;
}

bool secPalLeer(SecuenciaPalabra* secuencia, Palabra* palabra)
{
    while(*secuencia->cursor && !esLetra(*secuencia->cursor))
    {
        secuencia->cursor++;
        // Busca el primer caracter que cumple ser letra
    }

    if(*secuencia->cursor == '\0')
    {
        // Indica si se llego al final de la cadena
        secuencia->finSec=true;
        return false;
    }

    char* actPal = palabra->vectorPalabra;
    while(*secuencia->cursor && esLetra(*secuencia->cursor)) // Encontro una letra (palabra)
    {
        *actPal = *secuencia->cursor;
        actPal++;
        secuencia->cursor++;
    }

    *actPal = '\0';

    return true;
}

void secPalEscribir(SecuenciaPalabra* secuencia, Palabra palabra}
{
    char* actPal = palabra->vectorPalabra;
    while(*secuencia->cursor && esLetra(*secuencia->cursor)) // Encontro una letra (palabra)
    {
        *actPal = *secuencia->cursor;
        actPal++;
        secuencia->cursor++;
    }
}
void palabraATitulo(Palabra* palabra)
{
    char* actPal = palabra->vectorPalabra;
    *actPal = aMayuscula(*actPal);
    actPal++;

    while(*actPal)
    {
        *actPal = aMinuscula(*actPal);
        actPal++;
    }
}

bool secPalFin(SecuenciaPalabra* secuencia)
{
    return secuencia->finSec;
}

void secPalCerrar(SecuenciaPalabra* secuencia)
{
    *secuencia->cursor = '\0';
}

void secPalEscribirCaracter(SecuenciaPalabra* secuencia, char c)
{
    *secuencia->cursor = c;
    secuencia->cursor++;
}
