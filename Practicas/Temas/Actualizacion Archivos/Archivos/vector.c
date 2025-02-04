#include "vector.h"

int inicializarVector(Vector* vector, size_t ce, size_t tamElemento)
{
    vector->ce = ce;
    vector->tamElemento = tamElemento;
    vector->cap = CAPACIDAD_INICIAL;

    vector->v = malloc(CAPACIDAD_INICIAL * tamElemento);
    if(!vector->v)
    {
        return ERROR_RESERVA_MEMORIA;
    }

    return OK;
}

int destruirVector(Vector* vector)
{
    free(vector->v);
    vector->ce = 0;
    vector->cap = 0;
    vector->tamElemento = 0;
    return OK;
}

int redimensionarVector(Vector* vector, size_t nuevaCap);

int mostrarVector(Vector* vector, Impr imprimirElemento)
{
    void* ult = vector->v + (vector->ce - 1) * vector->tamElemento;

    for(void* p = vector->v; p<=ult; p+= vector->tamElemento)
    {
        imprimirElemento(p);
    }

    return OK;
}

int vectorCrearDeArchivo(Vector* v, const char* nomArch, size_t tamElem)
{
    FILE* archivo = fopen(nomArch, "rb");
    printf("hola");
    if(!archivo)
    {
        printf("No pude abrir el archivo");
        return ERROR_APERTURA_ARCHIVO;
    }

    fseek(archivo, 0L, SEEK_END);
    int cantidadRegistros = ftell(archivo) / tamElem;

    v->v = malloc(cantidadRegistros * tamElem);

    if(!v->v)
    {
        return ERROR_RESERVA_MEMORIA;
    }

    rewind(archivo);

    fread(v->v, tamElem, cantidadRegistros, archivo);

    v->ce = cantidadRegistros;
    v->cap = cantidadRegistros;
    v->tamElemento = tamElem;

    fclose(archivo);
    return OK;
}

int grabarVector(Vector* vector, const char* nomArch)
{
     FILE* arch = fopen(nomArch, "wb");

    if(!arch)
    {
        return false;
    }

    fwrite(vector->v, vector->tamElemento, vector->ce, arch);

    fclose(arch);

    return true;
}
int ordenarVectorInsercion(Vector* vector, Cmp cmp)
{
    void* ult = vector->v + (vector->ce - 1) * vector->tamElemento;
    void* elemAIns = malloc(vector->tamElemento);
    void* j;

    for(void* i = vector->v; i<=ult; i+= vector->tamElemento)
    {
        memcpy(elemAIns, i, vector->tamElemento);
        j = i - vector->tamElemento;

        while(j>=vector->v && cmp(elemAIns, j)<0)
        {
            memcpy(j+vector->tamElemento, j, vector->tamElemento);
            j-= vector->tamElemento;
        }

        memcpy(j + vector->tamElemento, elemAIns, vector->tamElemento);
    }

    free(elemAIns);
    return OK;
}

void busquedaBinaria(Vector* vector, int limiteInferior, int limiteSuperior, void* elemento, Cmp cmp, int* posEnc)
{
    if(limiteSuperior<limiteInferior)
    {
        *posEnc = -1;
        return;
    }

    int indiceMedio = (limiteInferior + limiteSuperior) / 2;
    void* elementoMedio = vector->v + (indiceMedio * vector->tamElemento);

    if(!cmp(elemento, elementoMedio))
    {
        *posEnc = indiceMedio;
        return;
    }

    if(cmp(elemento, elementoMedio)<0)
        return busquedaBinaria(vector, limiteInferior, indiceMedio - 1, elemento, cmp, posEnc);
    if(cmp(elemento, elementoMedio)>0)
        return busquedaBinaria(vector, indiceMedio + 1, limiteSuperior, elemento, cmp, posEnc);
}
