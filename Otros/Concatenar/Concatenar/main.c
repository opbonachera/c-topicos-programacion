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
    concatenarImagenVertical();
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

    pixel matrizImagen1[240][360];
    pixel matrizImagen2[240][360];
    pixel matrizImagenNueva[480][720];

    int mergedHeight = cabeceraImagen1.alto + cabeceraImagen2.alto;
    int mergedWidth = cabeceraImagen1.ancho > cabeceraImagen2.ancho ? cabeceraImagen1.ancho : cabeceraImagen2.ancho;

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            matrizImagenNueva[i][j].px[0] = 0xFF;
            matrizImagenNueva[i][j].px[1] = 0xC0;
            matrizImagenNueva[i][j].px[2] = 0xCB;
        }
    }

    for(int i=0; i<cabeceraImagen1.alto; i++)
    {
        for(int j=0; j<cabeceraImagen1.ancho; j++)
        {
            fread(&matrizImagen1[i][j].px, sizeof(unsigned char), 3, imagen1);
            matrizImagenNueva[i][j] = matrizImagen1[i][j];
        }
    }

    for(int i=0; i<cabeceraImagen2.alto; i++)
    {
        for(int j=0; j<cabeceraImagen2.ancho; j++)
        {
            fread(&matrizImagen2[i][j].px, sizeof(unsigned char), 3, imagen2);
            matrizImagenNueva[i + cabeceraImagen1.alto][j] = matrizImagen2[i][j];
        }
    }

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            fwrite(&matrizImagenNueva[i][j].px, sizeof(unsigned char),3, nueva);
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

    pixel matrizImagen1[240][360];
    pixel matrizImagen2[240][360];
    pixel matrizImagenNueva[480][720];

    int mergedHeight = cabeceraImagen1.alto > cabeceraImagen2.alto ? cabeceraImagen1.alto : cabeceraImagen2.alto;
    int mergedWidth = cabeceraImagen1.ancho + cabeceraImagen2.ancho;

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            matrizImagenNueva[i][j].px[0] = 0xFF;
            matrizImagenNueva[i][j].px[1] = 0xC0;
            matrizImagenNueva[i][j].px[2] = 0xCB;
        }
    }

    for(int i=0; i<cabeceraImagen1.alto; i++)
    {
        for(int j=0; j<cabeceraImagen1.ancho; j++)
        {
            fread(&matrizImagen1[i][j].px, sizeof(unsigned char), 3, imagen1);
            matrizImagenNueva[i][j] = matrizImagen1[i][j];
        }
    }

    for(int i=0; i<cabeceraImagen2.alto; i++)
    {
        for(int j=0; j<cabeceraImagen2.ancho; j++)
        {
            fread(&matrizImagen2[i][j].px, sizeof(unsigned char), 3, imagen2);
            matrizImagenNueva[i][j + cabeceraImagen1.ancho] = matrizImagen2[i][j];
        }
    }

    for(int i = 0; i < mergedHeight; i++)
    {
        for(int j = 0; j < mergedWidth; j++)
        {
            fwrite(&matrizImagenNueva[i][j].px, sizeof(unsigned char),3, nueva);
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

int copiarImagen()
{
    FILE* img;
    FILE* nueva;

    t_metadata cabeceraOriginal, cabeceraNueva;

    leerCabecera("unlam.bmp",&cabeceraOriginal);

    img = fopen("unlam.bmp","rb");
    nueva = fopen("nueva.bmp", "wb");

    pixel imgOriginal[360][240];

    unsigned char byte[3];
    for(int i=0; i<cabeceraOriginal.comienzoImagen;i++){
        fread(&byte, sizeof(unsigned char), 1, img);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }

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

    leerCabecera("nueva.bmp",&cabeceraNueva);
}
