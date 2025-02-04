#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define OK 0
#define ERROR_RESERVA_MEMORIA 1
#define ERROR_APERTURA_ARCHIVO 2
#define ERROR 3

#define CAPACIDAD_INICIAL 5
#define TAM_DESCR 30
#define CANT_PRODS 5


typedef struct
{
    int codigo;
    char descripcion[TAM_DESCR + 1];
    float preUni;
    int stock;
}
Producto;

typedef struct
{
    unsigned int nroRegistro;
    int codigo;
}Indice;

typedef struct
{
    void* v;
    size_t ce;
    size_t cap;
    size_t tamElemento;
}Vector;

typedef int(*Cmp)(const void* e1, const void* e2);
typedef void(*Impr)(const void* elemento);


#endif
