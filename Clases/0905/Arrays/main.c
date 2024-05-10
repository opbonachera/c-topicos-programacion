#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define SIN_MEMORIA 1
#define TAM 10
#define NUEVO_TAM 15

int main()
{
    int *p = (int*)malloc(sizeof(int) * TAM); // Casteamos a int ya que malloc devuelve un void

    if(!p) // Si p devuelve NULL, significa que no pudo reservarse memoria.
    {
        return SIN_MEMORIA;
    }

    iniciarVector(p,TAM);
    mostrarVector(p,TAM);

    printf("%x\n", p);

    int *auxP = (int *)realloc(p, sizeof(int) * NUEVO_TAM);
    if(!auxP)
    {
        free(p);
        return SIN_MEMORIA; // Verificamos que se pueda reservar memoria correctamente
    }

    p = auxP;

    mostrarVector(p,NUEVO_TAM);
    iniciarParteVector(p,NUEVO_TAM,10);

    printf("%x\n", p);

    free(p);
    return 0;
}

void iniciarVector(int *p, size_t ce)
{
    int i;
    for(i=0; i<ce; ++i)
    {
        *p = i;
        p++;
    }
}

void mostrarVector(const int *p, size_t ce)
{
    int i;

    printf("Mostrando vector\n");
    for(i=0; i<ce; ++i)
    {
        printf("(%d) ", *p);
        p++;
    }
}

void iniciarParteVector(int *p, size_t ce, size_t indiceInicial)
{
    int *q = p + indiceInicial;
    while(q < p+ce) // Mientras q no apunte a la ultima direccion valida
    {
        *q = q-p; // Le resto a q el elemento inicializado
        q++;
    }
}
