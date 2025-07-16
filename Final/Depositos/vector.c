#include "vector.h"

void inicializarVector(tVector* v, size_t tamElem)
{
    v->vec = malloc(CAP_INI * tamElem);

    if(!v->vec)
        return;

    v->cap = CAP_INI;
    v->ce = 0;
    v->tamElem = tamElem;
}

int  insertarElemOrdenadoVector(tVector* v, void* elem, Cmp cmp)
{
    if(v->ce == v->cap)
        return 0; // VECTOR LLENO. HAY QUE REDIMESIONAR

    // buscar la posicion de insercion
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = v->vec;

    while(posIns <= ult && cmp(elem, posIns)>0)
        posIns+=v->tamElem;

    if( posIns<=ult && cmp(elem,posIns) == 0)
        return 0; // ELEMENTO DUPLICADO

    for(void* p=ult; p>=posIns; p-=v->tamElem)
    {
        memcpy(p + v->tamElem, p, v->tamElem);
    }

    memcpy(posIns, elem, v->tamElem);
    v->ce++;


    return 1;
}

int  destruirVector(tVector* v)
{
    v->cap=0;
    v->ce=0;
    v->tamElem=0;
    free(v->vec);
    return 1;
}

int obtenerIndiceElemVector(tVector* v, void* elem, Cmp cmp)
{
    for(int i = 0; i < v->ce; i++)
    {
        void* actual = (void*)v->vec + i * v->tamElem;
        if(cmp(actual, elem) == 0)
            return i;
    }
    return -1;
}

int  recorrerVector(tVector* v, void* param, Accion accion)
{
    void* ult = v->vec + (v->ce-1*v->tamElem);
    for(void* i=v->vec; i<=ult; i+=v->tamElem)
    {
        accion(i, param);
    }
    return 1;
}

