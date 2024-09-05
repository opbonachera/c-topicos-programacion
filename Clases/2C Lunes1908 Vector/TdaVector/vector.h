#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 10
#define OK 0
#define VECTOR_LLENO 1
#define ELEMENTO_DUPLICADO 2
#define VECTOR_VACIO 3

typedef struct
{
    int vec[TAM];
    int ce;
}t_vector;


int inicializarVector(t_vector* vect);
int imprimirVector(t_vector* vect);
int ordenarVector(t_vector* vect);
int existeElemento(t_vector*, int elemento);
int insertarElementoVectorOrdenado(t_vector* vect, int elemento);
int removerElementoVectorOrdenado(t_vector* vect, int elemento);

#endif // VECTOR_H_INCLUDED
