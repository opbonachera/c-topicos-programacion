#include "vector.h"

int inicializarVector(Vector* vector, size_t tamElem, size_t ce)
{
    vector->cap = CAP_VECTOR;
    vector->ce = ce;
    vector->v = malloc(vector->v, tamElem * vector->cap);

    if(!vector->v)
    {
        printf("Hubo un error al reservar memoria para el vector\n");
        return ERROR_RESERVA_MEMORIA;
    }

    return OK;
}

int vaciarVector(Vector* vector)
{
    vector->ce = 0;
    return OK;
}

int destruirVector(Vector* vector)
{
    vector->ce=0;
    vector->cap=0;
    vector->tamElem=0;
    free(vector->v);

    return OK;
}

int cargarVectorOrdenadoEnteros(Vector* vector)
{
    int* ult = vector->v + (vector->ce - 1) * vector->tamElem;

    for(int* p = vector->v, i = 1; p <= ult; p++, i++)
    {
        *p = i;
    }

    return OK;
}

int redimensionarVector(Vector* vector, size_t nuevaCap)
{
    void* nuevoVector = malloc(vector->v, nuevaCap * vector->tamElem);

    if(!nuevoVector)
    {
        printf("Hubo un error al redimensionar el vector.\n");
        return ERROR_RESERVA_MEMORIA;
    }

    vector->v = nuevoVector;
    vector->cap = nuevaCap; 

    return OK;
}

int mostrarVector(Vector* vector, Imprimir imprimirElemento)
{
    void* ult = vector->v + (vector->ce - 1) * vector->tamElem;
    for(void* p = vector->v; p <= ult; p += vector->tamElem)
    {
        imprimirElemento(p);
    }

    return OK;
}

int cargarVectorRandom(Vector* vector)
{

}

// ---- Insercion ----
int insertarElementoAlFinal(Vector* vector, void* elemento)
{
    if(vector->ce == vector->cap)
    {
        redimensionarVector(vector, FACTOR_INCREMENTO);
    }

    void* posIns = vector->v + (vector->ce * vector->tamElem);

    memcpy(elemento, posIns, vector->tamElem);

    return OK;
}

int insertarElementoOrdenado(Vector* vector, Comparar cmp, void* elemento)
{
    if(vector->ce == vector->cap)
    {
        redimensionarVector(vector, FACTOR_INCREMENTO);
    }

    void* ult = vector->v + (vector->ce - 1 * vector->tamElem); 
    void* posIns = vector->v;

    while(posIns < ult && cmp(elemento, posIns)<0)
    {
        posIns+=vector->tamElem;
    }

    if(posIns <= ult && cmp(elemento, posIns) == 0)
    {
        return ELEMENTO_DUPLICADO;
    }

    for(void* p = ult; p >= posIns; p -= vector->tamElem)
    {
        memcpy(p + vector->tamElem, p, vector->tamElem);
    }

    memcpy(posIns, elemento, vector->tamElem);

    vector->ce++;

    return OK;
}

int insertarElementoEnPosicion(Vector* vector, Comparar cmp, void* elemento, int posIns)
{
    if(vector->ce == vector->cap)
    {
        redimensionarVector(vector, FACTOR_INCREMENTO);
    }

    if(posIns < vector->ce)
    {
        return POSICION_INEXISTENTE;
    }
    
    void* ult = vector->v + (vector->ce - 1) * vector->tamElem;
    void* p = vector->v;

    while(p <= ult && cmp(elemento, p) != 0)
    {
        p += vector->tamElem;
    }

    if(!cmp(elemento,posIns))
    {
        return ELEMENTO_DUPLICADO;
    }

    for(void* p = ult; p>=posIns; p += vector->tamElem)
    {
        memcpy(p + vector->tamElem, p, vector->tamElem);
    }

    memcpy(posIns, elemento, vector->tamElem);

    return OK;
}

