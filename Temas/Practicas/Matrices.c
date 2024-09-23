#include "Matrices.h"

void** crearMatriz(size_t orden, size_t tamElemento)
{
    void** matriz = malloc(orden * sizeof(void*));
    void** ult = matriz + orden - 1;

    for(void** i=matriz; i < ult; i++)
    {
        *i = malloc(tamElemento * orden);

        if(!(*i))
            printf("Error al reservar memoria.\n");
            free(*i);
            return ERROR_DE_MEMORIA;

    }

    return matriz;
}

void cargarMatriz(int** matriz, size_t orden)
{
    for(int* i = matriz; i < orden * orden; i++)
    {
        *i = (i+1);
        i++;

    }
}
