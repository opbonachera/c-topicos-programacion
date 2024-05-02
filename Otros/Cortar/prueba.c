
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct
{
    unsigned char pixel[3]; // ocupa 3 bytes

}t_pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;

void leerHeader(char[], t_metadata *);
void escribirImagen(unsigned int, unsigned int);
void aumentarColor( t_pixel *, int color);
void escalaDeGrises(t_pixel *);
void aumentarContraste(t_pixel *, int, int);
void invertirColores(t_pixel *);
void aumentarContraste(t_pixel *, int, int);

void ejecutarFunciones(const int, char *[], int);
void eliminarPrimerosDosCaracteres(char *);
int validarDevolver(char []);
int posicionBmp(const int, char *[]);

int main(int argc, char *argv[])
{
    int pos, arg;
    FILE *img;
    char nombreImg[256], nombreNueva[256];
    unsigned char byte;
    t_pixel px;
    t_metadata header;

    pos=posicionBmp(argc, argv);
    // Verifica y devuelve la posicion del archivo BMP
    if(pos==-1)
    {    printf("Existe mas de un archivo BMP");
        return 0;
    }
    else if (pos==0)
    { printf("No se encontro ningun archivo BMP")}
    strcpy(nombreImg, argv[pos]);
    printf("\n Nombre del archivo: %s \n", nombreImg);
    img=fopen(nombreImg, "rb");
    leerHeader(nombreImg, &header);
    for(int i = 1; i<argc; i++){
        if(i != pos){
            arg=validarDevolver(argv[i]);
            if(arg==-1)
            {
                printf("Argumento numero: %d, no existente\n", i);
            }
            else
            {
                eliminarPrimerosDosCaracteres(argv[i]);
                strcat(nombreNueva,"estudiante_");
                strcat(nombreNueva,argv[i]);
                strcat(nombreNueva,".bmp");
                printf("\n Nombre del archivo: %s \n", nombreNueva);
                FILE *nueva;
                nueva=fopen(nombreNueva, "wb");
                if (nueva == NULL) {
                    printf("Error al abrir el archivo de salida");
                    return -3;
                }
                fseek(img, 0, SEEK_SET);
                fseek(nueva, 0, SEEK_SET);
                for (int j=0; j<54;j++){
                    fread(&byte, sizeof(unsigned char), 1, img);
                    fwrite(&byte, sizeof(unsigned char), 1, nueva);
                }
                fseek(img, 54, SEEK_SET);
                fseek(nueva, 54, SEEK_SET);
                while (fread(&px.pixel, sizeof(unsigned char), 3, img)) {
                switch (arg) {
                    case 1:
                        invertirColores(&px);
                        break;
                    case 2:
                        //disminuirContraste(&px, min, max);
                        break;
                    case 3:
                        // Debes determinar los valores de min y max para aumentar contraste
                        //aumentarContraste(&px, min, max);
                        break;
                    case 4:
                        escalaDeGrises(&px);
                        break;
                    case 5:
                        //recortar imagen
                        break;
                    case 6:
                        aumentarColor(&px, 0);
                        break;
                    case 7:
                        aumentarColor(&px, 1);
                        break;
                    case 8:
                        aumentarColor(&px, 2);
                        break;
                    default:
                        break;
                }
                fwrite(&px.pixel, sizeof(unsigned char), 3, nueva);
            }

            fclose(nueva);
            }
            nombreNueva[0]='\0';
        }
    }
//    escribirImagen(240,360);

    fclose(img);
    printf("\n---------\n");
    return 0;
}

// Escritura de imagen
/*void escribirImagen(unsigned int width, unsigned int height) {
    FILE *img, *nueva;
    unsigned char byte;
    int i;
    img = fopen("unlam.bmp", "rb");//poner
    nueva = fopen("nueva.bmp","wb");


    if (img == NULL || nueva == NULL) {
        perror("Error opening file");
        return;
    }

    for (i=0; i<54;i++){
        fread(&byte, sizeof(unsigned char), 1, img);
        fwrite(&byte, sizeof(unsigned char), 1, nueva);
    }

    fclose(img);
    fclose(nueva);
}*/


//Lectura de cabecera
void leerHeader(char file[], t_metadata* header)
{
    FILE *img;

    img = fopen(file,"rb");


    printf("\n\n--------");
    printf("Filename: %s\n",file);

    fseek(img, 2, SEEK_SET);
    fread(&header->tamArchivo, sizeof(unsigned int), 1, img);

    fseek(img, 14, SEEK_SET);
    fread(&header->tamEncabezado, sizeof(unsigned int), 1, img);

    fseek(img, 10, SEEK_SET);
    fread(&header->comienzoImagen, sizeof(unsigned int), 1, img);

    fseek(img, 18, SEEK_SET);
    fread(&header->ancho, sizeof(unsigned int), 1, img);

    fseek(img, 22, SEEK_SET);
    fread(&header->alto, sizeof(unsigned int), 1, img);

    fseek(img, 28, SEEK_SET);
    fread(&header->profundidad, sizeof(unsigned short), 1, img);

    printf("Tamano de archivo: %u bytes\n", header->tamArchivo);
    printf("Tamano de cabecera: %u bytes\n", header->tamEncabezado);
    printf("Alto: %u bytes\n", header->alto);
    printf("Ancho: %u bytes\n", header->ancho);
    printf("Comienzo de imagen: byte %u\n", header->comienzoImagen);
    printf("Profundidad: %u bits\n", header->profundidad);

    fclose(img);
}

// Cambiar colores

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

void aumentarColor(t_pixel *px, int color)
{
    px->pixel[color]= MIN(255, ((int)px->pixel[color] + (px->pixel[color] / 2)));
}

int posicionBmp(const int argc, char *argv[])
{
    int cant=0, encontrado=0;
    char *extension;
    for (int i = 1; i < argc; i++) {

        // Verificar si el argumento termina con ".bmp" usando strrchr
        // strrchr devuelve un puntero a la última aparición de un carácter en una cadena
        // Aquí estamos buscando la última aparición de "." en el argumento
        extension = strrchr(argv[i], '.');

        // Si encontramos una extensión y es ".bmp", regresamos 1
        if (extension != NULL && strcmp(extension, ".bmp") == 0) {
            encontrado = i;
            cant++;
        }
    }
    if(cant > 1) encontrado =-1;
    return encontrado;
}

int validarDevolver(char arg[]){
    if(!strcmpi(arg, "--invertir-colores"))return 1;
    if(!strcmpi(arg, "--reducir-contraste")) return 2;
    if(!strcmpi(arg, "--aumentar-contraste")) return 3;
    if(!strcmpi(arg, "--escala-de-grises")) return 4;
    if(!strcmpi(arg, "--recortar-imagen")) return 5;
    if(!strcmpi(arg, "--tonalidad-azul")) return 6;
    if(!strcmpi(arg, "--tonalidad-verde")) return 7;
    if(!strcmpi(arg, "--tonalidad-roja")) return 8;
    return -1;
}

void eliminarPrimerosDosCaracteres(char *cadena) {
    size_t longitud = strlen(cadena);

    // Desplaza la cadena dos caracteres hacia la izquierda
    for (size_t i = 2; i <= longitud; i++) {
        cadena[i - 2] = cadena[i];
    }
}
