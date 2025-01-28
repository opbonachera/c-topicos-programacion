#include "vector.h"

int vectorCrear(Vector* vec, size_t tamElem)
{
    vec->ce = 0;
    vec->cap = 10;
    vec->vec = malloc(tamElem * vec->cap);

    if(!vec->vec)
    {
        return ERROR_RESERVA_MEMORIA;
    }

    return OK;
}

void vectorDestruir(Vector* vec)
{
    free(vec->vec);
    vec->cap=0;
    vec->ce=0;
}

void vectorVaciar(Vector* vector)
{
    vec->ce = 0;
}

void vectorGrabar(Vector* v, const char* nombreArch)
{
    FILE* archivo = fopen(nombreArch, "wb");

    if(!archivo)
    {
        printf("Error al abrir el archivo");
        return;
    }

    fwrite(&v->vec, sizeof(v->vec), 1, archivo);
    fclose(archivo);
}

int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp, Actualizar actualizar)
{
    if(!redimensionarVec(v, v->cap * FACTOR_INCR))
    {
        return SIN_MEM;
    }

    void* ult = vector->v + (v->tamElem * (v->ce - 1));
    void* posIns = vector->v;

    while(posIns <= ult && cmp(elem, posIns)>0)
    {
        posIns+=vector->tamElem;
    }

    if(cmp(elem, posIns) == 0)
    {
        printf("Elemento duplicado\n");
        return;
    }

    for(void* i = ult; i >= posIns; i-= vector->tamElem)
    {
        memcpy(i + vector->tamElem, i, vector->tamElem);
    }

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return OK;
}

int vectorOrdInsertarCDup(Vector* vector, const void* elem, Cmp cmp);
void vectorRecorrer(const Vector* v, Accion accion, void* datosAccion);

int vectorCargarDeArchivo(const char* nombreArch, Vector* vector, size_t tamElem)
{
    FILE* archivo = fopen(nombreArch, "rb");

    if(!archivo)
    {
        return;
    }

    fseek(archivo, 0L, SEEK_END);
    int cantReg = ftell(archivo) / tamElem;

    vector->ce = cantReg;
    vector->cap = 10;
    vector->tamElem = tamElem;

    vector->vec = malloc(cantReg * tamElem);
    if(!vector->vec)
    {
        printf("Error al reservar memoria para el vector. \n");
    }

    fread(&vector->vec, sizeof(vector->vec), 1, archivo);
}

int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp)

int vectorOrdEliminarDuplicados(Vector* v, Cmp cmp, Actualizar actualizar);
int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(v->ce == v->cap)
    {
        redimensionarVector(vector, 10);
        return;
    }

    void* ult = vector->vec + ((vector->ce - 1) * vector->tamElem);
    void* posIns += vector->tamElem;

    *posIns = *elem;

    return OK;
}

int vectorCantidadElementos(const Vector* v);
bool vectorVacio(const Vector* v);

void vectorItCrear(VectorIterador* it, Vector* vector);
void* vectorItPrimero(VectorIterador* it);
void* vectorItSiguiente(VectorIterador* it);
bool vectorItFin(VectorIterador* it);