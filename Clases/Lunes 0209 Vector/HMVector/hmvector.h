#ifndef HM_VECTOR_INCLUDED
#define HM_VECTOR_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define TAM 5
#define FACTOR_INCREMENTO 1.5
#define FACTOR_DECREMENTO 0.5

#define OK 0
#define ERROR_RESERVA_MEMORIA 1
#define ERROR_CREACION_VECTOR 2

typedef struct
{
    int* vec;
    int cap;
    int ce;
}Vector;

int crearVector(Vector* v);
int destruirVector(Vector* v);
int inicializarValores(Vector* v);
int vaciarVector(Vector* v);
int insertarElementoOrdenado(Vector* v, int elemento);
int eliminarElementoOrdenado(Vector* v, int elemento);
int redimensionarVector(Vector* v);
int imprimirVector(Vector* v);
int existeElemento(Vector* v);

#endif // HM_VECTOR_INCLUDED
