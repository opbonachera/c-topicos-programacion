#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char pixel[3]; // ocupa 3 bytes
} t_pixel;

typedef struct {
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tamaño del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
} t_metadata;

int leerCabecera(FILE*, t_metadata*);
void escribirCabecera(FILE*, t_metadata);

int main() {
    FILE* original = fopen("unlam.bmp","rb");
    FILE* nueva = fopen("nueva.bmp","wb");

    t_metadata cabeceraOriginal, cabeceraNueva;
    t_pixel px;

    unsigned char mOriginal[300][207] = {0};

    leerCabecera(original, &cabeceraOriginal);
    copiarCabecera(&cabeceraOriginal, &cabeceraNueva);
    // cabeceraNueva.alto=cabeceraOriginal.ancho;
    // cabeceraNueva.ancho=cabeceraOriginal.alto;
    escribirCabecera(nueva, cabeceraNueva);

    if (!original || !nueva) {
        printf("Error opening files\n");
        return 1;
    }

    fseek(original, 54, SEEK_SET);
    fseek(nueva, 54, SEEK_SET);

    while( (fread(&px.pixel, sizeof(unsigned char), 3, original)) )
    {
        fwrite(&px.pixel, sizeof(unsigned char), 3, nueva);
    }

    fclose(original);
    fclose(nueva);

}

void escribirCabecera(FILE *nueva, t_metadata cabecera) {

    fseek(nueva, 0, SEEK_SET);
    fwrite(&cabecera, sizeof(unsigned char), 54, nueva);

}

int copiarCabecera(t_metadata *cabeceraOriginal, t_metadata *cabeceraNueva)
{
    cabeceraNueva->tamArchivo = cabeceraOriginal->tamArchivo;
    cabeceraNueva->alto = cabeceraOriginal->alto;
    cabeceraNueva->ancho = cabeceraOriginal->ancho;
    cabeceraNueva->tamEncabezado = cabeceraOriginal->tamEncabezado;
    cabeceraNueva->profundidad = cabeceraOriginal->profundidad;
}

int leerCabecera(FILE* file, t_metadata* cabecera)
{
    printf("\n\n--------");

    fseek(file, 2, SEEK_SET);
    fread(&cabecera->tamArchivo, sizeof(unsigned int), 1, file);

    fseek(file, 14, SEEK_SET);
    fread(&cabecera->tamEncabezado, sizeof(unsigned int), 1, file);

    fseek(file, 10, SEEK_SET);
    fread(&cabecera->comienzoImagen, sizeof(unsigned int), 1, file);

    fseek(file, 18, SEEK_SET);
    fread(&cabecera->ancho, sizeof(unsigned int), 1, file);

    fseek(file, 22, SEEK_SET);
    fread(&cabecera->alto, sizeof(unsigned int), 1, file);

    fseek(file, 28, SEEK_SET);
    fread(&cabecera->profundidad, sizeof(unsigned short), 1, file);

    /*printf("Tamaño de archivo: %u bytes\n", cabecera->tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", cabecera->tamEncabezado);
    printf("Alto: %u bytes\n", cabecera->alto);
    printf("Ancho: %u bytes\n", cabecera->ancho);
    printf("Comienzo de imagen: byte %u\n", cabecera->comienzoImagen);
    printf("Profundidad: %u bits\n", cabecera->profundidad);*/

    return 0;
}
