#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "retorno.h"

int generarIndice(const char* nomArch, const char* nomArchIndice);
int mostrarIndice(const char* nomArchIndice);
int cmpIndice(void* e1, void* e2);

#endif