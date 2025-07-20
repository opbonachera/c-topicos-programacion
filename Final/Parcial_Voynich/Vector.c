#include "Vector.h"

void vectorInicializar(tVector* v, size_t tamElem)
{
    v->vec = malloc( CAP_INI * tamElem);
    if(!v->vec)
        return;

    v->ce=0;
    v->cap=CAP_INI;
    v->tamElem=tamElem;

    return;
}

void vectorDestruir(tVector* v)
{
    free(v->vec);
    v->ce=0;
    v->cap=0;
    v->tamElem=0;
}

int  vectorInsertarElemOrdenado(tVector* v, void* dato, int(*cmp)(const void*, const void*))
{
    if(v->ce==v->cap)
        return 0; // TODO: REDIMENSIONAR

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = v->vec;

    while(posIns<=ult && cmp(dato, posIns)>0)
        posIns+=v->tamElem;

    if(posIns <= ult && cmp(dato, posIns) == 0)
        return 0; // ELEMENTO DUPLICADO

    for(void* i=ult; i>=posIns; i-=v->tamElem)
    {
        memcpy(i + v->tamElem, i, v->tamElem);
    }

    memcpy(posIns, dato, v->tamElem);
    v->ce++;
    return OK;
}

void vectorRecorrer(tVector* v, void* params, void(*accion)(void*, void*))
{
    char* p = v->vec;
    for (int i = 0; i < v->ce; i++)
    {
        accion(p, params);
        p += v->tamElem;
    }

}
int vectorBusquedaBinaria(tVector* v, void* dato, int(*cmp)(const void*, const void*))
{
    int low = 0, high = v->ce - 1, currentIndex;

    while(low <= high)
    {
        currentIndex = (high + low) / 2;
        void* currentElem = (char*)v->vec + (currentIndex * v->tamElem);

        int comp = cmp(dato, currentElem);
        if(comp == 0)
            return currentIndex;
        else if(comp < 0)
            high = currentIndex - 1;
        else
            low = currentIndex + 1;
    }

    return -1;
}

void* obtenerElementoEnIndiceVector(tVector* v, int indice)
{
    return (v->vec + indice * v->tamElem);
}
