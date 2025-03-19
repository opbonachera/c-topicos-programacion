#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    void* v;
    int   tamElem;
    int   ce;
    int   cap;
}Vector;

// Funciones genericas
typedef int(*Cmp)(void* e1, void* e2);
int cmpEntero(void* e1, void* e2);

// Creacion y eliminacion de estructura
int  vectorInicializar(Vector* vec, int tamElem, int ce);
void vectorVaciar(Vector* vec);
void vectorDestruir(Vector* vec);
int  vectorRedimensionar(Vector* vec, int factorRedimension);
void vectorImprimirContenido(Vector* vec);
void vectorImprimirDetalles(Vector* vec);

// Asignacion de elementos
void vectorAsignarEnterosOrdenados(Vector* vec);
void vectorAsignarEnterosAleatorio(Vector* vec, int min, int max);

// Insercion y eliminacion de elementos
void vectorOrdAgregarElemento(Vector* vec, void* elemento, Cmp* cmp);
void vectorOrdEliminarElemento();

// Orden del vector
void vectorOrdenar(Vector* vector, int metodo);
void vectorOrdenarBurbujeo(Vector* vec, Cmp cmp);
void vectorOrdenarInsercion(Vector* vector);
void vectorOrdenarSeleccion(Vector* vector);

// Utilidades
void intercambiar(void* e1, void* e2, int tamElem);


#endif // VECTOR_H_INCLUDED
