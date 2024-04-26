#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TODO_OK 0
#define ARCHIVO_NO_ENCONTRADO 10
#define NO_SE_PUEDE_CREAR_ARCHIVO 20

#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))

typedef struct {
    unsigned char pixel[3];
} t_pixel;

typedef struct {
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int comienzoImagen;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
} t_metadata;

int crearImagen(char[], char[]);
int escribirCabecera(FILE *, FILE *, char[]);
int escribirDatos(FILE *, FILE *, char[]);

void aplicarFiltro(t_pixel *, char[], int, int);
void aumentarContraste(t_pixel *, int, int);

int main() {
    crearImagen("unlam.bmp", "nueva.bmp");
    return 0;
}

int crearImagen(char nombreArchivo[], char nombreFiltro[]) {
    FILE *original, *nueva;
    original = fopen(nombreArchivo, "rb");
    nueva = fopen(nombreFiltro, "wb");

    if (original == NULL || nueva == NULL) {
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    escribirCabecera(original, nueva, nombreFiltro);
    escribirDatos(original, nueva, nombreFiltro);

    fclose(original);
    fclose(nueva);

    return TODO_OK;
}

int escribirCabecera(FILE *original, FILE *nueva, char nombreFiltro[]) {
    unsigned char byte[54]; // Assuming BMP header size is 54 bytes

    if (original == NULL || nueva == NULL) {
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    fseek(original, 0, SEEK_SET);

    fread(byte, sizeof(unsigned char), 54, original);

    fwrite(byte, sizeof(unsigned char), 54, nueva);

    return TODO_OK;
}

int escribirDatos(FILE *original, FILE *nueva, char nombreFiltro[]) {
    t_pixel px;

    unsigned char min_value = 255;
    unsigned char max_value = 0;

    fseek(original, 54, SEEK_SET);
    fseek(nueva, 54, SEEK_SET);

    while (fread(&px.pixel, sizeof(unsigned char), 3, original)) {

        if(! (strcmpi(nombreFiltro, "--aumentar-contraste") || (strcmpi(nombreFiltro, "--reducir-contraste") ){
            for (int i = 0; i < 3; i++)
            {
                if (px.pixel[i] < min_value) { min_value = MIN(px.pixel[i], min_value); }
                if (px.pixel[i] > max_value) { max_value = MAX(px.pixel[i], min_value); }
            }
        }
        aplicarFiltro(&px, nombreFiltro, min_value, max_value);

        fwrite(&px.pixel, sizeof(unsigned char), 3, nueva);
    }

    return TODO_OK;
}

int aplicarFiltro(t_pixel &px, char nombreFiltro[], int min_value, int max_value)
{
    if(!strcmpi(nombreFiltro, "--aumentar-contraste"))
    {
        aumentarContraste(px, min_value, max_value);
        return TODO_OK;
    }

    if(!strcmpi(nombreFiltro, "--reducir-contraste"))
    {
        aumentarContraste(px, min_value, max_value);
        return TODO_OK;
    }

    if(!strcmpi(nombreFiltro, "--invertir-colores"))
    {
        invertirColores(px, min_value, max_value);
        return TODO_OK;
    }

    if(!strcmpi(nombreFiltro, "--escala-de-grises"))
    {
        escalaDeGrises(px, min_value, max_value);
        return TODO_OK;
    }
}

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

void aumentarContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 1.25; // Aumentar en un 25%

    // Aplicar la transformación a cada canal de color
    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}

void disminuirContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 0.75; // Disminuir en un 25%

    // Aplicar la transformación a cada canal de color
    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}
