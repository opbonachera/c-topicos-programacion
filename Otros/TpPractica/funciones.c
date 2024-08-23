#include "funciones.h"

#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define ERROR_APERTURA_ARCHIVO 1
#define ERROR_CREACION_ARCHIVO 2
#define MAX_ANCHO 1024
#define MAX_ALTO 1024

typedef struct
{
    unsigned char pixel[3]; // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos sólo 24 bits.
}t_pixel;


typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tamaño del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;

int copiarImagen()
{
    FILE* nuevaImagen;
    FILE* imagenOriginal;

    t_metadata* cabeceraNueva, cabeceraOriginal;

    imagenOriginal = fopen("unlam.bmp","rb");
    nuevaImagen    = fopen("nueva.bmp","wb");

    if(!imagenOriginal)
        return ERROR_APERTURA_ARCHIVO;

    if(!imagenOriginal)
        return ERROR_CREACION_ARCHIVO;

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    unsigned char byte[3];
    for(int i=0; i<cabeceraOriginal.comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    t_pixel imagen[360][240];
    for(int x=0; x<cabeceraOriginal.ancho; x++)
    {
        for(int y=0; y<cabeceraOriginal.alto; y++)
        {
            fread(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, imagenOriginal);
        }
    }

    for(int x=0; x<cabeceraOriginal.ancho; x++)
    {
        for(int y=0; y<cabeceraOriginal.alto; y++)
        {
            fwrite(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, nuevaImagen);
        }
    }


    fclose(imagenOriginal);
    fclose(nuevaImagen);


    leerCabecera("nueva.bmp", &cabeceraNueva);

    return OK;
}

int recortarImagen()
{
    FILE* nuevaImagen;
    FILE* imagenOriginal;

    t_metadata cabeceraNueva, cabeceraOriginal;

    imagenOriginal = fopen("unlam.bmp","rb");
    nuevaImagen    = fopen("nueva.bmp","wb");

    if(!imagenOriginal)
        return ERROR_APERTURA_ARCHIVO;

    if(!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    unsigned char byte[3];
    for(int i = 0; i < cabeceraOriginal.comienzoImagen; i++){
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    int nuevoX = cabeceraOriginal.ancho / 10; /* puede ser por 3 o por 10 */
    int nuevoY = cabeceraOriginal.alto / 10; /* puede ser por 3 o por 10  */

    // Ensure the correct array size
    t_pixel imagen[nuevoX][nuevoY];

    for(int y = 0; y < nuevoY; y++)
    {
        for(int x = 0; x < nuevoX; x++)
        {
            fread(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, imagenOriginal);

            fwrite(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, nuevaImagen);
        }
        fseek(imagenOriginal, (cabeceraOriginal.ancho - nuevoX) * 3, SEEK_CUR);
    }

    fseek(nuevaImagen, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, nuevaImagen);
    fwrite(&nuevoY, sizeof(unsigned int), 1, nuevaImagen);

    fclose(imagenOriginal);
    fclose(nuevaImagen);

    leerCabecera("nueva.bmp", &cabeceraNueva);

    return OK;
}


int leerCabecera(char file[], t_metadata *cabecera)
{
    FILE *img;

    img = fopen(file,"rb");

    printf("\n\n--------");
    printf("Filename: %s\n",file);

    fseek(img, 2, SEEK_SET);
    fread(&cabecera->tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&cabecera->tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&cabecera->comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&cabecera->ancho, sizeof(unsigned int), 1, img);

    fseek(img, 22, SEEK_SET);
    fread(&cabecera->alto, sizeof(unsigned int), 1, img);

    fseek(img, 28, SEEK_SET);
    fread(&cabecera->profundidad, sizeof(unsigned short), 1, img);

    printf("Tamaño de archivo: %u bytes\n",  cabecera->tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", cabecera->tamEncabezado);
    printf("Alto: %u bytes\n",               cabecera->alto);
    printf("Ancho: %u bytes\n",              cabecera->ancho);
    printf("Comienzo de imagen: byte %u\n",  cabecera->comienzoImagen);
    printf("Profundidad: %u bits\n",         cabecera->profundidad);

    fclose(img);
    return 0;
}

int rotarImagenDerecha()
{
    FILE* nuevaImagen;
    FILE* imagenOriginal;

    t_metadata cabeceraNueva, cabeceraOriginal;

    imagenOriginal = fopen("unlam.bmp", "rb");
    nuevaImagen    = fopen("nueva.bmp", "wb");

    if (!imagenOriginal)
        return ERROR_APERTURA_ARCHIVO;

    if (!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    unsigned char byte[3];
    for(int i = 0; i < cabeceraOriginal.comienzoImagen; i++){
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;

    t_pixel imagen[240][360];

    for(int y = 0; y < altoOriginal; y++) {
        for(int x = 0; x < anchoOriginal; x++) {
            fread(&imagen[y][x].pixel[0], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[1], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[2], sizeof(unsigned char), 1, imagenOriginal);
        }
    }

    for(int y = 0; y < anchoOriginal; y++) {
        for(int x = 0; x < altoOriginal; x++) {
            fwrite(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, nuevaImagen);
        }
    }

    int nuevoX = altoOriginal;
    int nuevoY = anchoOriginal;

    fseek(nuevaImagen, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, nuevaImagen);
    fwrite(&nuevoY, sizeof(unsigned int), 1, nuevaImagen);

    fclose(imagenOriginal);
    fclose(nuevaImagen);

    leerCabecera("nueva.bmp", &cabeceraNueva);

    return OK;
}

int rotarImagenIzquierda()
{
    FILE* nuevaImagen;
    FILE* imagenOriginal;

    t_metadata cabeceraNueva, cabeceraOriginal;

    imagenOriginal = fopen("unlam.bmp", "rb");
    nuevaImagen    = fopen("nueva.bmp", "wb");

    if (!imagenOriginal)
        return ERROR_APERTURA_ARCHIVO;

    if (!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    unsigned char byte[3];
    for(int i = 0; i < cabeceraOriginal.comienzoImagen; i++){
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;

    t_pixel imagen[240][360];

    for(int y = 0; y < altoOriginal; y++) {
        for(int x = 0; x < anchoOriginal; x++) {
            fread(&imagen[y][x].pixel[0], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[1], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[2], sizeof(unsigned char), 1, imagenOriginal);
        }
    }

    for(int y = 0; y < anchoOriginal; y++) {
        for(int x = 0; x < altoOriginal; x++) {
            fwrite(&imagen[x][altoOriginal - 1 - y].pixel[0], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][altoOriginal - 1 - y].pixel[1], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][altoOriginal - 1 - y].pixel[2], sizeof(unsigned char), 1, nuevaImagen);
        }
    }

    int nuevoX = altoOriginal;
    int nuevoY = anchoOriginal;

    fseek(nuevaImagen, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, nuevaImagen);
    fwrite(&nuevoY, sizeof(unsigned int), 1, nuevaImagen);

    fclose(imagenOriginal);
    fclose(nuevaImagen);

    leerCabecera("nueva.bmp", &cabeceraNueva);

    return OK;
}

int transposeMatrix()
{
    int ancho = 4;
    int alto=5;
    int matrix[4][5] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16},{17,18,19,10}};


    printf("Transposed matrix");
    for(int x = 0; x < ancho; x++)
    {
        for(int y = 0; y < alto; y++)
        {
            printf(" %d ", matrix[ancho - 1 - x][alto - 1 - y]);
        }
        printf("\n");
    }

    return 0;
}


