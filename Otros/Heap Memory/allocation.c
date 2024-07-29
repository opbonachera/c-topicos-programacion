#include <stdio.h>
#include <stdlib.h>

#include "allocation.h"
/*
int printMemoryAddress(int *p)
{
    printf("memory address: %p\n", (void *)p);
    return OK;
}

int imprimirEntero(t_entero entero)
{
    printf("%d", entero);
    return OK;
}

int inicializarVectorGenerico(t_vector_generico* vector_generico, size_t tamanioElemento)
{
    vector_generico->cantidadElementos = 0;
    vector_generico->capacidad = 5;
    vector_generico->tamanioElemento = tamanioElemento;
    vector_generico->vec = (int *)malloc(vector_generico->capacidad * tamanioElemento);

    if (vector_generico->vec == NULL) {
        printf("Error allocating memory\n");
        free(vector_generico->vec);
        return ERROR_ALLOCATING_MEMORY;
    }

    return OK;
}

int asignarValoresVectorGenerico(t_vector_generico* vector_generico)
{

    for (size_t i = 0; i < ((vector_generico->capacidad) - 1); i++)
    {
        vector_generico->vec[i] = i + 1;
        vector_generico->cantidadElementos++;
    }

    return 0;
}

int imprimirValoresVectorGenerico(t_vector_generico* vector_generico)
{

    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%d ", vector_generico->vec[i]);
    }
    printf("\n");
    return 0;
}

int imprimirDetallesVectorGenerico(t_vector_generico* vector_generico)
{
    printf("Cantidad de elementos: %d\n", vector_generico->cantidadElementos);
    printf("Capacidad: %d\n", vector_generico->capacidad);
    printf("Tamanio de elementos: %d\n", vector_generico->tamanioElemento);
    return 0;
}

int aniadirElemento(t_vector_generico* vector_generico)
{
    int elemento = 5;

    if(vector_generico->cantidadElementos == vector_generico->capacidad)
    {
        printf("La capacidad del vector esta llena");
        return ERROR_FULL_CAPACITY;
    }

    // Puntero que apunta a la ultima posicion de memoria disponible
    int* p = (vector_generico->vec) + (vector_generico->cantidadElementos);
    *p = elemento;

    vector_generico->cantidadElementos++;

    return OK;
}
*/
// Codigo por ChatGPT

int inicializarVectorGenerico(t_vector_generico* vector_generico, size_t tamanioElemento)
{
    vector_generico->cantidadElementos = 0;
    vector_generico->capacidad = 5;
    vector_generico->tamanioElemento = tamanioElemento;
    vector_generico->vec = malloc(vector_generico->capacidad * tamanioElemento);

    if (vector_generico->vec == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return -1;
    }

    return 0;
}

int asignarValoresVectorGenerico(t_vector_generico* vector_generico, void* valores, size_t cantidad)
{
    if (cantidad > vector_generico->capacidad) {
        fprintf(stderr, "La cantidad de valores excede la capacidad del vector\n");
        return -1;
    }

    vector_generico->cantidadElementos = cantidad;
    memcpy(vector_generico->vec, valores, cantidad * vector_generico->tamanioElemento);

    return 0;
}

int imprimirDetallesVectorGenerico(t_vector_generico* vector_generico)
{
    printf("Cantidad de elementos: %zu\n", vector_generico->cantidadElementos);
    printf("Capacidad: %zu\n", vector_generico->capacidad);
    printf("Tamanio de elementos: %zu\n", vector_generico->tamanioElemento);
    return 0;
}

int agregarElemento(t_vector_generico* vector_generico, void* elemento)
{
    if (vector_generico->cantidadElementos == vector_generico->capacidad) {
        fprintf(stderr, "No se puede agregar más elementos, el vector está lleno\n");
        return -1;
    }

    void* destino = (char*)vector_generico->vec + vector_generico->cantidadElementos * vector_generico->tamanioElemento;
    memcpy(destino, elemento, vector_generico->tamanioElemento);
    vector_generico->cantidadElementos++;

    return 0;
}

void imprimirVectorEnteros(t_vector_generico* vector_generico)
{
    int* vec = (int*)vector_generico->vec;
    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void imprimirVectorFloats(t_vector_generico* vector_generico)
{
    float* vec = (float*)vector_generico->vec;
    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%f ", vec[i]);
    }
    printf("\n");
}

int main()
{
    t_vector_generico vectorEnteros;
    inicializarVectorGenerico(&vectorEnteros, sizeof(int));

    int valoresEnteros[] = {1, 2, 3, 4, 5};
    asignarValoresVectorGenerico(&vectorEnteros, valoresEnteros, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    int nuevoEntero = 6;
    if (agregarElemento(&vectorEnteros, &nuevoEntero) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de enteros.\n");
    }

    imprimirDetallesVectorGenerico(&vectorEnteros);
    imprimirVectorEnteros(&vectorEnteros);

    t_vector_generico vectorFloats;
    inicializarVectorGenerico(&vectorFloats, sizeof(float));

    float valoresFloats[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    asignarValoresVectorGenerico(&vectorFloats, valoresFloats, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    float nuevoFloat = 6.6;
    if (agregarElemento(&vectorFloats, &nuevoFloat) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de floats.\n");
    }

    imprimirDetallesVectorGenerico(&vectorFloats);
    imprimirVectorFloats(&vectorFloats);

    // Liberar la memoria asignada
    free(vectorEnteros.vec);
    free(vectorFloats.vec);

    return 0;
}
