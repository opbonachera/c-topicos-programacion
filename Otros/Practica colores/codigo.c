#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned char pixel[3];
    // unsigned int profundidad;  // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos s�lo 24 bits.
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

void leerHeader();
void printBmp(unsigned int, unsigned int);
void printNumbers();

int main()
{
    leerHeader();
    printBmp(240,360);
    printNumbers();

    return 0;
}


void printBmp(unsigned int alto, unsigned int ancho) {
    FILE *img, *nueva;
    img = fopen("unlam.bmp", "rb");
    nueva = fopen("nueva.bmp","wb");
    t_pixel px;
    t_metadata header;

    if (img == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(img, 54, SEEK_SET);

    fseek(img, 2, SEEK_SET);
    fread(&header.tamArchivo, sizeof(unsigned int), 1, img);
    fwrite(&header.tamArchivo, sizeof(unsigned int),1, nueva);

    fseek(img, 14, SEEK_SET);
    fread(&header.tamEncabezado, sizeof(unsigned int), 1, img);
    fwrite(&header.tamEncabezado, sizeof(unsigned int),1, nueva);

    fseek(img, 10, SEEK_SET);
    fread(&header.comienzoImagen, sizeof(unsigned int), 1, img);
    fwrite(&header.comienzoImagen, sizeof(unsigned int),1, nueva);

    fseek(img, 18, SEEK_SET);
    fread(&header.ancho, sizeof(unsigned int), 1, img);
    fread(&header.alto, sizeof(unsigned int), 1, img);
    fwrite(&header.ancho, sizeof(unsigned int),1, nueva);
    fwrite(&header.alto, sizeof(unsigned int),1, nueva);

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fread(&px.pixel, sizeof(px.pixel), 1, img);
            fwrite(&px.pixel, sizeof(px.pixel), 1, nueva);
        }
    }

    fclose(img);
    fclose(nueva);
}

void printNumbers()
{
    unsigned char arr[3] = {0xFF, 0x32, 0x99};

    for(int i = 0; i < 1 ; i++)
    {
        printf("Positive: %x\n", arr[i]);// 1111 1111 for 0xff 0000 0000
        printf("Negative: %x\n", (unsigned char)~arr[i]); // 0011 0010 for 0x32 1100 1101

        printf("Moved by two: %x \n", arr[1] >> 2);
    }
}

void leerHeader()
{
    FILE *img;
    t_metadata header;

    img = fopen("unlam.bmp", "rb");

    if(img == NULL){
        printf("Error al abrir el archivo. \n");
        exit(1);
    }

    fseek(img, 2, SEEK_SET);
    fread(&header.tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&header.tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&header.comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&header.ancho, sizeof(unsigned int), 1, img);
    fread(&header.alto, sizeof(unsigned int), 1, img);

    printf("Tamaño de archivo: %u bytes\n", header.tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", header.tamEncabezado);
    printf("Alto: %u bytes\n", header.alto);
    printf("Ancho: %u bytes\n", header.ancho);
}
