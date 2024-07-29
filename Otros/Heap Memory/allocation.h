#ifndef ALLOCATION_H_INCLUDED
#define ALLOCATION_H_INCLUDED

#define OK 0
#define ERROR_ALLOCATING_MEMORY 1
#define ERROR_REALLOCATING_MEMORY 2
#define ERROR_FULL_CAPACITY 3
#define ERROR_INVALID_POSITION 4

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
int aniadirElemento(t_vector_generico* vector_generico, void* elemento);
int imprimirVectorChar(t_vector_generico* vector_generico);
int imprimirVectorInt(t_vector_generico* vector_generico);
int imprimirVectorFloat(t_vector_generico* vector_generico);
int eliminarElementoUltimaPosicion(t_vector_generico* vector_generico);
int eliminarElementoPosicionDeterminada(t_vector_generico* vector_generico, int posicion);

#endif
