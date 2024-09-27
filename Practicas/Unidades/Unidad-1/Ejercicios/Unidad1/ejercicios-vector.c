#include "ejercicios-vector.h"

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

void vectorCargarRandom(VectorGenerico* v, size_t ce)
{
    srand(time(NULL));

    for (int i = 0; i < ce; i++)
    {
        int randomValue = rand() % v->cap;
        vectorInsertarElementoFinal(v, &randomValue);
    }

    vectorImprimirDetalles(v);
}

void vectorCargarEnteros(VectorGenerico* v, size_t ce)
{
    for (int i = 0; i < ce; i++)
    {
        int value = i + 1;
        vectorInsertarElementoFinal(v, &value);
    }
}

void vectorImprimirDetalles(VectorGenerico* v)
{
    printf("Capacidad: %d \n", v->cap);
    printf("Cantidad de elementos: %d \n", v->ce);
    printf("Tama�o de elementos: %d \n", v->tamElemento);
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


// ---------------- EJERCICIO 1.1
int vectorInsertarElementoEnPos(VectorGenerico* v, const void* elemento, int pos)
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

// ---------------- EJERCICIO 1.2
int vectorInsertarElementoOrdenado(VectorGenerico* v, CompararElemento cmp, const void* elemento)
{
    // Verificar que haya espacio
    // Encontrar la posicion de insercion
    // Insertar el elemento

    if(v->cap == v->ce)
    {
        vectorRedimensionar(v, FACTOR_REDIMENSION);
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* posIns = v->vec;

    while(cmp(elemento, posIns) > 0  && posIns <= ult)
    {
        posIns += v->tamElemento;
    }

     for(void* i = ult; i >= posIns; i -= v->tamElemento)
    {
        memcpy(i + v->tamElemento, i, v->tamElemento); // *(i + 1) = *i;
    }

    memcpy(posIns, elemento, v->tamElemento);
    v->ce++;

    return OK;

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

// ---------------- EJERCICIO 1.3
int vectorEliminarElementoOrdenado(VectorGenerico* v, CompararElemento cmp, const void* elemento)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* posElim = v->vec;

    while((posElim <= ult) && (cmp(elemento, posElim)>0))
    {
        posElim+=v->tamElemento;
    }

    if(posElim > ult || cmp(elemento, posElim) < 0)
    {
        return ERROR_ELEMENTO_INEXISTENTE;
    }

    memcpy((void*)elemento, posElim, v->tamElemento);

    for(void* i = ult; i>=posElim; i-=v->tamElemento)
    {
        memcpy(i, i+v->tamElemento, v->tamElemento);
    }

    v->ce--;

    return OK;
}

// ---------------- EJERCICIO 1.4
int vectorEliminarPrimeraAparicion(VectorGenerico* v, CompararElemento cmp, const void* elemento)
{
    if (v->ce == 0)
    {
        return ERROR_VECTOR_VACIO;
    }

    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* posElim = v->vec;

    while ((posElim <= ult) && (cmp(elemento, posElim) != 0))
    {
        posElim += v->tamElemento;
    }

    if (posElim > ult)
    {
        return ERROR_ELEMENTO_INEXISTENTE;
    }


    memcpy((void*)elemento, posElim, v->tamElemento);
    for (void* i = posElim; i < ult; i += v->tamElemento)
    {
        memcpy(i, i + v->tamElemento, v->tamElemento);
    }

    v->ce--;

    return OK;
}

// ---------------- EJERCICIO 1.5
int vectorEliminarTodasApariciones(VectorGenerico* v, CompararElemento cmp, const void* elemento)
{
    // No se si es la mejor forma pero es la mas rapida que se me ocurre
    if (v->ce == 0)
    {
        return ERROR_VECTOR_VACIO;
    }

    void* posElim = v->vec;
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;


    while (posElim <= ult)
    {
        if (cmp(elemento, posElim) == 0)
        {

            vectorEliminarPrimeraAparicion(v, cmp, posElim);

            posElim = v->vec;

            ult = v->vec + (v->ce - 1) * v->tamElemento;
        }else
        {
            posElim += v->tamElemento;
        }
    }

    return OK;
}




int vectorEliminarElementoFinal(VectorGenerico* v)
{
    if(v->ce==0)
    {
        return ERROR_VECTOR_VACIO;
    }

    v->ce--;
    return OK;
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
    // minuto 2:08:00
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* limJ = ult - v->tamElemento;

    for(int i = 1; i < v->ce; i++, limJ-=v->tamElemento)
    {
        for(void* j = v->vec; j <= limJ; j+=v->tamElemento)
        {
            if(cmp(j, j+v->tamElemento) > 0)
            {
                intercambiar(j, j + v->tamElemento, v->tamElemento);
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

        if( cmp(j, m) < 0)
        {
            m = j;
        }
    }

    return m;
}

void ordenarInsercion(VectorGenerico* v, CompararElemento cmp)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElemento;
    void* elemAIns = malloc(v->tamElemento);
    void* j;

    for(void* i = v->vec + v->tamElemento; i <= ult; i += v->tamElemento)
    {
        memcpy(elemAIns, i, v->tamElemento);
        j = i - v->tamElemento;

        while(j >= v->vec && cmp(elemAIns, j) < 0)
        {
            memcpy(j + v->tamElemento, j, v->tamElemento);
            j -= v->tamElemento;
        }

        memcpy(j + v->tamElemento, elemAIns, v->tamElemento);
    }

    free(elemAIns);
}

// Comparaciones compupc
int compararChar(const void* e1, const void* e2)
{
    char* elemento1 = e1;
    char* elemento2 = e2;

    return *elemento1 - *elemento2;
}

int compararFloat(const void* e1, const void* e2)
{
    float* elemento1 = e1;
    float* elemento2 = e2;

    return *elemento1 - *elemento2;
}

int compararInt(const void* e1, const void* e2)
{
    int* elemento1 = e1;
    int* elemento2 = e2;

    return *elemento1 - *elemento2;
}

// Busqueda
