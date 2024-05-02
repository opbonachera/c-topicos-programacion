/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Bonachera
    Nombre: Ornella
    DNI: 46119546
    Entrega:
    -----------------
    Apellido: Pityla
    Nombre: Damian
    DNI:
    Entrega:
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "constantes.h"
#include "estructuras.h"

#include <stdlib.h>
#include <stdio.h>

int solucion(int argc, char* argv[])
{
/*
    Aquí deben hacer el código que solucione lo solicitado.
    Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
*/
    return TODO_OK;
}

int crearImagen()
{
    t_metadata cabeceraNuevo, cabeceraOriginal;
    t_pixel px;


    FILE *archivoNuevo = fopen("nueva.bmp", "wb");

    if (archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    leerCabecera("unlam.bmp", &cabeceraOriginal);

    escribirCabecera(archivoNuevo);

    //modificarDimensiones(archivoNuevo, cabeceraOriginal.alto, cabeceraOriginal.ancho);

    escribirDatos(archivoNuevo);

    leerCabecera("nueva.bmp", &cabeceraNuevo);

    fclose(archivoNuevo); // Close the file at the end

    return 0;
}


int escribirCabecera(FILE *archivoNuevo)
{
    // Copia TODOS los datos de la cabecera del archivo original al nuevo
    FILE *archivoOriginal;

    archivoOriginal = fopen("unlam.bmp","rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    unsigned char byte[3];

    for (int i=0; i<54;i++){
        fread(&byte, sizeof(unsigned char), 1, archivoOriginal);
        fwrite(&byte, sizeof(unsigned char), 1, archivoNuevo);
    }

    fclose(archivoOriginal);

    return 0;
}

int escribirDatos(FILE *archivoNuevo)
{
    // Escribe los pixeles que componen la imagen
    t_pixel px;

    FILE *archivoOriginal;

    archivoOriginal = fopen("unlam.bmp","rb");

    if (archivoOriginal == NULL || archivoNuevo == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(archivoOriginal, 54, SEEK_SET);
    fseek(archivoNuevo, 54, SEEK_SET);

    t_pixel imagen[360][240];
    // Read and write pixel data directly
    for(int i = 0; i < 360; i++) {
        for(int j = 0; j < 240; j++) {
            fread(&imagen[i][j], sizeof(unsigned char), 3, archivoOriginal);
            fwrite(&imagen[i][j], sizeof(unsigned char), 3, archivoNuevo);
        }
    }

    fclose(archivoOriginal);
    return 0;
}

int modificarDimensiones(FILE *file, unsigned int w, unsigned int h)
{
    fseek(file, 18, SEEK_SET);
    fwrite(&w, sizeof(unsigned int), 1, file);

    fseek(file, 22, SEEK_SET);
    fwrite(&h, sizeof(unsigned int), 1, file);

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

    printf("Tamaño de archivo: %u bytes\n", cabecera->tamArchivo);
    printf("Tamaño de cabecera: %u bytes\n", cabecera->tamEncabezado);
    printf("Alto: %u bytes\n", cabecera->alto);
    printf("Ancho: %u bytes\n", cabecera->ancho);
    printf("Comienzo de imagen: byte %u\n", cabecera->comienzoImagen);
    printf("Profundidad: %u bits\n", cabecera->profundidad);

    fclose(img);
    return 0;
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

    //Si es mayor q1ue 255 poner en 255 y si es menor poner en 0
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
