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

int vectorInsElemOrdenado(tVector* v, void* elem, Cmp cmp)
{
    if(v->ce == v->cap)
        vectorRedimensionar(v, CAP_INI * 2);

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posIns = v->vec;

    while(posIns<=ult && cmp(elem, posIns)>0)
        posIns+=v->tamElem;

    if(posIns<=ult && cmp(elem,posIns)==0)
        return ERROR_ELEMENTO_DUPLICADO;

    for(void* i=ult; i>=posIns; i-=v->tamElem)
    {
        memcpy(i+v->tamElem, i, v->tamElem);
    }

    memcpy(posIns, elem, v->tamElem);

    v->ce++;

    return OK;
}

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

    void* posElim = v->vec;
    void* ult = v->vec + (v->ce - 1) * v->tamElem;

    while(posElim < ult)
    {
        void* elemSig = posElim + v->tamElem;

        if(cmp(posElim, elemSig) == 0)
        {
            size_t bytes_restantes = (v->vec + v->ce * v->tamElem) - elemSig - v->tamElem;
            memmove(elemSig, elemSig + v->tamElem, bytes_restantes);
            v->ce--;
        }
        else
        {
            posElim += v->tamElem;
        }

        ult = v->vec + (v->ce - 1) * v->tamElem;
    }

    return OK;
}


int vectorBuscar(tVector* v, Cmp cmp, void* elem)
{
    int limSup = v->ce - 1, limInf=0, indActual;

    while(limInf<=limSup)
    {
        indActual = (limInf + limSup) / 2;
        void* elemActual = v->vec + (v->tamElem * indActual);

        if(cmp(elem, elemActual)==0)
        {
            memcpy(elem, elemActual, v->tamElem);
            return indActual;
        }

        if(cmp(elem, elemActual)>0)
            limInf = indActual + 1;

        if(cmp(elem, elemActual)<0)
            limSup = indActual - 1;

    }

    return -1;
}

int vectorEliminarElemOrdenado(tVector* v, void* elem, Cmp cmp)
{
    if(v->ce==0)
        return ERROR_VECTOR_VACIO;

    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    void* posElim = v->vec;

    while(posElim<=ult && cmp(elem, posElim)>0)
        posElim+=v->tamElem;

    if(posElim>ult || cmp(posElim, elem)!=0)
        return ERROR;

    for(void* i=posElim; i<=ult; i+=v->tamElem)
    {
        memcpy(i, i+v->tamElem, v->tamElem);
    }

    v->ce--;

    return OK;
}

void vectorOrdenar(tVector* v, Cmp cmp, int metodo)
{
    switch(metodo)
    {
        case BURBUJEO:
            vectorOrdenarBurbujeo(v, cmp);
            break;
        case INSERCION:
            vectorOrdenarInsercion(v, cmp);
            break;
        case QSORT:
            vectorOrdenarQsort(v, 0, v->ce, cmp);
            break;
    }
}

void vectorOrdenarQsort(tVector* v, int inicio, int fin, Cmp cmp)
{
    // CASO BASE
    if(inicio>=fin)
        return;

    void* pivote = v->vec + (fin * v->tamElem);
    int i = inicio - 1;

    for(int j=inicio; j<fin; j++)
    {
        void* elemActual = v->vec + (v->tamElem * j);
        if(cmp(elemActual, pivote) <= 0)
        {
            i++;
            intercambiar(v->vec + (i * v->tamElem), elemActual, v->tamElem);
        }
    }

    void* posFinalPivote = v->vec + (i + 1) * v->tamElem;
    intercambiar(posFinalPivote, pivote, v->tamElem);

    vectorOrdenarQsort(v, inicio, i, cmp);
    vectorOrdenarQsort(v, i + 2, fin, cmp);
}

void intercambiar(void* e1, void* e2, size_t tamElem)
{
    void* temp = malloc(tamElem);
    if(!temp)
        return;

    memcpy(temp, e1, tamElem);
    memcpy(e1, e2, tamElem);
    memcpy(e2, temp, tamElem);

    free(temp);
}
void vectorOrdenarBurbujeo(tVector* v, Cmp cmp)
{

}
void vectorOrdenarInsercion(tVector* v, Cmp cmp)
                           {

                           }

void vectorDeArchivoBin(tVector* v, size_t tamElem, const char* nombreArchBin)
{
    FILE* f = fopen(nombreArchBin, "rb");
    if(!f)
        return;

    fseek(f, 0, SEEK_END);
    int cantElem = ftell(f) / tamElem;

    v->ce = cantElem;
    v->cap = cantElem;
    v->vec = malloc(cantElem * tamElem);

    if(!v->vec)
        return;

    rewind(f);

    fread(v->vec, tamElem, cantElem, f);

    fclose(f);
}
