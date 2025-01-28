#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

int calcular(int a, int b, int(*oper)(int,int))
{
    int r;
    r = oper(a,b);
    return r;
}

int printVector(const int *p, size_t ce)
{
    for(int i=0; i<ce;i++)
    {
        printf("%d ", *p);
        p++;
    }
    return 0;
}

int vectorCrear(tVector *vec, size_t tamElem)
{
    // La unica forma de conocer el tamaño de los elementos es recibiendolo por parametro
    int cant = 5;
    vec->tamElem = sizeof(tamElem);
    vec->vec = malloc(cant * vec->tamElem);

    if(!vec->vec)
        return 0;

    vec->ce = 0;
    vec->cap = cant;
    vec->tamElem;


    return 1;
}

void destruirVector(tVector * vec)
{
    free(vec->vec);
}

int  vectorInsertarAlfinal(tVector *vec, const void *elem)
{
    // Verificar si hay espacio para insertar el elemento nuevo
    if(vec->ce == vec->cap)
    {
        if(!_ampliarVector(vec))
        {
            printf("SIN MEMORIA\n");
            return 10; // Codigo de error
        }
    }
    // Ampliar la capacidad

}

int _ampliarVector(tVector* vec)
{
    size_t nuevaCap = vec->cap * FACTOR_INCREMENTO;
    void *nuevoVec = realloc(vec->vec, nuevaCap * sizeof(vec->tamElem));

    if(!nuevoVec)
        return 10;

    vec->vec = nuevoVec;
    vec->cap = nuevaCap;

    // Buscar la posicion a insertar
    void * posInsercion = vec->vec + vec->ce * vec->tamElem;
    // Instertamos el elemeno
    //memcpy(posInsercion, elem, vec->tamElem); // Para insertar SI O SI debemos usar un memcpy

    vec->ce++;

    return 1; // El 1 representaría un true
}

void vectorMostrar(const tVector *vec)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;

    for(void *i = vec->vec; i<fin; i+=vec->tamElem)
    {
        //printf();
    }
}

void vectorOrdenarSeleccion(tVector *vec, cmpElemento cmp)
{
    void* ult = vec->vec + vec->ce * vec->tamElem;
    void* menor;

    for(void *i = vec->vec; i<ult; i+= vec->tamElem)
    {
        m = _buscarMenor(i,ult, cmp);
        _intercambiarElem(i,m,vec->tamElem);
    }
}
