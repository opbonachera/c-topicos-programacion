#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Vector.h"


#define CAP_INI 10 // elementos
#define FACTOR_INCR 1.5
#define FACTOR_DECR 0.5


bool redimensionarVec(Vector* v, size_t nuevaCap);
void ordenarBurbujeo(Vector* v, Cmp cmp);
void ordenarSeleccion(Vector* v, Cmp cmp);
void ordenarInsercion(Vector* v, Cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);
void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp);


bool vectorCrear(Vector* v, size_t tamElem)
{
    v->ce = 0;
    v->cap = CAP_INI;
    v->tamElem = tamElem;
    v->vec = malloc(CAP_INI * tamElem);

    if(v->vec == NULL)
    {
        return false;
    }

    return true;
}


int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVec(v, v->cap * FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = v->vec;
    while(posIns <= ult && cmp(elem, posIns) > 0)
    {
        posIns += v->tamElem;
    }

    // 1 - Elem del vec mayor. Sí inserto
    // 2 - Elem del vec igual (Duplicado). No inserto
    // 3 - Elem mayor a todos los del vector. Sí inserto

    if(posIns <= ult && cmp(elem, posIns) == 0)
        return DUPLICADO;

    for(void* i = ult; i >= posIns; i -= v->tamElem)
    {
        memcpy(i + v->tamElem, i, v->tamElem); // *(i + 1) = *i;
    }

    memcpy(posIns, elem, v->tamElem);

    v->ce++;

    return TODO_OK;
}


int vectorInsertarAlFinal(Vector* v, const void* elem)
{
    if(v->ce == v->cap)
    {
        if(!redimensionarVec(v, v->cap * FACTOR_INCR))
        {
            return SIN_MEM;
        }
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = ult + v->tamElem;
    memcpy(posIns, elem, v->tamElem);
    v->ce++;

    return TODO_OK;  
}


bool vectorOrdEliminarElem(Vector* v, void* elem, Cmp cmp)
{
    if(v->ce == 0)
    {
        return false;
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posElim = v->vec;
    while(posElim <= ult && cmp(elem, posElim) > 0)
    {
        posElim += v->tamElem;
    }

    // 1 - elem = posElim. Lo elimino.
    // 2 - elem < posElim. No existe.
    // 3 - elem > todos. No existe.

    if(posElim > ult || cmp(elem, posElim) < 0)
    {
        return false;
    }

    memcpy(elem, posElim, v->tamElem); // Sin sentido para ints. Sí para estructuras.

    for(void* i = posElim; i < ult; i += v->tamElem)
    {
        memcpy(i, i + v->tamElem, v->tamElem);
    }

    v->ce--;

    if(v->cap * FACTOR_DECR >= CAP_INI && v->ce * 4 <= v->cap)
    {
        redimensionarVec(v, v->cap * FACTOR_DECR);
    }

    return true;
}


void vectorOrdenar(Vector* v, Cmp cmp, int metodo)
{
    switch(metodo)
    {
        case BURBUJEO:
            ordenarBurbujeo(v, cmp);
            return;

        case SELECCION:
            ordenarSeleccion(v, cmp);
            return;

        case INSERCION:
            ordenarInsercion(v, cmp);
            return;
    }
}


void ordenarBurbujeo(Vector* v, Cmp cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    void* limJ = ult - v->tamElem;
    for(int i = 1; i < v->ce; i++, limJ -= v->tamElem)
    {
        for(void* j = v->vec; j <= limJ; j += v->tamElem)
        {
            if(cmp(j, j + v->tamElem) > 0)
            {
                intercambiar(j, j + v->tamElem, v->tamElem);
            }
        }
    }
}


void ordenarSeleccion(Vector* v, Cmp cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* m;

    for(void* i = v->vec; i < ult; i += v->tamElem)
    {
        m = buscarMenor(i, ult, v->tamElem, cmp);
        intercambiar(m, i, v->tamElem);
    }
}


void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
    void* m = ini;

    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, m) < 0)
        {
            m = j;
        }
    }

    return m;
}


void ordenarInsercion(Vector* v, Cmp cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* elemAIns = malloc(v->tamElem);
    void* j;

    for(void* i = v->vec + v->tamElem; i <= ult; i += v->tamElem)
    {
        memcpy(elemAIns, i, v->tamElem);
        j = i - v->tamElem;
        
        while(j >= v->vec && cmp(elemAIns, j) < 0)
        {
            memcpy(j + v->tamElem, j, v->tamElem);
            j -= v->tamElem;
        }

        memcpy(j + v->tamElem, elemAIns, v->tamElem);
    }

    free(elemAIns);
}


void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);
    memcpy(aTemp, a, tamElem); // aTemp = *a;
    memcpy(a, b, tamElem); // *a = *b;
    memcpy(b, aTemp, tamElem); // *b = aTemp;
    free(aTemp);
}


void vectorVaciar(Vector* v)
{
    v->ce = 0;
    redimensionarVec(v, CAP_INI);
}


void vectorEliminar(Vector* v)
{
    free(v->vec);
    v->vec = NULL;
    v->cap = 0;
    v->ce = 0;
    v->tamElem = 0;
}


bool redimensionarVec(Vector* v, size_t nuevaCap)
{
    int* nVec = realloc(v->vec, nuevaCap * v->tamElem);

    if(!nVec)
    {
        return false;
    }

    printf("Redimension de %lu a %lu\n", v->cap, nuevaCap);

    v->vec = nVec;
    v->cap = nuevaCap;

    return true;
}


void vectorMostrar(Vector* v, ImprimirElem imprimirElem)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* i = v->vec;
    for(int pos = 0; i <= ult; pos++, i += v->tamElem)
    {
        imprimirElem(pos, i);// printf("[%d]: %d\n", pos, *i);
    }
}


void cargarVectorRandom(Vector* v, size_t ce)
{
    srand(time(NULL));

    for(int i = 0; i < ce; i++)
    {
        vectorInsertarAlFinal(v, rand() % 100);
    }
}
