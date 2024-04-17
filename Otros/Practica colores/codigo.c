#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned char pixel[3];
    unsigned int profundidad;  // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos s�lo 24 bits.
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
void escribirHeader(char[], char[]);

int main()
{
    escribirHeader("unlam.bmp","nueva.bmp");

    leerHeader("unlam.bmp");
    leerHeader("nueva.bmp");
    escribirImagen(240,360);

    return 0;
}


void escribirImagen(unsigned int width, unsigned int height) {
    FILE *img, *nueva;

    img = fopen("unlam.bmp", "rb");
    nueva = fopen("nueva.bmp","wb");

    t_pixel px;
    t_metadata header;

    if (img == NULL || nueva == NULL) {
        perror("Error opening file");
        return;
    }

    // Copy pixel data with padding
    int rowSize = width * sizeof(t_pixel);
    int padding = (4 - (rowSize % 4)) % 4; // Calculate padding
    unsigned char paddingData[3] = {0}; // Padding data is always zero
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fread(&px, sizeof(t_pixel), 1, img);
            fwrite(&px, sizeof(t_pixel), 1, nueva);
        }
        fwrite(paddingData, 1, padding, nueva); // Write padding
    }

    fclose(img);
    fclose(nueva);
}

void escribirHeader(char vieja[], char nuevaImg[])
{
    FILE *img;
    FILE *nueva;

    t_metadata header;

    img = fopen(vieja, "rb");
    nueva = fopen(nuevaImg,"wb");

    if(img == NULL || nueva == NULL){
        printf("Error al abrir el archivo. \n");
        exit(1);
    }

    fseek(img, 2, SEEK_SET);
    fread(&header.tamArchivo, sizeof(unsigned int), 1, img);
    fseek(img, 2, SEEK_SET);
    fwrite(&header.tamArchivo,sizeof(unsigned int),1,nueva);

    fseek(img, 14, SEEK_SET);
    fread(&header.tamEncabezado, sizeof(unsigned int), 1, img);
    fseek(nueva, 14, SEEK_SET);
    fwrite(&header.tamEncabezado,sizeof(unsigned int),1,nueva);

    fseek(img, 10, SEEK_SET);
    fread(&header.comienzoImagen, sizeof(unsigned int), 1, img);
    fseek(nueva, 10, SEEK_SET);
    fwrite(&header.comienzoImagen,sizeof(unsigned int),1,nueva);

    fseek(img, 18, SEEK_SET);
    fread(&header.ancho, sizeof(unsigned int), 1, img);
    fseek(nueva, 18, SEEK_SET);
    fwrite(&header.ancho,sizeof(unsigned int),1,nueva);

    fseek(img, 22, SEEK_SET);
    fread(&header.alto, sizeof(unsigned int), 1, img);
    fseek(nueva, 22, SEEK_SET);
    fwrite(&header.alto,sizeof(unsigned int),1,nueva);

    fseek(img, 28, SEEK_SET);
    fread(&header.profundidad, sizeof(unsigned short), 1, img);
    fseek(nueva, 28, SEEK_SET);
    fwrite(&header.profundidad,sizeof(unsigned int),1,nueva);

    fclose(img);
    fclose(nueva);
}

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


