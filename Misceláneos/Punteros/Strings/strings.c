#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "strings.h"

#define esBlanco(ch) ((ch) == ' ' ? 1 : 0)
#define esEspacio(ch) ((ch) == '\n' ? 1 : 0)

int imprimirCadena(char *cadena)
{
    while (*cadena != '\0')
    {
        printf("%c", *cadena);
        cadena++;
    }
    printf("\n");
    return OK;
}

char* normalizarCadena(char *cadenaDestino, char *cadenaOrigen)
{
    char* destino = cadenaDestino;
    char* destinoInicial = cadenaDestino;

    while (*cadenaOrigen != '\0')
    {
        while (esBlanco(*cadenaOrigen) || esEspacio(*cadenaOrigen))
        {
            cadenaOrigen++;
        }

        if (*cadenaOrigen != '\0')
        {
            *destino = toupper(*cadenaOrigen);
            destino++;
            cadenaOrigen++;
        }

        // Copy the rest of the string
        while (*cadenaOrigen != '\0')
        {
            // Si en la cadena origen encontramos un espacio o salto de linea no lo copiamos
            while (esBlanco(*cadenaOrigen) || esEspacio(*cadenaOrigen))
            {
                cadenaOrigen++;
                // Si el siguiente caracter no es retorno de carro agregar un espacio
                if (*cadenaOrigen != '\0')
                {
                    *destino = ' ';
                    destino++;
                }
            }

            // Copiamos los caracteres siguientes en minuscula
            if (*cadenaOrigen != '\0')
            {
                *destino = tolower(*cadenaOrigen);
                destino++;
                cadenaOrigen++;
            }
        }
    }

    if (destino > destinoInicial && *(destino - 1) == ' ')
    {
        destino--;
    }

    *destino = '\0';

    return destinoInicial;
}


int compararCadenas(char* s1, char* s2)
{
    while( *s1 != '\0' && *s2 != '\0' )
    {
        if(*s1 != *s2)
        {
            // Si son iguales devuelve n positivo
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
         else
        {
            // Incrementamos los punteros en una unidad si son iguales
            s1++;
            s2++;
        }
    }

    // Si son iguales devuelve 0;
    return (unsigned char)*s1 - (unsigned char)*s2;
}
