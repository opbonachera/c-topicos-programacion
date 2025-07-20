#ifndef TDA_H_INCLUDED
#define TDA_H_INCLUDED

#include "macros.h"
#include "prueba.h"

typedef struct
{
    void *vec;
    int ce;
    unsigned cap_max;
    unsigned tamanio;
}TDA_Vector;

int TrozarLinea(const char *linea, TDA_Vector *buffer);
int TDA_Construir(TDA_Vector *v, unsigned tamanio);
int TDA_Insertar_al_final(TDA_Vector *v, void *valor);
int TDA_10_mas_frecuentes(TDA_Vector *v);
void TDA_sort(TDA_Vector *buffer, int comparar(const void*, const void*));
void* TDA_BuscarExtremo(TDA_Vector *buffer, int ce_real ,int comparar(const void*,const void*));
void* TDA_bSeq(TDA_Vector *v, void *clave, int cmp(const void*,const void*));
void *TDA_map(TDA_Vector *buffer, void accion(void*));
int TDA_Aumentar_apariciones(TDA_Vector *buffer, void *pos);
int TDA_Destruir(TDA_Vector *v);
int resize(TDA_Vector *buffer);

#endif // TDA_H_INCLUDED
