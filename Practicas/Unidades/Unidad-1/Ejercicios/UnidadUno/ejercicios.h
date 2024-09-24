#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED


#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Constantes
#define  FACTOR_REDIMENSION 1.5
#define  CAP_INI 10

// Mensajes
#define OK 0
#define ERROR 4
#define ERROR_RESERVA_MEMORIA 1
#define ERROR_ELEMENTO_DUPLICADO 2
#define ERROR_POSICION_INVALIDA 3

// Estructuras
typedef struct
{
    size_t tamElemento;
    size_t cap;
    size_t ce;
    void*  vec;
}VectorGenerico;
// Funciones
typedef void(*ImprimirElemento)(int pos, const void* elemento);
typedef int(*CompararElemento)(int pos, const void* elemento);

/*
    Para trabajar con cualquier tipo de dato es necesario contar con:
    - Funciones genericas que reciban el TDA
    - Funciones especificas que conozcan el tipo de dato en concreto y realicen comparaciones
    - Funciones para mover memoria sin conocer el tipo de dato con el cual se va a operar
*/

// Vector
int vectorCrear    (VectorGenerico* v, size_t tamElem);
void vectorDestruir (VectorGenerico* v);
void vectorVaciar   (VectorGenerico* v);
void vectorCargar   (VectorGenerico* v, size_t ce);
void vectorMostrar  (VectorGenerico* v, ImprimirElemento printFunc);
void vectorRedimensionar(VectorGenerico* v, size_t nuevaCap);
void vectorImprimirDetalles(VectorGenerico* v);

// _Insercion y eliminacion de elementos
void vectorInsertarElementoFinal (VectorGenerico* v, const void* elemento);
void vectorInsertarElementoEnPos(VectorGenerico* v, const void* elemento, int pos);
void vectorEliminarElementoEnPos(VectorGenerico* v, int pos);
int  vectorEliminarElementoFinal(VectorGenerico* v);

// Ordenamiento
void ordenarBurbujeo(VectorGenerico* v, CompararElemento cmp);
void* buscarMenor(void* ini, void* fin, size_t tamElem, CompararElemento cmp);
//Utilidades genericas
void intercambiar(void* a, void* b, size_t tamElem);

// _Impresion
void printInt(int pos, const void* elemento);
void printChar(int pos, const void* elemento);
void printFloat(int pos, const void* elemento);

// _Comparacion
int compararChar(const void* e1, const void* e2);
int compararFloat(const void* e1, const void* e2);
int compararInt(const void* e1, const void* e2);

#endif // EJERCICIOS_H_INCLUDED
