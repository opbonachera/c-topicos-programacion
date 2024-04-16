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

void leerHeader();
void printBmp();

int main()
{
    leerHeader();
    printBmp();
    return 0;
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

void printBmp(unsigned int alto, unsigned int ancho) {
    FILE *img;
    img = fopen("unlam.bmp", "rb");

    if (img == NULL) {
        perror("Error opening file");
        return;
    }

    t_pixel px;
    fseek(img, 54, SEEK_SET);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fread(&px.pixel, sizeof(px.pixel), 1, img);
            printf("%x, %x, %x\n",px.pixel[0], px.pixel[1], px.pixel[2]);
            // AcA SE PODRIA ESCRIBIR
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            fread(&px.pixel, sizeof(px.pixel), 1, img);
            printf("%x, %x, %x\n",px.pixel[0], px.pixel[1], px.pixel[2]);
        }
    }
    fclose(img);
}

void printNumbers()
{
    unsigned char arr[3] = {0xFF, 0x32, 0x99};

    for(int i = 0; i < 3 ; i++)
    {
        printf("Positive: %x\n", arr[i]);// 1111 1111 for 0xff 0000 0000
        printf("Negative: %x\n", (unsigned char)~arr[i]); // 0011 0010 for 0x32 1100 1101

        printf("Moved by two: %x \n", arr[1] >> 2);
    }
}
