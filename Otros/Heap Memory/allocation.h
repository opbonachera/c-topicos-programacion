#ifndef ALLOCATION_H_INCLUDED
#define ALLOCATION_H_INCLUDED

#define OK 0
#define ERROR_ALLOCATING_MEMORY 1
#define ERROR_FULL_CAPACITY

typedef int t_entero;

typedef struct
{
    void   *vec;
    size_t capacidad;
    size_t cantidadElementos;
    size_t tamanioElemento;
}t_vector_generico;

int printMemoryAddress(int *p);
int inicializarVectorGenerico(t_vector_generico *vector_generico, size_t tamanioElemento);
int imprimirDetallesVectorGenerico(t_vector_generico *vector_generico);
int asignarValoresVectorGenerico(t_vector_generico* vector_generico, void* valores, size_t cantidad);
int aniadirElemento(t_vector_generico* vector_generico);

#endif
