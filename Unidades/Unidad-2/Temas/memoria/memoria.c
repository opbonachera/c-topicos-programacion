#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoria.h"

int almacenar10Enteros()
{
    int* enteros = (int*)malloc(10 * sizeof(int));
    if(enteros==NULL)
    {
        printf("Hubo un problema al reservar la memoria.\n");
    }

    printf("Memoria reservada correctamente.\n");

    for(int i=0; i<10; i++)
    {
        enteros[i] = i;
    }
    printf("Imprimiendo vector...\n");

    for(int i=0; i<10; i++)
    {
        printf("%d ", enteros[i] + 1);
    }

    free(enteros);
}


int printVector(int *vec, const int ce)
{
    int i;
    for(i=0; i<ce; i++)
    {
        printf("%d ", *vec);
        vec++;
    }
    return 0;
}

