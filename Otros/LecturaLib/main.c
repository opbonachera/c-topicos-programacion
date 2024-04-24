#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escribirImagen(char,char);

int main(int argc, char *argv[])
{
    int i;
    char arg[100];

    for(i=1; i<argc; i++)
    {
        if(strcmpi("₋₋invertir-colores", argv[i]))
            printf("Invirtiendo colores de imagen...");
            break;

        if(strcmpi("₋₋aumentar-contraste", argv[i]))
            printf("IAumentando contraste de imagen...");
            break;

        if(strcmpi("₋₋reducir-contraste", argv[i]))
            printf("Reduciendo contraste de la imagen...");
            break;

        if(strcmpi("--tonalidad-azul", argv[i]))
            printf("Tonalizando de azul la imagen...");
            break;
    }





    return 0;
}

void escribirImagen(char filtro, char fileName)
{
    printf("Convirtendo la imagen %d a... %s", fileName, filtro);
}
