#include "ejercicios.h"

// Manejo de Vector Generico
int vectorCrear(VectorGenerico* v, size_t tamElem)
{
    v->cap = CAP_INI;
    v->ce = 0;
    v->tamElemento = tamElem;
    v->vec = malloc(tamElem * v->cap);

    if (v->vec == NULL)
    {
        printf("Error al reservar memoria. \n");
        return ERROR_RESERVA_MEMORIA;
    }

    return OK;
}

void vectorCargar(VectorGenerico* v, size_t ce)
{
    srand(time(NULL));

    for (int i = 0; i < ce; i++)
    {
        int randomValue = rand() % v->cap;
        vectorInsertarElementoFinal(v, &randomValue);
    }

    vectorImprimirDetalles(v);
}

void vectorInsertarElementoFinal(VectorGenerico* v, const void* elemento)
{

    if (v->cap == v->ce)
    {
        vectorRedimensionar(v, v->cap * 2);
    }

    void* posIns = (char*)v->vec + v->ce * v->tamElemento;
    memcpy(posIns, elemento, v->tamElemento);
    v->ce++;
}

void vectorInsertarElementoEnPos(VectorGenerico* v, const void* elemento, int pos)
{

    if (v->cap == v->ce)
    {
        vectorRedimensionar(v, v->cap * 2);
    }

    if(v->ce < pos)
    {
        return ERROR_POSICION_INVALIDA;
    }

    void* posIns = (char*)v->vec + pos * v->tamElemento;
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;

    // Mover el bloque de memoria desde la posicion de insercion hasta el ultimo elemento + 1
    for(void* i = ult; i >= posIns; i -= v->tamElemento)
    {
        memcpy(i + v->tamElemento, i, v->tamElemento); // *(i + 1) = *i;
    }

    memcpy(posIns, elemento, v->tamElemento);
    v->ce++;

    return OK;
}

void vectorEliminarElementoEnPos(VectorGenerico* v, int pos)
{

    if (v->cap == v->ce)
    {
        vectorRedimensionar(v, v->cap * 2);
    }

    if(v->ce < pos)
    {
        return ERROR_POSICION_INVALIDA;
    }

    void* posElim = (char*)v->vec + pos * v->tamElemento;
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;

    // Mover el bloque de memoria desde la posicion de insercion 1 elemento hacia la izquierda
    for(int* i = posElim; i < ult; i++)
    {
        *i = *(i + 1);
    }

    v->ce--;

    return OK;
}

int vectorEliminarElementoFinal(VectorGenerico* v)
{
    v->ce--;
    return OK;
}

void vectorImprimirDetalles(VectorGenerico* v)
{
    printf("Capacidad: %d \n", v->cap);
    printf("Cantidad de elementos: %d \n", v->ce);
    printf("Tamaño de elementos: %d \n", v->tamElemento);
}

void vectorRedimensionar(VectorGenerico* v, size_t nuevaCap)
{
    void* nuevo = realloc(v->vec, nuevaCap * v->tamElemento);

    if (nuevo == NULL)
    {
        printf("Error al reservar memoria. \n");
        return ERROR_RESERVA_MEMORIA;
    }

    v->vec = nuevo;
    v->cap = nuevaCap;
}

void vectorDestruir(VectorGenerico* v)
{
    v->cap = 0;
    v->ce = 0;
    v->tamElemento = 0;
    free(v->vec);
}

void vectorVaciar(VectorGenerico* v)
{
    v->ce = 0;
    vectorRedimensionar(v, CAP_INI);
}

void vectorMostrar(VectorGenerico* v, ImprimirElemento printFunc)
{

    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* i = v->vec;

    for(int pos=0; i<= ult; pos++, i+= v->tamElemento)
    {
        printFunc(pos, i);
    }
}

// Utilidades Genericas
void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);
    memcpy(aTemp, a, tamElem); // aTemp = *a;
    memcpy(a, b, tamElem); // *a = *b;
    memcpy(b, aTemp, tamElem); // *b = aTemp;
    free(aTemp);
}

void printInt(int pos, const void* elemento)
{
    const int* e = elemento;
    printf("[%d]: %d\n", e, *e);
}

void printChar(int pos, const void* elemento)
{
    const char* e = elemento;
    printf("[%d]: %c\n", e, *e);
}

void printFloat(int pos, const void* elemento)
{
    const float* e = elemento;
    printf("[%d]: %f\n", e, *e);
}

// Ordenamiento
void ordenarBurbujeo(VectorGenerico* v, CompararElemento cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;

    for(void* i = 1, *limJ = ult - 1; i < v->ce; i++, limJ--)
    {
        for(void* j = v->vec; j <= limJ; j++)
        {
            if(cmp(j, j+1)>0)
            {
                intercambiar(j, j + 1, v->tamElemento);
            }
        }
    }
}

void ordenarSeleccion(VectorGenerico* v, CompararElemento cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* m;

    for(void* i = v->vec; i < ult; i += v->tamElemento)
    {
        m = buscarMenor(i, ult, v->tamElemento, cmp);
        intercambiar(m, i, v->tamElemento);
    }
}


void* buscarMenor(void* ini, void* fin, size_t tamElem, CompararElemento cmp)
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

// Comparaciones
int compararChar(const void* e1, const void* e2)
{
    char* elemento1 = e1;
    char* elemento2 = e2;

    return elemento1 - elemento2;
}

int compararFloat(const void* e1, const void* e2)
{
    float* elemento1 = e1;
    float* elemento2 = e2;

    return elemento1 - elemento2;
}

int compararInt(const void* e1, const void* e2)
{
    int* elemento1 = e1;
    int* elemento2 = e2;

    return elemento1 - elemento2;
}

