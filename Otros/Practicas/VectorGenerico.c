#include "VectorGenerico.h"


int inicializarVector(VectorGenerico* vector)
{
    vector->cap = 15;
    vector->ce  = 15;
    vector->tamElemento = sizeof(int);
    vector->vec = malloc( vector->tamElemento * vector->ce);


    if(!vector->vec)
    {
        return ERROR_DE_MEMORIA;
    }

    return OK;
}

int inicializarValoresEnteros(VectorGenerico* vector)
{
    int* posicion = (int*)vector->vec;
    for(size_t i=0; i < vector->ce; i++)
    {
        *posicion = i + 1;
        posicion++;
    }
    return OK;
}

int imprimirVectorEnteros(VectorGenerico* vector)
{
    int* posicion = (int*)vector->vec;
    for(size_t i = 0; i < vector->ce; i++)
    {
        printf("%d\n", *posicion);
        posicion++;
    }
    return OK;
}

int redimensionarVector(VectorGenerico* vector)
{
    void* nuevoPuntero = realloc(vector->vec, sizeof(vector->tamElemento) * FACTOR_REDIMENSION);

    if(!nuevoPuntero)
    {
        printf("Error: No se pudo reservar mas memoria.\n");
        return ERROR_DE_MEMORIA;
    }

    vector->ce = vector->ce * FACTOR_REDIMENSION;

    return OK;
}

int destruirVector(VectorGenerico* vector)
{
    free(vector->vec);
    vector->ce=0;
    vector->cap=0;

    return OK;
}

int insertarEnteroOrdenado(VectorGenerico* vector, int* elemento)
{
    /*size_t posIns = 0;

    if(vector->cap == vector->ce)
        redimensionarVector(vector);

    while(posIns <= vector->ce && *(vector->vec[posIns]))
        posIns++;

    for(size_t i = posIns; i < vector->ce; i++)
        vector->vec[i + 1] = vector->vec[i];

    *(vector->vec[posIns]) = *(elemento);
    vector->ce++;
    */
    return OK;
}
