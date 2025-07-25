#include "vector.h"

void vectorRecorrer(tVector* v, Imp imprimir)
{
    void* ult = v->vec + v->tamElem * (v->ce - 1);
    for(void* i=v->vec; i<=ult; i+=v->tamElem)
    {
        imprimir(i);
    }
}
void vectorDeArchivo(tVector* v, const char* nomArch, int cap_ini, size_t tamElem)
{

    FILE* arch = fopen(nomArch, "rb");
    if(!arch)
    {
        printf("No se pudo abrir el archivo (%s)\n", nomArch);
        return;
    }

    fseek(arch, 0L, SEEK_END);
    int cantElem = ftell(arch) / tamElem;

    rewind(arch);

    v->vec = malloc(tamElem * cap_ini);
    if(!v->vec)
        return;

    fread(v->vec, tamElem, cantElem, arch);

    v->ce=cantElem;
    v->cap=cap_ini;
    v->tamElem=tamElem;

    return;
}

void vectorDestruir(tVector* v)
{
    free(v->vec);
    v->ce=0;
    v->tamElem=0;
    v->cap=0;
}

int vectorRedimensionar(tVector* v, size_t nuevaCap)
{
    void* aux = realloc(v->vec, nuevaCap * v->tamElem);
    if(!aux)
        return ERROR_MEMORIA;

    v->vec = aux;
    v->cap=nuevaCap;

    return OK;
}

int vectorGrabar(tVector* v, const char* nomArch)
{
    FILE* arch = fopen(nomArch, "wb");
    if(!arch)
    {
        printf("No se pudo abrir el archivo (%s)\n", nomArch);
        return ERROR_ARCHIVO;
    }

    fwrite(v->vec, v->tamElem, v->ce, arch);
    return OK;
}

int vectorOrdenar(tVector* v, int inicio, int fin, Cmp cmp)
{
    printf("Ordenando de %d a %d\n", inicio, fin);

    if(inicio >= fin)
        return OK;

    int i = inicio - 1;
    void* pivote = v->vec + fin * v->tamElem;
    char tempPivote[v->tamElem];
    memcpy(tempPivote, pivote, v->tamElem);

    for(int j = inicio; j < fin; j++)
    {
        void* elem = v->vec + j * v->tamElem;
        if(cmp(elem, tempPivote) < 0)
        {
            i++;
            intercambiar(v->vec + i * v->tamElem, elem, v->tamElem);
        }
    }

    intercambiar(v->vec + (i + 1) * v->tamElem, pivote, v->tamElem);

    vectorOrdenar(v, inicio, i, cmp);
    vectorOrdenar(v, i + 2, fin, cmp);

    return OK;
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

int vectorEliminarDuplicados(tVector* v, Cmp cmp, Actualizar actualizar)
{
    size_t i = 0;

    while(i < v->ce - 1)
    {
        void* elemActual = v->vec + i * v->tamElem;
        void* elemSig = v->vec + (i + 1) * v->tamElem;

        if(cmp(elemActual, elemSig) == 0)
        {
            if(actualizar)
                actualizar(elemActual, elemSig);

            size_t elemsRestantes = v->ce - (i + 2);
            memmove(elemSig, elemSig + v->tamElem, elemsRestantes * v->tamElem);
            v->ce--;
        }
        else
        {
            i++;
        }
    }

    return OK;
}

