#include "VectorGenerico.h"


int inicializarVector(VectorGenerico* vector)
{
    vector->cap = CANT_ELEMENTOS + 5;
    vector->ce  = CANT_ELEMENTOS;
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
    /*int* posicion = (int*)vector->vec;
    for(size_t i=0; i < vector->ce; i++)
    {
        *posicion = i + 1;
        posicion++;
    }*/

    vector->vec[0] = 6;
    vector->vec[1] = 4;
    vector->vec[2] = 1;
    vector->vec[3] = 5;
    vector->vec[4] = 2;
    vector->vec[5] = 3;

    return OK;
}

int imprimirVectorEnteros(VectorGenerico* vector)
{
    int* posicion = (int*)vector->vec;
    for(size_t i = 0; i < vector->ce; i++)
    {
        printf("%d ", *posicion);
        posicion++;
    }

    printf("\n");
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

int aniadirElementoFinal(VectorGenerico* vector, void* elemento)
{
    if (vector->ce == vector->cap)
        redimensionarVector(vector);



    void* destino = (char*)vector->vec + vector->ce * vector->tamElemento; // Ultima posicion en el vector generico
    memcpy(destino, elemento, vector->tamElemento);
    vector->ce++;

    return OK;
}


int insertarEnteroOrdenado(VectorGenerico* vector, int* elemento)
{
    int posIns = 0;

    if(vector->ce == vector->cap)
        redimensionarVector(vector);

    while(posIns < vector->ce && *elemento > vector->vec[posIns])
        posIns++;

    for(int i = vector->ce-1; i>=posIns; i++)
        vector->vec[i+1] = vector->vec[i];

    vector->vec[posIns] = *elemento;
    vector->ce++;

    printf("Se aniadio el elemento %d \n", *elemento);
    return OK;
}


