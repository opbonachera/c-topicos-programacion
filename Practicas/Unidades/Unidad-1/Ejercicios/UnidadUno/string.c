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

    return contador;
}

// Ejercicio 1.9
// Normalizar cadena
/*
    Crear una secuencia de palabras
    Leer una palabra. Cuando se encuentra un caracter, leer hasta que se encuetnre un retorno de carro,
*/



void normalizarCadena()
{
    SecPal secLect, secEscr;

    char cadANormalizar[] = "#$%@#esTa@#$eS$#%^uNA$%^&^(())cAdenA@#$PaRa#$%nORmalIZar@#$@#";
    char cadNormalizada[TAM_PAL];

    secPalCrear(&secLect, cadANormalizar);
    secPalCrear(&secEscr, cadNormalizada);

    Palabra pal;
    secPalLeer(&secLect, &pal);
    while(!secPalFin(&secLect))
    {
        palabraATitulo(&pal);
        secPalEscribir(&secEscr, &pal);


        if(secPalLeer(&secLect, &pal))
        {
            secPalEscribirCar(&secEscr, ' ');
        }
    }

    secPalCerrar(&secEscr);

    printf("Cadena normalizada: %s\n", cadNormalizada);
    return cadNormalizada;

}

void palabraATitulo(Palabra* pal)
{
    const char* palabra = pal->pal;

    aMayuscula(*palabra);
    palabra++;

    while(*palabra!='\0')
    {
        aMinuscula(*palabra);
        palabra++;
    }
}

void secPalCrear(SecPal* sec, const char* cad)
{
    sec->cursor = (char*)cad;
    sec->finSec = false;
}

void secPalCerrar(SecPal* sec)
{
    sec->cursor = '\0';
}

bool secPalFin(SecPal* sec)
{
    return sec->finSec;
}

bool secPalLeer(SecPal* sec, Palabra* pal)
{
    if(!*sec->cursor && !esLetra(*sec->cursor))
    {
        sec->cursor++;
    }

    if(!(*sec->cursor))
    {
        sec->finSec = true;
        return false;
    }

    char* palEncontrada = pal->pal;
    if(*sec->cursor != '\0' && esLetra(*sec->cursor))
    {
        *palEncontrada = *sec->cursor;

        palEncontrada++;
        sec->cursor++;
    }

    *palEncontrada = '\0';
    return true;
}

void secPalEscribir(SecPal* sec, Palabra* pal)
{
    // Colocar el cursor de la secuencia con el puntero de la palabra a la misma altura
    // Copiar los caracteres de la estructura palabra a la secuencia
    // Caso borde: la palabra llego a su fin '\0'
    const char* palEncontrada = pal->pal;
    while(*pal->pal != '\0')
    {
        *sec->cursor = *palEncontrada;
        sec->cursor++;
        palEncontrada++;
    }
}

void secPalEscribirCar(SecPal* sec, const char* c)
{
    *sec->cursor = c;
    sec->cursor++;
}
