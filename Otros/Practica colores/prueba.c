#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int crearImagen(char[], int);
int escribirCabecera(FILE *, FILE *, char[]);
int escribirDatos(FILE *, FILE *, char[]);
int validarDevolverFiltro(char[]);
int leerCabecera(t_metadata *);

int aplicarFiltro(t_pixel *, int, int, int);
void aumentarContraste(t_pixel *, int, int);
void disminuirContraste(t_pixel *, int, int);
void escalaDeGrises(t_pixel *);
void invertirColores(t_pixel *);

int main(int argc, char *argv[]) {


    int filtro = validarDevolverFiltro(argv[2]);

    if(filtro) crearImagen(argv[1], filtro);

    else printf("El filtro (%d) no es valido.\n", filtro);

    printf("Codigo del filtro: %d\n",filtro);

    return 0;
}

int crearImagen(char nombreArchivoOriginal[], int codFiltro) {
    FILE *original, *nueva;

    original = fopen(nombreArchivoOriginal, "rb");
    nueva = fopen("nueva.bmp", "wb");

    printf("Nombre imagen original: (%s)\n", nombreArchivoOriginal);
    printf("Codigo del filtro: (%d)\n", nombreFiltro);

    if (original == NULL || nueva == NULL) {
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    //escribirCabecera(original, nueva, codFiltro);
    //escribirDatos(original, nueva, codFiltro);

    fclose(original);
    fclose(nueva);

    return TODO_OK;
}

int escribirCabecera(FILE *original, FILE *nueva, char nombreFiltro[]) {
    t_metadata header;

    if (original == NULL || nueva == NULL) {
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    fseek(original, 0, SEEK_SET);

    fread(header, sizeof(unsigned char), 54, original);

    fwrite(header, sizeof(unsigned char), 54, nueva);

    return TODO_OK;
}

int leerCabecera(t_metadata *)
{

}

int escribirDatos(FILE *original, FILE *nueva, char nombreFiltro[]) {
    t_pixel px;

    unsigned char min_value = 255;
    unsigned char max_value = 0;

    fseek(original, 54, SEEK_SET);
    fseek(nueva, 54, SEEK_SET);

    while (fread(&px.pixel, sizeof(unsigned char), 3, original)) {

        if(! (strcmpi(nombreFiltro, "--aumentar-contraste") || (strcmpi(nombreFiltro, "--reducir-contraste")))){
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

int validarDevolverFiltro(char filtro[])
{
    if(!strcmpi(filtro, "--invertir-colores")) return 1;
    if(!strcmpi(filtro, "--reducir-contraste")) return 2;
    if(!strcmpi(filtro, "--aumentar-contraste")) return 3;
    if(!strcmpi(filtro, "--escala-de-grises")) return 4;
    if(!strcmpi(filtro, "--recortar-imagen")) return 5;
    return -1;
}

int aplicarFiltro(t_pixel* px, int codFiltro, int min_value, int max_value)
{
    switch(codFiltro)
    {
    case 1:
    case 2:
    case 3:
    }
    return 0;
}

void invertirColores(t_pixel *px)
{
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
    float nuevo_contraste = contraste_actual * 1.25;

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}

void disminuirContraste(t_pixel *px, int min, int max) {
    float contraste_actual = (max - min) / (float)(max + min);
    float nuevo_contraste = contraste_actual * 0.75;

    for(int i = 0; i < 3; i++) {
        int nuevo_valor = ((px->pixel[i] - min) * nuevo_contraste) / contraste_actual + min;
        px->pixel[i] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
    }
}
