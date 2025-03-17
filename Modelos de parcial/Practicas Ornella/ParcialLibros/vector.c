#include "vector.h"
#include "estructuras.h"
#include "archivos.h"

int inicializarVector(Vector* vector, size_t tamElemento, size_t ce);

int vectorCrearDeArchivo(Vector* vector, const char* nomArch, size_t tamElemento)
{
    FILE* archivo = fopen(nomArch, "rb");

    if(!archivo)
    {
        return ERROR_LECTURA_ARCHIVO;
    }

    size_t cantReg;

    fseek(archivo,0L,SEEK_END);
    cantReg = ftell(archivo) / tamElemento;
    rewind(archivo);

    vector->v = malloc(tamElemento * cantReg);

    if(!vector->v)
    {
        return ERROR_RESERVA_MEMORIA;
    }

    fread(vector->v, cantReg, tamElemento, archivo);

    vector->ce = cantReg;
    vector->cap = (size_t)(cantReg * 1.5);
    vector->tamElemento = tamElemento;

    imprimirDetallesVector(vector);

    fclose(archivo);
    return OK;
}

void imprimirDetallesVector(Vector* vector)
{
    printf("Detalles del vector");
    printf("%d \n", vector->ce);
    printf("%d \n", vector->cap);
    printf("%d \n", vector->tamElemento);
    printf("\n");
}

void ordenarVector(Vector* v, Comparar cmp)
{
    void* ult = v->v + (v->ce - 1) * v->tamElemento;
    void* elemAIns = malloc(v->tamElemento);
    void* j;

    for(void* i = v->v + v->tamElemento; i <= ult; i += v->tamElemento)
    {
        memcpy(elemAIns, i, v->tamElemento);
        j = i - v->tamElemento;

        // Change "< 0" to "<= 0" to allow duplicates to remain in order
        while(j >= v->v && cmp(elemAIns, j) < 0)
        {
            memcpy(j + v->tamElemento, j, v->tamElemento);
            j -= v->tamElemento;
        }

        memcpy(j + v->tamElemento, elemAIns, v->tamElemento);
    }

    free(elemAIns);
}

int vectorGrabar(const Vector* v, const nomArch)
{
    FILE* archivo = fopen(nomArch, "wb");

    if(!archivo)
    {
        return ERROR_LECTURA_ARCHIVO;
    }

    imprimirDetallesVector(v);
    fwrite(v->v, v->tamElemento, v->ce, archivo);

    fclose(archivo);

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



int redimensionarVector(Vector* vector, int nuevaCap);
