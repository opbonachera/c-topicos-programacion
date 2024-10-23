#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define OK 0
#define ERROR_RESERVA_MEMORIA 1

typedef struct
{
    unsigned char px[3];
}Pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}Metadata;

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
void   destruirMatriz(void** matriz, int n);

int leerCabecera(FILE* img, Metadata *cabecera);

void pixelearImagen(char* nombreImgEntrada, char* nombreImgSalida);
void modificarDimensiones(FILE* img, int nuevoX, int nuevoY);
void escribirImagen(FILE* img, Pixel** matrizImagen, int filas, int columnas);
void cargarImagen(FILE* img, Pixel** matrizImagen, int filas, int columnas);
int crearImagen(char* imgOriginal, char* copia);
void escribirCabecera(FILE* img, FILE* nueva, Metadata* cabeceraOriginal);
int copiarImagen(char* nombreImgEntrada, char* nombreImgSalida);


#endif
