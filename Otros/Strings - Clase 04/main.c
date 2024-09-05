#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define esBlanco(X) (return strcmpi(X,' ') ? 1 : 0)

int comparar(const char *, const char *);
char *normalizarCadena(char *, const char *);

int main()
{
    return 0;
}

int comparar(const char *s1, const char *s2)
{

}

char* normalizarCadena(char* dest, const char* orig)
{
    char* destInicial = dest;

    while(*orig)
    {
        while(esBlanco(*orig))
            orig++;

        if(*orig)
        {
            *dest = toupper(*orig);
            dest++;
            orig++;

            while(!esBlanco(*orig) && *orig)
            {
                *dest = tolower(*orig);
                dest++;
                orig++;
            }

            if(esBlanco(*orig))
            {
                *dest = ' ';
                dest++;
                orig++;
            }
        }
    }

    if(dest > destInicial && *(dest-1) == ' ') // Para saber si se movio el puntero
        dest--;

    *dest = '\0';

    return dest;
}
