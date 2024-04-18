#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM_PIXEL 3

int main() {
    FILE *entrada, *salida;
    unsigned char pixel[TAM_PIXEL], byte, pixelRojo[TAM_PIXEL]={255,0,0};
    unsigned int ancho, alto;
    int cantPixeles, i;

    entrada = fopen("unlam.bmp", "rb");
    salida = fopen("imagen_clonada.bmp", "wb");
    if (salida == NULL || entrada == NULL) {
        perror("Error al abrir un archivo\n");
        return 1;
    }
    //no importa
    fseek(entrada, 18, SEEK_SET);
    fread(&ancho, sizeof(unsigned int), 1, entrada);
    fread(&alto, sizeof(unsigned int), 1, entrada);
    cantPixeles = ancho*alto;
    printf("ancho de la imagen: %d\n",ancho);
    printf("alto de la imagen: %d\n",alto);
    printf("cantidad de pixeles: % d", cantPixeles);

    //vuelvo a la posicion 0 para que no empiece a copiar los datos mal
    fseek(entrada, 0, SEEK_SET);

    //copio solo la parte de datos (hasta byte 40 inclusive)(no copio pixeles)
    for (i=0; i<54;i++){
        fread(&byte, sizeof(unsigned char), 1, entrada);
        printf("%d",&byte);
        fwrite(&byte, sizeof(unsigned char), 1, salida);
    }
    //me posiciono en la posicion que empiezan los pixeles
    fseek(entrada, 54, SEEK_SET);
    fseek(salida, 54, SEEK_SET);

    //por cada pixel del archivo inicial pego un pixel rojo en el archivo final, (pixel rojo declarado arriba)
    while (fread(pixel, sizeof(unsigned char), TAM_PIXEL, entrada)) {
        //pixel[2] = fmin((pixel[2] += (unsigned char)( ((float)pixel[2]) * 0.5f )), 255);
        fwrite(pixelRojo, sizeof(unsigned char), TAM_PIXEL, salida);
    }

    fclose(entrada);
    fclose(salida);

    printf("La imagen ha sido clonada exitosamente.\n");
    printf("%d", fmin(1,2));

    return 0;
}


