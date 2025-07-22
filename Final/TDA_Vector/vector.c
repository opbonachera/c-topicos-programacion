#include "vector.h"

void vectorInicializar(tVector* v, size_t tamElem)
{
    v->vec=malloc(v->tamElem * CAP_INI);

    if(!v->vec)
        return;

    v->ce=0;
    v->cap=CAP_INI;
    v->tamElem=tamElem;
}

void vectorDestruir(tVector* v)
{
    free(v->vec);
    v->cap=0;
    v->tamElem=0;
    v->ce=0;
}

void vectorVaciar(tVector* v)
{
    v->ce=0;
    v->vec=malloc(v->tamElem * CAP_INI);
}

int  vectorRedimensionar(tVector* v, size_t nuevaCap)
{
    void* nVec = realloc(v->vec, v->tamElem * nuevaCap);
    if(!nVec)
        return 0;

    v->vec=nVec;
    v->cap=nuevaCap;

    return 1;
}


int vectorRecorrer(tVector* v, void* params, Accion accion)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    for(void* i=v->vec; i<=ult; i+=v->tamElem)
    {
        accion(i, params);
    }
    return OK;
}

int vectorInsElemOrdenado(tVector* v, void* elem, Cmp cmp);

int vectorInsAlFinal(tVector* v, void* elem)
{
    if(v->ce == v->cap)
    {
        if(!vectorRedimensionar(v, 100))
            return ERROR_MEMORIA;
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = ult + v->tamElem;

    memcpy(posIns, elem, v->tamElem);

    v->ce++;

    return OK;
}

int vectorEliminarDuplicados(tVector* v, Cmp cmp)
{
    if(v->ce == 0)
        return ERROR;

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posElim = v->vec;

    while(posElim < ult)
    {
        void* elemSig = posElim+=v->tamElem;

        if(cmp(posElim, elemSig) == 0)
        {
            memmove(posElim, elemSig, ult - (elemSig + v->tamElem));
            ult-=v->tamElem;
            v->ce--;
        }else
        {
            posElim+=v->tamElem;
        }
    }

    return OK;
}

int vectorBuscar(tVector* v, Cmp cmp, void* elem)
{
    int limSup = v->ce - 1, limInf=0, indActual;

    while(limInf<=limSup)
    {
        indActual = (limInf + limSup) / 2;
        void* elemActual = v->vec + (indActual) * v->tamElem;

        if(cmp(elem, elemActual) == 0)
            return indActual;

        else if(cmp(elem, elemActual) < 0)
            limSup = indActual - 1;

        else if( cmp(elem, elemActual) > 0 )
            limInf = indActual + 1;
    }

    return -1;
}

int vectorEliminarElemOrdenado(tVector* v, void* elem, Cmp cmp)
{
    if(v->ce==0)
        return ERROR_VECTOR_VACIO;

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posElim = v->vec;

    while( posElim<= ult && cmp(elem, posElim)<0 )
        posElim+=v->tamElem;

    if(posElim>ult || cmp(elem, posElim) != 0)
        return ERROR;

    memcpy(elem, posElim, v->tamElem);

    for(void* i=posElim; i<ult; i+=v->tamElem)
    {
        memcpy(i, i+v->tamElem, v->tamElem);
    }

    v->ce--;

    return OK;
}
