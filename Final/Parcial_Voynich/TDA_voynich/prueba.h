#ifndef PRUEBA_H_INCLUDED
#define PRUEBA_H_INCLUDED
#include "macros.h"
#include "TDA.h"

typedef struct
{
    char palabra[MAXLINE];
    int cant_apariciones;
}tPalabras;

int Procesar_lote_texto(const char *nom_Arch);
void EliminarSalto_linea(char *linea);
int Comparar_cadenas(const void *a, const void *b);
char* Copia_cadena(char *cad_destino, const char *cad_origen, unsigned bytes);
void Mostrar_palabra(void *info);
int Mas_frecuente(const void *a, const void *b);
int Intercambio_generico(void *a, void *b, unsigned tamanio);

#endif // PRUEBA_H_INCLUDED
