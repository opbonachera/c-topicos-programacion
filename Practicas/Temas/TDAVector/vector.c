#include "vector.h"
#include "constantes.h"

int vectorInicializar(Vector* vec, int tamElem, int ce)
{
    vec->v = malloc(tamElem * CAP_INICIAL);

    if(!vec->v)
    {
        printf("No se pudo reservar memoria para la creacion del vector.\n");
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    vec->ce = ce;
    vec->tamElem = tamElem;
    vec->cap = CAP_INICIAL;

    return OK;
}

void vectorVaciar(Vector* vec)
{
    free(vec->v);
    vec->ce = 0;
}

void vectorDestruir(Vector* vec)
{
    free(vec->v);
    vec->ce = 0;
    vec->cap = 0;
    vec->tamElem = 0;
}

int vectorRedimensionar(Vector* vec, int factorRedimension)
{
    void* nPuntero = realloc(vec->v, factorRedimension * tamElem);

    if(!nPuntero)
    {
        printf("No se pudo redimensionar el vector. \n");
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    vec->v = nPuntero;
    vec->cap = factorRedimension;

    return OK;
}
