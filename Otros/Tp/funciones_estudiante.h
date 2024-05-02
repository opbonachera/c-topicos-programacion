#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include "constantes.h"
#include "estructuras.h"

int solucion(int argc, char* argv[]);

void escalaDeGrises(t_pixel *);
void invertirColores(t_pixel *);
void aumentarContraste(t_pixel *, int, int);
void aumentarContraste(t_pixel *, int, int);

int leerCabecera(char [], t_metadata *);
int escribirCabecera(FILE *archivoNuevo);
int escribirDatos(FILE *archivoNuevo);
int modificarDimensiones(FILE *archivoNuevo, unsigned int, unsigned int);
int crearImagen();


#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
