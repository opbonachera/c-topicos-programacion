#include "string.h"

// Ejercicio 1.6
bool esPalindromo(char* s1, char* s2)
{

    char* s2Copia = s2 + strlen(s2) - 1;

    while (*s1 != '\0' && s2Copia >= s2)
    {
        if (*s1 != *s2Copia)
        {
            return false;
        }

        s1++;
        s2Copia--;
    }

    return true;
}

// Ejercicio 1.7
int valorNumerico(char* s1) {
    int numero = 0;

    while(*s1 != '\0')
    {
        numero = numero * 10 + (*s1 - '0');
        s1++;
    }

    return numero;
}

// Ejercicio 1.8
int contarApariciones(char* texto, char* palabra)
{
    // Contar la cantidad de veces que aparece la cadena palabra dentro de texto
    // Listado de caso borde
    // - La palabra aparece
    // - La palabra no aparece
    // - Aparece una parte de la palabra
    // - Comparar el texto con la palabra. Devolver falso cuando los caracteres sean distintos.
    // - La palabra aparece mas de una vez


    int contador = 0;
    char *t, *p;

    while (*texto != '\0')
    {
        t = texto;
        p = palabra;

        while (*t != '\0' && *p != '\0' && aMinuscula(*t) == aMinuscula(*p))
        {
            t++;
            p++;
        }


        if (*p == '\0')
        {
            contador++;
        }

        texto++;
    }

    printf("El resultado es %d\n", contador);

    return contador;
}

// Ejercicio 1.9


