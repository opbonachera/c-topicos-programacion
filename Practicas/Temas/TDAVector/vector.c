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
    void* nPuntero = realloc(vec->v, factorRedimension * vec->tamElem);

    if(!nPuntero)
    {
        printf("No se pudo redimensionar el vector. \n");
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    vec->v = nPuntero;
    vec->cap = factorRedimension;

    return OK;
}

void vectorAsignarEnterosOrdenados(Vector* vec)
{
    int* ult = vec->v + (vec->tamElem * vec->ce);
    for(int* p = (int*)vec->v, i=1; p <= ult; i++, p++)
    {
        *p = i;
    }
}

void vectorAsignarEnterosAleatorio(Vector* vec, int min, int max)
{
    int* ult = vec->v + (vec->tamElem * vec->ce);
    srand(time(NULL));
    for(int* p = vec->v; p <= ult; p++)
    {
        *p = (rand() % (max - min + 1)) + min;
    }
}

void vectorImprimirContenido(Vector* vec)
{
    int* ult = vec->v + (vec->tamElem * vec->ce);
    for(int* p = vec->v; p <= ult; p++)
    {
        printf("[%d]", *p);
    }
    printf("\n");
}

void vectorImprimirDetalles(Vector* vec)
{
    printf("Imprimiendo detalles del vector...\n");
    printf("ce: -> [%d]\n", vec->ce);
    printf("cap: -> [%d]\n", vec->cap);
    printf("tamElem: -> [%d] bytes \n", vec->tamElem);
}

void vectorOrdenar(Vector* vec, int metodo)
{
    switch(metodo)
    {
        case BURBUJEO:
            vectorOrdenarBurbujeo(vec, cmpEntero);
            break;
    }
}

void vectorOrdenarBurbujeo(Vector* vec, Cmp cmp)
{
    void* anteUlt = (vec->v + (vec->ce - 1) * vec->tamElem) - vec->tamElem;

    for(int i = 1; i < vec->ce; i++, anteUlt -= vec->tamElem)
    {
        for(void* j = vec->v; j <= anteUlt; j += vec->tamElem)
        {
            if(cmp(j, j + vec->tamElem) > 0)
            {
                intercambiar(j, j + vec->tamElem, vec->tamElem);
            }
        }
    }
}

void vectorOrdenarInsercion(Vector* vector);
void vectorOrdenarSeleccion(Vector* vector);

void vectorOrdAgregarElemento(Vector* vec, void* elemento, Cmp* cmp)
{
    //
}

void intercambiar(void* e1, void* e2, int tamElem)
{
    void* temp = malloc(tamElem);

    memcpy(temp, e1, tamElem);
    memcpy(e1, e2, tamElem);
    memcpy(e2, temp, tamElem);

    free(temp);
}

int cmpEntero(void* e1, void* e2)
{
    int* elemento1 = e1;
    int* elemento2 = e2;

    return *elemento1 - *elemento2;
}
