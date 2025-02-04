#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1

#define CAP_INICIAL 10

typedef struct
{
    int   cap;
    int   ce;
    int   tamElem;
    void* vec;
}Vector;

// ---- GENERICAS ----
typedef void(*Imp)(void* elemento);

void imprimirCaracter(void* elemento);
void imprimirEntero(void* elemento);

typedef void(*Cmp)(void* elemento1, void* elemento2);

int compararEnteros(void* elemento1, void* elemento2);
int compararCaracteres(void* elemento1, void* elemento2);

// ---- VECTOR ----
int vectorInicializar(Vector* v, int ce, int tamElem);
int vectorDestruir(Vector* v);
int vectorImprimir(Vector* v, Imp imprimir);
int vectorBusquedaBin(Vector* v);
int vectorCargar(Vector* v);

// ---- MATRIZ ----
void** matrizInicializar(void** mat, int cF, int cC);
int matrizDestruir(void** mat, int cF);
int matrizMostrar(void** mat, Imp imprimir);

int main()
{
    Vector vecCodDepositos;

    vectorInicializar(&vecCodDepositos, 4, sizeof(char));
    vectorCargar(&vecCodDepositos);
    vectorImprimir(&vecCodDepositos, imprimirCaracter);

    char target = 'C';

    int index = buscarVectorOrdenadoBin(&vecCodDepositos, &target, 0, vecCodDepositos.ce - 1, compararCaracteres);

    vectorDestruir(&vecCodDepositos);
    vectorDestruir(&vecCodDepositos);

    return 0;
}

int vectorInicializar(Vector* v, int ce, int tamElem)
{
    v->vec = malloc(tamElem * ce);

    if(!v->vec)
    {
        return ERROR;
    }

    v->ce = ce;
    v->cap = CAP_INICIAL;
    v->tamElem = tamElem;

    return OK;
}

int vectorDestruir(Vector* v)
{
    free(v->vec);

    v->cap = 0;
    v->ce = 0;
    v->tamElem = 0;

    return OK;
}

int vectorImprimirDetalles(Vector* v)
{
    printf("Cantidad de elementos: [%d]\n", v->ce);
    printf("Tamaño del elemento: [%d] bytes \n", v->tamElem);
    printf("Cantidad de elementos: [%d]\n", v->tamElem);
}

int vectorImprimir(Vector* v, Imp imprimir)
{
    void* ult = v->vec + (v->ce - 1) * v->tamElem;
    int i=0;

    for (void* p = v->vec; p <= ult; p += v->tamElem)
    {
        imprimir(p);
    }

    return OK;
}

int vectorBusquedaBin(Vector* v);

int vectorCargar(Vector* v)
{
    char* arr = (char*) v->vec;

    arr[0] = 'A';
    arr[1] = 'B';
    arr[2] = 'C';
    arr[3] = 'D';

    return OK;
}

void imprimirCaracter(void* elemento)
{
    char* c = elemento;
    printf("{%c} - \n", *c);
}


int compararCaracteres(void* elemento1, void* elemento2)
{
    char* e1 = elemento1;
    char* e2 = elemento2;

    return *e1 - *e2;
}

void imprimirEntero(void* elemento)
{
    int* e = elemento;
    printf("[%d] - \n", *e);
}

int buscarVectorOrdenadoBin(Vector* v, void* elemento, size_t inicio, size_t fin, Cmp cmp)
{
    if (v->ce == 0 || !v->vec) // Empty vector check
        return -1;

    while (inicio <= fin)
    {
        size_t mitad_idx = inicio + (fin - inicio) / 2;
        void* mitad = (char*)v->vec + mitad_idx * v->tamElem;  // Correct: Get pointer to element

        int comparison = cmp(elemento, mitad);  // Corrected: Pass pointer, not index

        if (comparison == 0)
            return mitad_idx;
        else if (comparison < 0)
        {
            if (mitad_idx == 0) // Prevent underflow
                return -1;
            fin = mitad_idx - 1;
        }
        else
        {
            inicio = mitad_idx + 1;
        }
    }

    return -1;
}
