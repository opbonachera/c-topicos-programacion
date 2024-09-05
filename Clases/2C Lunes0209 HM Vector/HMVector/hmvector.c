#include "hmvector.h"

int crearVector(Vector* v)
{
    v->vec = malloc(sizeof(int) * TAM);

    if(!v->vec)
        return ERROR_RESERVA_MEMORIA;

    v->cap = TAM;
    v->ce = 0;

    printf("--- Vector creado correctamente --- \n");

    return OK;
}

int destruirVector(Vector* v)
{
    free(v->vec);
    v->ce=0;
    v->cap=0;

    return OK;
}

int vaciarVector(Vector* v)
{
    v->vec = malloc(sizeof(int) * TAM);
    v->ce = 0;
    return OK;
}

int inicializarValores(Vector* v)
{
    int* ptr = v->vec;
    for(int i=1; i<5; i++)
    {
        *ptr = i;
        ptr++;
        v->ce++;
    }
    return OK;
}

int imprimirVector(Vector* v)
{
    printf("Cantidad de elementos: %d\n", v->ce);
    printf("Cantidad de lugares disponibles: %d\n", v->cap - v->ce);

    int* ptr = v->vec;
    for(int i=0; i<v->ce; i++)
    {
        printf("Posicion: (%d) - Elemento: (%d)\n", i, *ptr);
        ptr++;
    }
    return OK;
}

int redimensionarVector(Vector* v)
{
    int* nuevoVector = realloc(v->vec, sizeof(int) * 15);

    if(!nuevoVector)
        return ERROR_RESERVA_MEMORIA;

    v->cap = 15;

    return OK;
}

int insertarElementoOrdenado(Vector* v, int elemento)
{
    int posIns = 0;

    if(v->ce == v->cap)
        redimensionarVector(v);

    while(posIns < v->ce && elemento > v->vec[posIns])
        posIns++;

    for(int i = v->ce-1; i>=posIns; i++)
        v->vec[i+1] = v->vec[i];


    v->vec[posIns] = elemento;
    v->ce++;

    printf("Se agrego el elemento (%d) en la posicion (%d)\n", elemento, posIns);

    return OK;
}

int eliminarElementoOrdenado(Vector* v, int elemento)
{
    int posElim=0;
    while(posElim < v->ce && elemento > v->vec[posElim])
        posElim++;

    for (int i = posElim; i < v->ce - 1; i++)
        v->vec[i] = v->vec[i + 1];


    v->ce--;
    printf("Se elimino el elemento (%d) en la posicion (%d)\n", elemento, posElim);

    return OK;
}
