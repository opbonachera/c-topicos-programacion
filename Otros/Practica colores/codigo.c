#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct
{
    unsigned char pixel[3]; // ocupa 3 bytes

}t_pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;

void leerHeader(char[]);
void escribirImagen(unsigned int, unsigned int);

void escalaDeGrises(t_pixel *);
void aumentarContraste(t_pixel *);
void invertirColores(t_pixel *);
void disminuirContraste(t_pixel *);

int main()
{
    t_pixel px;


    escribirImagen(240,360);

    leerHeader("unlam.bmp");
    leerHeader("nueva.bmp");

    printf("\n---------\n");

    printf("tamaño de px.pixel: %zu bytes\n", sizeof(px.pixel)); // 3 bytes
    printf("tamaño de px: %zu bytes\n", sizeof(px)); // 8 bytes

    return 0;
}

// Escritura de imagen
void escribirImagen(unsigned int width, unsigned int height) {
    FILE *img, *nueva;
    unsigned char byte[3];

    img = fopen("unlam.bmp", "rb");
    nueva = fopen("nueva.bmp","wb");

    t_pixel px;
    t_metadata header;


    if (img == NULL || nueva == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i=0; i<54;i++){
        fread(&byte, sizeof(unsigned char), 1, img);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }
    int intensity ;

    fseek(img, 54, SEEK_SET);
    fseek(nueva, 54, SEEK_SET);

     while (fread(&px.pixel, sizeof(unsigned char), 3, img)) {

        intensity= MAX(px.pixel[1], px.pixel[0]);

        fwrite(&px.pixel, sizeof(unsigned char), 3, nueva);
    }

    printf("Min value: %d", intensity);

    fclose(img);
    fclose(nueva);
}

//Lectura de cabecera
void leerHeader(char file[])
{
    FILE *img;
    t_metadata header;

    img = fopen(file,"rb");


    printf("\n\n--------");
    printf("Filename: %s\n",file);

    fseek(img, 2, SEEK_SET);
    fread(&header.tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&header.tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&header.comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&header.ancho, sizeof(unsigned int), 1, img);

    fseek(img, 22, SEEK_SET);
    fread(&header.alto, sizeof(unsigned int), 1, img);

    fseek(img, 28, SEEK_SET);
    fread(&header.profundidad, sizeof(unsigned short), 1, img);

    printf("Tamaño de archivo: %u bytes\n", header.tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", header.tamEncabezado);
    printf("Alto: %u bytes\n", header.alto);
    printf("Ancho: %u bytes\n", header.ancho);
    printf("Comienzo de imagen: byte %u\n", header.comienzoImagen);
    printf("Profundidad: %u bits\n", header.profundidad);

    fclose(img);
}

// Cambiar colores

void invertirColores(t_pixel *px)
{
    //printf("%d\n", px->pixel[0]);
    // *px es la direccion de memoria donde se encuentra guardada la estructura px de tipo t_pixel que definimos en el main
    px->pixel[0] = (unsigned char)(~px->pixel[0]);
    px->pixel[1] = (unsigned char)(~px->pixel[1]);
    px->pixel[2] = (unsigned char)(~px->pixel[2]);
}

void escalaDeGrises(t_pixel *px)
{
    float promedio = ((px->pixel[0] + px->pixel[1] + px->pixel[2]) / 3);

    px->pixel[0] = (unsigned char)(promedio);
    px->pixel[1] = (unsigned char)(promedio);
    px->pixel[2] = (unsigned char)(promedio);
}

void aumentarContraste(t_pixel *px)
{
    px->pixel[0] = (unsigned char)(px->pixel[0] + (px->pixel[0] >> 2));
    px->pixel[1] = (unsigned char)(px->pixel[1] + (px->pixel[1] >> 2));
    px->pixel[2] = (unsigned char)(px->pixel[2] + (px->pixel[2] >> 2));
}

void disminuirContraste(t_pixel *px)
{

    px->pixel[0] = (unsigned char)(px->pixel[0] - (px->pixel[0] >> 2));
    px->pixel[1] = (unsigned char)(px->pixel[1] - (px->pixel[1] >> 2));
    px->pixel[2] = (unsigned char)(px->pixel[2] - (px->pixel[2] >> 2));
}

