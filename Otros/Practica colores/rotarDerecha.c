#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int comienzoImagen;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
} t_metadata;

typedef struct {
    unsigned char pixel[3];
} t_pixel;

void escribirCabecera(FILE *, FILE *, t_metadata*);
void leerHeader(FILE *, t_metadata *);

int main() {
    t_metadata metadata;
    t_pixel px;

    FILE *original = fopen("unlam.bmp", "rb");
    FILE *nueva = fopen("neuvisima.bmp", "wb");

    if (original == NULL || nueva == NULL) {
        printf("Error al abrir los archivos.");
        return 1;
    }

    leerHeader(original, &metadata);
    escribirCabecera(original, nueva, &metadata);

    metadata.alto = 360; // Interchange alto and ancho for rotation
    metadata.ancho = 240;

    fseek(original, metadata.comienzoImagen, SEEK_SET);
    fseek(nueva, metadata.comienzoImagen, SEEK_SET);

    unsigned char mcopia[240][360][3]; // Interchange 360 and 240
    unsigned char moriginal[240][360][3];

    for(int i = 0; i < metadata.alto; i++) {
        for(int j = 0; j < metadata.ancho; j++) {
            fread(&moriginal[i][j], sizeof(unsigned char), 3, original);
        }
    }

    for(int i = 0; i < metadata.ancho; i++) {
        for(int j = 0; j < metadata.alto; j++) {
            fwrite(&moriginal[j][i], sizeof(unsigned char),3, nueva);
        }
    }

    printf("Imagen copiada y rotada correctamente.\n");

    fclose(original);
    fclose(nueva);

    return 0;
}

void leerHeader(FILE *archivo, t_metadata *metadata) {
    fseek(archivo, 2, SEEK_SET);
    fread(&metadata->tamArchivo, sizeof(unsigned int), 1, archivo);
    fseek(archivo, 10, SEEK_SET);
    fread(&metadata->comienzoImagen, sizeof(unsigned int), 1, archivo);
    fseek(archivo, 18, SEEK_SET);
    fread(&metadata->ancho, sizeof(unsigned int), 1, archivo);
    fseek(archivo, 22, SEEK_SET);
    fread(&metadata->alto, sizeof(unsigned int), 1, archivo);
}

void escribirCabecera(FILE *original, FILE *nueva, t_metadata *metadata) {
    unsigned char byte[54];

    fseek(original, 0, SEEK_SET);

    fread(byte, sizeof(unsigned char), 54, original);

    // Actualizar el ancho y el alto en la cabecera
    byte[18] = metadata->ancho & 0xFF;
    byte[19] = (metadata->ancho >> 8) & 0xFF;
    byte[20] = (metadata->ancho >> 16) & 0xFF;
    byte[21] = (metadata->ancho >> 24) & 0xFF;
    byte[22] = metadata->alto & 0xFF;
    byte[23] = (metadata->alto >> 8) & 0xFF;
    byte[24] = (metadata->alto >> 16) & 0xFF;
    byte[25] = (metadata->alto >> 24) & 0xFF;

    fwrite(byte, sizeof(unsigned char), 54, nueva);


}
