#include "TDA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TrozarLinea(const char *linea, TDA_Vector *buffer)
{
    char *ini;
    int ce_letras;
    void *pos;
    tPalabras pal;
    while(*linea)
    {
        ini = (char*)linea;
        while(*linea && *linea!='.' && *linea!='?')
            linea++;
        if( (*linea=='.' || *linea=='\0' ) && *linea!='?')
        {
            ce_letras = linea - ini;
            Copia_cadena(pal.palabra,ini,ce_letras);
            pal.cant_apariciones=1;
            if(!( pos=TDA_bSeq(buffer,&pal,Comparar_cadenas) ))
                TDA_Insertar_al_final(buffer,&pal);
            else
                TDA_Aumentar_apariciones(buffer,pos);
        }
        else
        {
            while(*linea && *linea!='.')
                linea++;
        }
        if(*linea=='.')
            linea++;
    }
    return 1;
}

int TDA_10_mas_frecuentes(TDA_Vector *v)
{
    return (v->ce=TAM);
}

void TDA_sort(TDA_Vector *buffer, int comparar(const void*, const void*))
{
    int i;
    void *ini = buffer->vec;
    void *clave;
    for(i=0;i<(buffer->ce-1);i++)
    {
        clave = TDA_BuscarExtremo(buffer,buffer->ce-i-1,comparar);
        if(clave!=buffer->vec)
            Intercambio_generico(clave,buffer->vec,buffer->tamanio);
        buffer->vec+=buffer->tamanio;
    }
    buffer->vec=ini;
}

void* TDA_BuscarExtremo(TDA_Vector *buffer, int ce_real ,int comparar(const void*,const void*))
{
    int i;
    void *p_vec = buffer->vec;
    void *clave = p_vec;
    for(i=0;i<ce_real;i++)
    {
        p_vec+=buffer->tamanio;
        if(!comparar(clave,p_vec))
            clave = p_vec;
    }
    return clave;
}

int TDA_Destruir(TDA_Vector *v)
{
    v->cap_max = 0;
    v->ce = 0;
    v->tamanio = 0;
    free(v->vec);
    return 1;
}

int TDA_Construir(TDA_Vector *v, unsigned tamanio)
{
    v->vec = malloc(tamanio*TAM);
    if(!v->vec)
        return 0;
    v->cap_max = TAM;
    v->ce = 0;
    v->tamanio = tamanio;
    return 1;
}

int TDA_Insertar_al_final(TDA_Vector *v, void *valor)
{
    void *pos;
    if(v->ce==v->cap_max)
    {
        if(!resize(v))
            return 0;
    }
    pos = v->vec + (v->ce)*(v->tamanio);
    memcpy(pos,valor,v->tamanio);
    (v->ce)++;
    return 1;
}

void *TDA_map(TDA_Vector *buffer, void accion(void*))
{
    int i;
    void *vec = buffer->vec;
    for(i=0;i<buffer->ce;i++)
    {
        accion(vec);
        vec+=buffer->tamanio;
    }
    return vec;
}

void* TDA_bSeq(TDA_Vector *v, void *clave, int cmp(const void*,const void*))
{
    void *p_vec = v->vec;
    int i;
    for(i=0;i<v->ce;i++)
    {
        if(cmp(clave,p_vec)==0)
        {
            memcpy(clave,p_vec,v->tamanio);
            return p_vec;
        }
        p_vec+=v->tamanio;
    }
    return NULL;
}

int resize(TDA_Vector *buffer)
{
    int bytes = (buffer->cap_max)*(buffer->tamanio);
    void *temporario = realloc(buffer->vec,2*bytes);
    if(!temporario)
        return 0;
    buffer->vec = temporario;
    buffer->cap_max+=buffer->cap_max;
    return 1;
}

int TDA_Aumentar_apariciones(TDA_Vector *buffer, void *pos)
{
    tPalabras *dest = (tPalabras*)buffer->vec;
    tPalabras *src = (tPalabras*)pos;
    dest = src;
    dest->cant_apariciones++;
    return 1;
}
