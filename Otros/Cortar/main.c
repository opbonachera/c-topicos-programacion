#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char pixel[3]; // Assumes each pixel is represented by 3 bytes
} t_pixel;

typedef struct {
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int comienzoImagen;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
} t_metadata;

int leerCabecera(FILE*, t_metadata*);
void escribirCabecera(FILE*, t_metadata);
void copiarCabecera(t_metadata *cabeceraOriginal, t_metadata *cabeceraNueva); // Changed return type to void

#define HEADER_SIZE 54 // Explicitly define header size

int main() {
    FILE* original = fopen("kitty.bmp","rb");
    FILE* nueva = fopen("nueva.bmp","wb");

    t_metadata cabeceraOriginal, cabeceraNueva;

    if (!original || !nueva) {
        printf("Error opening files\n");
        return 1;
    }

    unsigned char mOriginal[300][207] = {0}; // This should be dynamically allocated, but I'm skipping it as per your request

    leerCabecera(original, &cabeceraOriginal);
    copiarCabecera(&cabeceraOriginal, &cabeceraNueva);
    // cabeceraNueva.alto=cabeceraOriginal.ancho;
    // cabeceraNueva.ancho=cabeceraOriginal.alto;
    escribirCabecera(nueva, cabeceraNueva);

    fseek(nueva, HEADER_SIZE, SEEK_SET); // Use HEADER_SIZE instead of hardcoded value
    fseek(original, HEADER_SIZE, SEEK_SET);

    for(int i = 0; i < 207; i++) {
        for(int j = 0; j < 300; j++) {
            if (fread(&mOriginal[i][j], sizeof(unsigned char), 3, original) != 3) {
                printf("Error reading pixel data from original file\n");
                return 1;
            }
            if (fwrite(&mOriginal[i][j], sizeof(unsigned char), 3, nueva) != 3) {
                printf("Error writing pixel data to new file\n");
                return 1;
            }
        }
    }

    fclose(original);
    fclose(nueva);
    return 0;
}

void escribirCabecera(FILE *nueva, t_metadata cabecera) {
    fseek(nueva, 0, SEEK_SET);
    fwrite(&cabecera, sizeof(unsigned char), HEADER_SIZE, nueva); // Use HEADER_SIZE instead of hardcoded value
}

void copiarCabecera(t_metadata *cabeceraOriginal, t_metadata *cabeceraNueva) {
    cabeceraNueva->tamArchivo = cabeceraOriginal->tamArchivo;
    cabeceraNueva->alto = cabeceraOriginal->alto;
    cabeceraNueva->ancho = cabeceraOriginal->ancho;
    cabeceraNueva->tamEncabezado = cabeceraOriginal->tamEncabezado;
    cabeceraNueva->profundidad = cabeceraOriginal->profundidad;
}

int leerCabecera(FILE* file, t_metadata* cabecera) {
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

    return 0;
}
