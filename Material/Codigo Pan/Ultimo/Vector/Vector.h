#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#define TODO_OK 0
#define SIN_MEM 1
#define DUPLICADO 2

#define BURBUJEO 1
#define SELECCION 2
#define INSERCION 3


typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}
Vector;


typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Actualizar)(void* elemV, const void* elemP);
typedef void (*ImprimirElem)(int pos, const void* e);


bool vectorCrear(Vector* v, size_t tamElem);
bool vectorCrearDeArchivo(Vector* v, size_t tamElem, const nomArch);
int vectorOrdInsertar(Vector* v, const void* elem, Cmp cmp, Actualizar actualizar);
int vectorInsertarEnPos(Vector* v, int elem, int pos);
int vectorInsertarAlInicio(Vector* v, int elem);
int vectorInsertarAlFinal(Vector* v, const void* elem);
int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp); // Búsqueda binaria / dicotómica
int vectorBuscar(const Vector* v, int* elem);
bool vectorOrdEliminarElem(Vector* v, void* elem, Cmp cmp);
bool vectorEliminarElem(Vector* v, void* elem, Cmp cmp);
bool vectorEliminarElemDePos(Vector* v, int pos, int* elemElim);
bool vectorEliminarElemPrimero(Vector* v, int* elemElim);
void vectorOrdenar(Vector* v, Cmp cmp, int metodo);
void vectorVaciar(Vector* v);
void vectorEliminar(Vector* v);
void vectorMostrar(Vector* v, ImprimirElem imprimirElem);
void cargarVectorRandom(Vector* v, size_t ce);
bool vectorGrabar(const Vector* v, const nomArch);


#endif // VECTOR_H
