#include "vector.h"

void vectorInicializar(tVector* v, size_t tamElem)
{
    v->vec = malloc(tamElem * CAP_INI);
    if(!v->vec)
        return;

    v->ce=0;
    v->cap=CAP_INI;
    v->tamElem=tamElem;
}

int  vectorInsEnOrden(tVector* v, void* elem, int(*cmp)(const void*, const void*))
{
    if(v->ce==v->cap)
        return 0;//redimensionarVector();

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = v->vec;

    while( posIns<=ult && cmp(elem, posIns) > 0)
        posIns+=v->tamElem;

    if(posIns <= ult && cmp(elem,posIns)==0)
        return 0; // ELEMENTO DUPLICADO

    for(void* i=ult; i>=posIns; i-=v->tamElem)
    {
        memcpy(i+v->tamElem, i, v->tamElem);
    }

    memcpy(posIns, elem, v->tamElem);
    v->ce++;

    return 0;
}

void vectorDestruir(tVector* v)
{
    free(v->vec);
    v->ce=0;
    v->ce=0;
    v->tamElem=0;
}

void vectorVaciar(tVector* v)
{
    v->ce=0;
    v->vec=NULL;
    v->vec=malloc(v->tamElem * CAP_INI);
    if(!v->vec)
        return;
}

void vectorRecorrer(tVector* v, void* params, void(*accion)(void*, void*))
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    for(void* i=v->vec; i<=ult; i+= v->tamElem)
    {
        accion(i, params);
    }

}

int vectorVacio(tVector* v)
{
    return !v->ce;
}
