#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned char px[3];
}pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tamaño del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;

int main()
{
    FILE* img;
    FILE* nueva;

    t_metadata cabeceraOriginal;

    img = fopen("unlam.bmp","rb");
    nueva = fopen("nueva.bmp", "wb");

    pixel imgNueva[408][412];
    pixel imgOriginal[360][240];

    leerCabecera("unlam.bmp",&cabeceraOriginal);

    unsigned char byte[3];
    for(int i=0; i<cabeceraOriginal.comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, img);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }

    fseek(nueva, 138, SEEK_SET);
    for(int i=0; i<360;i++)
    {
        for(int j=0; j<240; j++)
        {
            fread(&imgOriginal[i][j].px, sizeof(unsigned char), 3, img);
            fwrite(&imgOriginal[i][j].px, sizeof(unsigned char), 3, nueva);
        }
    }

    fclose(img);
    fclose(nueva);
    return 0;
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
