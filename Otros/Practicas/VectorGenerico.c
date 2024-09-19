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

int insertarElementoOrdenado(VectorGenerico* vector, void* elemento)
{
    int posIns = 0;
    int* elem = (int*)elemento; // Cast the void* to the appropriate type (int in this case)

    if(vector->ce == vector->cap)
        redimensionarVector(vector);

    // Assuming vector->vec contains integers, cast the elements for comparison
    while(posIns < vector->ce && *elem > *((int*)vector->vec + posIns))
    {
        posIns++;
    }

    // Shift elements to the right
    for(int i = vector->ce - 1; i >= posIns; i--)
    {
        ((int*)vector->vec)[i + 1] = ((int*)vector->vec)[i];
    }

    // Insert the element
    ((int*)vector->vec)[posIns] = *elem;
    vector->ce++;

    return 0; // Assuming 0 means success
}
