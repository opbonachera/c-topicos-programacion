#include "funciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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


int copiarImagen(FILE* imagenOriginal, char* nombreNuevoArchivo)
{
    FILE* nuevaImagen = fopen(nombreNuevoArchivo, "wb");

    if(!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    t_metadata cabeceraOriginal;

    leerCabecera(imagenOriginal, &cabeceraOriginal);
    escribirCabecera(imagenOriginal, nuevaImagen, cabeceraOriginal);

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;


    t_pixel** imagen = malloc(sizeof(t_pixel *) * altoOriginal);

    for (int i = 0; i < altoOriginal; i++) {
        imagen[i] = malloc(anchoOriginal * sizeof(t_pixel));
    }

    for (int i = 0; i < altoOriginal; i++) {
        fread(imagen[i], sizeof(t_pixel), anchoOriginal, imagenOriginal);
    }


    for (int i = 0; i < altoOriginal; i++) {
        fwrite(imagen[i], sizeof(t_pixel), anchoOriginal, nuevaImagen);
    }


    for (int i = 0; i < altoOriginal; i++) {
        free(imagen[i]);
    }

    free(imagen);
    fclose(nuevaImagen);
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
            fread(&imagen[y][x], sizeof(unsigned char), 3, imagenOriginal);
            /*fread(&imagen[y][x].pixel[0], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[1], sizeof(unsigned char), 1, imagenOriginal);
            fread(&imagen[y][x].pixel[2], sizeof(unsigned char), 1, imagenOriginal);*/
        }
    }

    for(int y = 0; y < anchoOriginal; y++) {
        for(int x = 0; x < altoOriginal; x++) {
            fwrite(&imagen[x][y], sizeof(unsigned char), 3, nuevaImagen);
            /*fwrite(&imagen[x][y].pixel[0], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[1], sizeof(unsigned char), 1, nuevaImagen);
            fwrite(&imagen[x][y].pixel[2], sizeof(unsigned char), 1, nuevaImagen);*/
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

int rotarMatrizIzquierda() {
    int alto = 5, ancho = 4;

    int matriz[5][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16},
                        {17, 18, 19, 20}};

    int matrizRotada[4][5];

    for(int i=0; i<alto; i++)
    {
        for(int j=0; j<ancho; j++)
        {
            matrizRotada[j][i] = matriz[i][j];
        }
    }

    for (int i = 0; i < ancho; i++) {
        for (int j = 0; j < alto; j++) {
            printf("%d ", matrizRotada[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int rotarImagenIzquierda()
{
    FILE* nuevaImagen;
    FILE* imagenOriginal;

    t_metadata cabeceraNueva, cabeceraOriginal;

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    imagenOriginal = fopen("unlam.bmp", "rb");
    nuevaImagen    = fopen("nueva.bmp", "wb");

    if (!imagenOriginal)
        return ERROR_APERTURA_ARCHIVO;

    if (!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;


    unsigned char byte[3];
    for(int i = 0; i < cabeceraOriginal.comienzoImagen; i++){
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;

    t_pixel imagen[240][360];
    t_pixel imagenNueva[360][240];

    for(int y = 0; y < altoOriginal; y++) {
        for(int x = 0; x < anchoOriginal; x++) {
            fread(&imagen[y][x], sizeof(unsigned char), 3, imagenOriginal);
            imagenNueva[x][altoOriginal - 1 - y] = imagen[y][x];
        }
    }

    for(int x = 0; x < anchoOriginal; x++) {
        for(int y = 0; y < altoOriginal; y++) {
            fwrite(&imagenNueva[x][y], sizeof(unsigned char), 3, nuevaImagen);
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

int espejarImagenHorizontal() {
    FILE* imagenOriginal;
    FILE* nuevaImagen;

    t_metadata cabeceraOriginal;

    imagenOriginal = fopen("unlam.bmp", "rb");
    nuevaImagen    = fopen("horizontal.bmp", "wb");

    if (!imagenOriginal)
        return -1; // ERROR_APERTURA_ARCHIVO

    if (!nuevaImagen) {
        fclose(imagenOriginal);
        return -2; // ERROR_CREACION_ARCHIVO
    }


    leerCabecera("unlam.bmp", &cabeceraOriginal);

    unsigned char byte;
    for (int i = 0; i < cabeceraOriginal.comienzoImagen; i++) {
        fread(&byte, sizeof(unsigned char), 1, imagenOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, nuevaImagen);
    }

    t_pixel matrizOriginal[ANCHO][ALTO];
    t_pixel matrizEspejada[ANCHO][ALTO];

    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            fread(matrizOriginal[x][y].pixel, sizeof(unsigned char), 3, imagenOriginal);
        }
    }

    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            matrizEspejada[x][y] = matrizOriginal[cabeceraOriginal.ancho - 1 - x][y];
        }
    }

    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            fwrite(matrizEspejada[x][y].pixel, sizeof(unsigned char), 3, nuevaImagen);
        }
    }

    fclose(imagenOriginal);
    fclose(nuevaImagen);

    return 0; // OK
}

int espejarImagenVertical(FILE* imagenOriginal, char* nombreNuevoArchivo)
{
    /*FILE* nuevaImagen = fopen(nombreNuevoArchivo, "wb");

    if(!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    t_metadata cabeceraOriginal, cabeceraNueva;

    leerCabecera(imagenOriginal, &cabeceraOriginal);

    escribirCabecera(imagenOriginal, nuevaImagen, cabeceraOriginal);

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;

    t_pixel matrizOriginal[anchoOriginal][altoOriginal];
    t_pixel matrizEspejada[anchoOriginal][altoOriginal];


    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            fread(matrizOriginal[x][y].pixel, sizeof(unsigned char), 3, imagenOriginal);
        }
    }

    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            matrizEspejada[x][y] = matrizOriginal[x][cabeceraOriginal.alto - y -1];
        }
    }

    for (int y = 0; y < cabeceraOriginal.alto; y++) {
        for (int x = 0; x < cabeceraOriginal.ancho; x++) {
            fwrite(matrizEspejada[x][y].pixel, sizeof(unsigned char), 3, nuevaImagen);
        }
    }

    fclose(nuevaImagen);
    return OK;*/
    FILE* nuevaImagen = fopen(nombreNuevoArchivo, "wb");

    if (!nuevaImagen)
        return ERROR_CREACION_ARCHIVO;

    t_metadata cabeceraOriginal;

    leerCabecera(imagenOriginal, &cabeceraOriginal);
    escribirCabecera(imagenOriginal, nuevaImagen, cabeceraOriginal);

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;


    t_pixel** matrizOriginal = malloc(sizeof(t_pixel*) * altoOriginal);
    t_pixel** matrizEspejada = malloc(sizeof(t_pixel*) * altoOriginal);

    for (int i = 0; i < altoOriginal; i++) {
        matrizOriginal[i] = malloc(anchoOriginal * sizeof(t_pixel));
        matrizEspejada[i] = malloc(anchoOriginal * sizeof(t_pixel));
    }

    for (int i = 0; i < altoOriginal; i++)
        fread(matrizOriginal[i], sizeof(t_pixel), anchoOriginal, imagenOriginal);


    for (int y = 0; y < altoOriginal; y++) {
        for (int x = 0; x < anchoOriginal; x++) {
            matrizEspejada[y][x] = matrizOriginal[altoOriginal - y - 1][x];
        }
    }

    for (int y = 0; y < altoOriginal; y++)
        fwrite(matrizEspejada[y], sizeof(t_pixel), anchoOriginal, nuevaImagen);


    for (int i = 0; i < altoOriginal; i++) {
        free(matrizOriginal[i]);
        free(matrizEspejada[i]);
    }

    free(matrizOriginal);
    free(matrizEspejada);

    fclose(nuevaImagen);

    return OK;
}
// Prototipos con matrices estáticas
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

int espejarHorizontal() {
    int n = 5, m = 4;

    int matriz[5][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16},
                        {18, 19, 20, 21}};

    int matrizEspejada[5][4] = {0};


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrizEspejada[i][j] = matriz[i][m - j - 1];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrizEspejada[i][j]);
        }
        printf("\n");
    }

    return 0;
}


int espejarVertical() {
    int n = 5, m = 4;

    int matriz[5][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16},
                        {17, 18, 19, 20}};

    int matrizEspejada[5][4] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrizEspejada[i][j] = matriz[n - 1 - i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrizEspejada[i][j]);
        }
        printf("\n");
    }

    return 0;
}

bool validarRango(int limiteInferior, int limiteSuperior, int valor)
{
    return (valor>=limiteInferior && valor<=limiteSuperior);
}

int obtenerParametro(char* argumento)
{
    char* pos = strrchr(argumento, '=') + 1;
    int num;

    if(pos)
    {
        sscanf(pos, "%d", &num);

        if(!validarRango(1,100,num))
        {
            printf("El parametro no esta dentro del rango aceptado.\n");
            return -2;
        }

        return num;
    }else
    {
        printf("No se encontro ningun parametro.\n");
        return -1;
    }
}


void concatenarMatrizVertical()
{
    int matrizA[4][5] = { {1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int matrizB[5][4] = { {10,11,12,13}, {10,11,12,13}, {10,11,12,13}, {10,11,12,13}, {10,11,12,13} };
    int matrizNueva[9][5];

    // Initialize matrizNueva with a default color value
    int filling = 0xffb3ff;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<5; j++)
        {
            matrizNueva[i][j] = filling;
        }
    }


    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            matrizNueva[i][j] = matrizA[i][j];
        }
    }

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<4; j++)
        {
            matrizNueva[i+4][j] = matrizB[i][j];
        }
    }

    // Print the resulting matrizNueva
    printf("Resultado de la matriz nueva (Vertical): \n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", matrizNueva[i][j]);
        }
        printf("\n");
    }
}

int concatenarMatrizHorizontal() {
    int matrizA[4][4] = { {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4} };
    int matrizB[4][5] = { {10,11,12,13,14}, {10,11,12,13,14}, {10,11,12,13,14}, {10,11,12,13,14} };
    int matrizNueva[4][9] = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrizNueva[i][j] = matrizA[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            matrizNueva[i][4 + j] = matrizB[i][j];
        }
    }

    printf("Resultado de la matriz nueva (horizontal): \n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", matrizNueva[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int concatenarImagenHorizontal()
{

    FILE* imagen1;
    FILE* imagen2;
    FILE* nueva;

    t_metadata cabeceraImagen1, cabeceraImagen2, cabeceraNueva;

    leerCabecera("unlam.bmp",&cabeceraImagen1);
    leerCabecera("dos.bmp",&cabeceraImagen2);

    imagen1 = fopen("unlam.bmp", "rb");
    imagen2 = fopen("dos.bmp", "rb");
    nueva = fopen("nueva.bmp", "wb");

    if(!imagen1 || !imagen2 || !nueva){
        return 324;
    }

    unsigned char byte[3];
    for(int i=0; i<cabeceraImagen1.comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, imagen1);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }

    t_pixel matrizImagen1[240][360];
    t_pixel matrizImagen2[240][360];
    t_pixel matrizImagenNueva[480][720];

    int mergedHeight = cabeceraImagen1.alto > cabeceraImagen2.alto ? cabeceraImagen1.alto : cabeceraImagen2.alto;
    int mergedWidth = cabeceraImagen1.ancho + cabeceraImagen2.ancho;

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            matrizImagenNueva[i][j].pixel[0] = 0xFF;
            matrizImagenNueva[i][j].pixel[1] = 0xC0;
            matrizImagenNueva[i][j].pixel[2] = 0xCB;
        }
    }

    for(int i=0; i<cabeceraImagen1.alto; i++)
    {
        for(int j=0; j<cabeceraImagen1.ancho; j++)
        {
            fread(&matrizImagen1[i][j].pixel, sizeof(unsigned char), 3, imagen1);
            matrizImagenNueva[i][j] = matrizImagen1[i][j];
        }
    }

    for(int i=0; i<cabeceraImagen2.alto; i++)
    {
        for(int j=0; j<cabeceraImagen2.ancho; j++)
        {
            fread(&matrizImagen2[i][j].pixel, sizeof(unsigned char), 3, imagen2);
            matrizImagenNueva[i][j + cabeceraImagen1.ancho] = matrizImagen2[i][j];
        }
    }

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            fwrite(&matrizImagenNueva[i][j].pixel, sizeof(unsigned char),3, nueva);
        }
    }

    fseek(nueva, 18, SEEK_SET);
    fwrite(&mergedWidth, sizeof(unsigned int), 1, nueva);
    fwrite(&mergedHeight, sizeof(unsigned int), 1, nueva);

    fclose(imagen1);
    fclose(imagen2);
    fclose(nueva);

    leerCabecera("nueva.bmp",&cabeceraNueva);
    return 0;
}

int concatenarImagenVertical()
{
    FILE* imagen1;
    FILE* imagen2;
    FILE* nueva;

    t_metadata cabeceraImagen1, cabeceraImagen2, cabeceraNueva;

    leerCabecera("unlam.bmp",&cabeceraImagen1);
    leerCabecera("dos.bmp",&cabeceraImagen2);

    imagen1 = fopen("unlam.bmp", "rb");
    imagen2 = fopen("dos.bmp", "rb");
    nueva = fopen("nueva.bmp", "wb");

    if(!imagen1 || !imagen2 || !nueva){
        return 324;
    }

    unsigned char byte[3];
    for(int i=0; i<cabeceraImagen1.comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, imagen1);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }

    t_pixel matrizImagen1[240][360];
    t_pixel matrizImagen2[240][360];
    t_pixel matrizImagenNueva[480][720];

    int mergedHeight = cabeceraImagen1.alto + cabeceraImagen2.alto;
    int mergedWidth = cabeceraImagen1.ancho > cabeceraImagen2.ancho ? cabeceraImagen1.ancho : cabeceraImagen2.ancho;

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            matrizImagenNueva[i][j].pixel[0] = 0xFF;
            matrizImagenNueva[i][j].pixel[1] = 0xC0;
            matrizImagenNueva[i][j].pixel[2] = 0xCB;
        }
    }

    for(int i=0; i<cabeceraImagen1.alto; i++)
    {
        for(int j=0; j<cabeceraImagen1.ancho; j++)
        {
            fread(&matrizImagen1[i][j].pixel, sizeof(unsigned char), 3, imagen1);
            matrizImagenNueva[i][j] = matrizImagen1[i][j];
        }
    }

    for(int i=0; i<cabeceraImagen2.alto; i++)
    {
        for(int j=0; j<cabeceraImagen2.ancho; j++)
        {
            fread(&matrizImagen2[i][j].pixel, sizeof(unsigned char), 3, imagen2);
            matrizImagenNueva[i + cabeceraImagen1.alto][j] = matrizImagen2[i][j];
        }
    }

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            fwrite(&matrizImagenNueva[i][j].pixel, sizeof(unsigned char),3, nueva);
        }
    }

    fseek(nueva, 18, SEEK_SET);
    fwrite(&mergedWidth, sizeof(unsigned int), 1, nueva);
    fwrite(&mergedHeight, sizeof(unsigned int), 1, nueva);

    fclose(imagen1);
    fclose(imagen2);
    fclose(nueva);

    leerCabecera("nueva.bmp",&cabeceraNueva);
    return 0;
}



#define WIDTH 360
#define HEIGHT 240

int pixelearImagen(FILE* imagenOriginal, char* nombreNuevoArchivo)
{
    FILE* nuevaImagen = fopen(nombreNuevoArchivo, "wb");
    if (!nuevaImagen)
        printf("Hubo un error al crear la imagen");
        return ERROR_CREACION_ARCHIVO;

    t_metadata cabeceraOriginal, cabeceraNueva;

    leerCabecera(imagenOriginal, &cabeceraOriginal);
    escribirCabecera(imagenOriginal, nuevaImagen, cabeceraOriginal);

    int anchoOriginal = cabeceraOriginal.ancho;
    int altoOriginal = cabeceraOriginal.alto;

    t_pixel** imagen = malloc(altoOriginal * sizeof(t_pixel*));
    t_pixel** matrizNuevaImagen = malloc(altoOriginal * sizeof(t_pixel*));

    for (int i = 0; i < altoOriginal; i++) {
        imagen[i] = malloc(anchoOriginal * sizeof(t_pixel));
        matrizNuevaImagen[i] = malloc(anchoOriginal * sizeof(t_pixel));
    }

    for (int i = 0; i < altoOriginal; i++) {
        fread(imagen[i], sizeof(t_pixel), anchoOriginal, imagenOriginal);
    }

    int n = 8;
    for (int i = 0; i < altoOriginal; i += n) {
        for (int j = 0; j < anchoOriginal; j += n) {
            unsigned long sumaR = 0, sumaG = 0, sumaB = 0;
            int acumuladorPixeles = 0;

            for (int k = 0; k < n && (i + k) < altoOriginal; k++) {
                for (int l = 0; l < n && (j + l) < anchoOriginal; l++) {
                    sumaR += imagen[i + k][j + l].pixel[0];
                    sumaG += imagen[i + k][j + l].pixel[1];
                    sumaB += imagen[i + k][j + l].pixel[2];
                    acumuladorPixeles++;
                }
            }

            unsigned char avgR = MIN(sumaR / acumuladorPixeles, 255);
            unsigned char avgG = MIN(sumaG / acumuladorPixeles, 255);
            unsigned char avgB = MIN(sumaB / acumuladorPixeles, 255);

            for (int k = 0; k < n && (i + k) < altoOriginal; k++) {
                for (int l = 0; l < n && (j + l) < anchoOriginal; l++) {
                    matrizNuevaImagen[i + k][j + l].pixel[0] = avgR;
                    matrizNuevaImagen[i + k][j + l].pixel[1] = avgG;
                    matrizNuevaImagen[i + k][j + l].pixel[2] = avgB;
                }
            }
        }
    }

    for (int i = 0; i < altoOriginal; i++) {
        fwrite(matrizNuevaImagen[i], sizeof(t_pixel), anchoOriginal, nuevaImagen);
    }

    for (int i = 0; i < altoOriginal; i++) {
        free(imagen[i]);
        free(matrizNuevaImagen[i]);
    }
    free(imagen);
    free(matrizNuevaImagen);

    fclose(nuevaImagen);

    return OK;
}



