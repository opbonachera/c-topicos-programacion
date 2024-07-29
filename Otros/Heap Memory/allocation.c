#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocation.h"

int inicializarVectorGenerico(t_vector_generico* vector_generico, size_t tamanioElemento)
{
    vector_generico->cantidadElementos = 0;
    vector_generico->capacidad = 5;
    vector_generico->tamanioElemento = tamanioElemento;
    vector_generico->vec = malloc(vector_generico->capacidad * tamanioElemento);

    if (vector_generico->vec == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return ERROR_ALLOCATING_MEMORY;
    }

    return OK;
}

int asignarValoresVectorGenerico(t_vector_generico* vector_generico, void* valores, size_t cantidad)
{
    if (cantidad > vector_generico->capacidad) {
        printf("La cantidad de valores excede la capacidad del vector\n");
        return ERROR_FULL_CAPACITY;
    }

    vector_generico->cantidadElementos = cantidad;
    memcpy(vector_generico->vec, valores, cantidad * vector_generico->tamanioElemento);

    return OK;
}

int imprimirDetallesVectorGenerico(t_vector_generico* vector_generico)
{
    printf("Cantidad de elementos: %d\n", vector_generico->cantidadElementos);
    printf("Capacidad: %d\n", vector_generico->capacidad);
    printf("Tamanio de elementos: %d\n", vector_generico->tamanioElemento);
    printf("Tamanio del elemento: %d bytes\n", vector_generico->tamanioElemento);
    return OK;
}

int aniadirElemento(t_vector_generico* vector_generico, void* elemento)
{
    if (vector_generico->cantidadElementos == vector_generico->capacidad) {
        printf("El vector esta lleno pero se duplicara su capacidad para añadir el elemento deseado. \n");
        int nuevaCapacidad = vector_generico->capacidad * 2;
        int* temp = (int *)realloc(vector_generico->vec, nuevaCapacidad * vector_generico->tamanioElemento);


        if(!temp)
        {
            printf("Error reallocating memory.\n");
            return ERROR_REALLOCATING_MEMORY;
        }

        vector_generico->vec = temp;
        vector_generico->capacidad = nuevaCapacidad;

        printf("Nueva capacidad: %d\n", vector_generico->capacidad);
    }

    void* destino = (char*)vector_generico->vec + vector_generico->cantidadElementos * vector_generico->tamanioElemento; // Ultima posicion en el vector generico
    memcpy(destino, elemento, vector_generico->tamanioElemento);
    vector_generico->cantidadElementos++;

    return OK;
}

int imprimirVectorEnteros(t_vector_generico* vector_generico)
{
    printf("Imprimiendo vector de enteros...\n");
    int* vec = (int*)vector_generico->vec;
    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%d", *vec);
        vec++;
    }
    printf("\n");
    return OK;
}

int imprimirVectorFloats(t_vector_generico* vector_generico)
{
    printf("Imprimiendo vector de floats...\n");
    float* vec = (float*)vector_generico->vec;
    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%f ", *vec);
        vec++;
    }
    printf("\n");
    return OK;
}

int imprimirVectorChar(t_vector_generico* vector_generico)
{
    printf("Imprimiendo vector de caracteres...\n");
    char* vec = (char*)vector_generico->vec;
    for (size_t i = 0; i < vector_generico->cantidadElementos; i++)
    {
        printf("%c ", *vec);
        vec++;
    }
    printf("\n");
    return OK;
}

int eliminarElementoUltimaPosicion(t_vector_generico* vector_generico)
{
    int nuevaCantidadElementos = vector_generico->cantidadElementos - 1;

    vector_generico->cantidadElementos = nuevaCantidadElementos;

    return OK;
}

int eliminarElementoPosicionDeterminada(t_vector_generico* vector_generico, int posicion) {
    if (posicion < 0 || (size_t)posicion >= vector_generico->cantidadElementos) {
        printf("Posicion de movimiento invalida");
        return ERROR_INVALID_POSITION;
    }

    void *pos = (char*)vector_generico->vec + (posicion * vector_generico->tamanioElemento);
    void *siguientePosicion = (char*)pos + vector_generico->tamanioElemento;
    size_t cantidadElementosAMover = vector_generico->cantidadElementos - posicion - 1;

    memmove(pos, siguientePosicion, cantidadElementosAMover * vector_generico->tamanioElemento);
    vector_generico->cantidadElementos--;

    return OK;
}

