#include "funciones.h"

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
    void** matriz = malloc(filas * sizeof(void*));
    void** ult = matriz + filas - 1;

    if(!matriz)
    {
        printf("Error");
        return NULL;
    }

    for(void** f = matriz; f<=ult; f++)
    {
        *f = malloc(columnas* tamElem);

        if(!f)
        {
            destruirMatriz(matriz, matriz - f);
        }
    }

    return matriz;

}

void destruirMatriz(void** matriz, int n)
{
    void** ult = matriz + n - 1;

    for(void** p = matriz; p>= ult; p++)
    {
        free(*p);
    }

    free(matriz);
}

int copiarImagen(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);
    escribirImagen(imgSalida, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void espejarImagenHorizontal(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    for(int i=0; i<cabeceraEntrada.alto; i++)
    {
        for(int j=0; j<cabeceraEntrada.ancho; j++)
        {
            matrizSalida[i][cabeceraEntrada.ancho - j - 1] = matrizEntrada[i][j];
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.alto);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void achicarImagen(char* nombreImgEntrada, char* nombreImgSalida) {
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if (!imgEntrada) {
        printf("Ocurrió un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
        return;
    }

    if (!imgSalida) {
        printf("Ocurrió un error al abrir la imagen de salida.\n");
        fclose(imgEntrada);
        return;
    }

    Metadata cabeceraEntrada;


    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    float factorDecremento = 0.5;

    int nuevoAlto  = (int)(cabeceraEntrada.alto * factorDecremento);
    int nuevoAncho = (int)(cabeceraEntrada.ancho * factorDecremento);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(nuevoAlto, nuevoAncho, sizeof(Pixel));  // Matriz más pequeña

    modificarDimensiones(imgSalida, nuevoAncho, nuevoAlto);

    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);

    printf("original dimensions %dx%d\n", cabeceraEntrada.alto, cabeceraEntrada.ancho);
    printf("new dimensions %dx%d\n", nuevoAlto, nuevoAncho);
    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    int alRatio = cabeceraEntrada.alto / nuevoAlto;
    int anRatio = cabeceraEntrada.ancho / nuevoAncho;

    for (int i = 0; i < nuevoAlto; i++) {
        for (int j = 0; j < nuevoAncho; j++) {
            int nJ = (int)(j * anRatio);
            int nI = (int)(i * alRatio);

            matrizSalida[i][j] = matrizEntrada[nI][nJ];
        }
    }

    escribirImagen(imgSalida, matrizSalida, nuevoAlto, nuevoAncho);


    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, nuevoAlto);


    fclose(imgEntrada);
    fclose(imgSalida);

    return;
}

void espejarImagenVertical(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    for(int i=0; i<cabeceraEntrada.alto; i++)
    {
        for(int j=0; j<cabeceraEntrada.ancho; j++)
        {
            matrizSalida[i][j] = matrizEntrada[cabeceraEntrada.alto - i - 1][j];
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.alto);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void pixelearImagen(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;
    int n=4;
    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizTemporal = (Pixel**)crearMatriz(n,n,sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    for(int i=0; i<cabeceraEntrada.alto; i+=n)
    {
        for(int j=0; j<cabeceraEntrada.ancho; j+=n)
        {
            unsigned int sumaRojo=0, sumaVerde=0, sumaAzul=0;

            for(int k=0; k<n; k++)
            {
                for(int l=0; l<n; l++)
                {
                    sumaRojo  += matrizEntrada[k+i][l+j].px[0];
                    sumaVerde += matrizEntrada[k+i][l+j].px[1];
                    sumaAzul  += matrizEntrada[k+i][l+j].px[2];
                }
            }

            unsigned char prmRojo =  MIN(sumaRojo / (n * n), 255);
            unsigned char prmVerde = MIN(sumaVerde / (n * n), 255);
            unsigned char prmAzul =  MIN(sumaAzul / (n * n), 255);

            for(int k=0; k<n; k++)
            {
                for(int l=0; l<n; l++)
                {
                    matrizSalida[k+i][l+j].px[0] = prmRojo;
                    matrizSalida[k+i][l+j].px[1] = prmVerde;
                    matrizSalida[k+i][l+j].px[2] = prmAzul;
                }
            }
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.alto);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void rotarImagenDerecha(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.ancho, cabeceraEntrada.alto, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    for (int i = 0; i < cabeceraEntrada.alto; i++)
    {
        for (int j = 0; j < cabeceraEntrada.ancho; j++)
        {
             matrizSalida[cabeceraEntrada.ancho - j - 1][i] = matrizEntrada[i][j];
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.ancho, cabeceraEntrada.alto);

    modificarDimensiones(imgSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.ancho);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void comodin(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada; int n = 16;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizTemporal = (Pixel**)crearMatriz(n, n, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);


    for(int i=0; i<cabeceraEntrada.alto; i += n)
    {
        for(int j=0; j<cabeceraEntrada.ancho; j+= n)
        {

            for(int k=0; k<n; k++)
            {
                for(int l=0; l<n; l++)
                {

                     // matrizSalida[k+i][l+j] = matrizEntrada[k + i][j + l];
                     // transposed[filas - j - 1][i] = matrix[i][j];
                     // matrizSalida[cabeceraEntrada.ancho - j - 1][i] = matrizEntrada[i][j];

                     matrizSalida[j + k][(n - 1 - l) + i] = matrizEntrada[i + k][j + l];
                }
            }

        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.ancho);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void modificarContraste(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    float factor = 0.25;

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));

    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);
    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    unsigned char min, max;
    calcularMinMax(matrizEntrada, &min, &max, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    float contraste_actual = (max - min) / (float)(255);
    float nuevo_contraste = contraste_actual * .9;

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    for(int i=0; i<cabeceraEntrada.alto; i++)
    {
        for(int j=0; j<cabeceraEntrada.ancho; j++)
        {
            for(int k=0; k<3; k++)
            {
                unsigned char nuevo_valor = ((matrizEntrada[i][j].px[k] - min) * nuevo_contraste) / contraste_actual + min;
                matrizSalida[i][j].px[k] = (unsigned char)MAX(0, MIN(255, nuevo_valor));
            }
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void calcularMinMax(Pixel** matrizImagen, unsigned char* min, unsigned char* max, int filas, int columnas)
{
    unsigned char mn = 255, mx = 0;

    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
        {
            for (int k = 0; k < 3; k++)
                {
                    if (matrizImagen[i][j].px[k] < mn)
                        mn = MIN(matrizImagen[i][j].px[k], mn);
                    if (matrizImagen[i][j].px[k] > mx)
                        mx = MAX(matrizImagen[i][j].px[k], mx);
                }
        }
    }
    *min = mn, *max = mx;
}

void rotarImagenIzquierda(char* nombreImgEntrada, char* nombreImgSalida)
{
    FILE* imgEntrada = fopen(nombreImgEntrada, "rb");
    FILE* imgSalida = fopen(nombreImgSalida, "wb");

    if(!imgEntrada)
    {
        printf("Ocurrio un error al abrir la imagen de entrada.\n");
        fclose(imgSalida);
    }

    if(!imgSalida)
    {
        printf("Ocurrio un error al abrir la imagen de salida.\n");
        fclose(imgSalida);
    }

    Metadata cabeceraEntrada;

    leerCabecera(imgEntrada, &cabeceraEntrada);
    escribirCabecera(imgEntrada, imgSalida, &cabeceraEntrada);

    Pixel** matrizEntrada = (Pixel**)crearMatriz(cabeceraEntrada.alto, cabeceraEntrada.ancho, sizeof(Pixel));
    Pixel** matrizSalida = (Pixel**)crearMatriz(cabeceraEntrada.ancho, cabeceraEntrada.alto, sizeof(Pixel));

    fseek(imgSalida, cabeceraEntrada.comienzoImagen, SEEK_SET);
    fseek(imgEntrada, cabeceraEntrada.comienzoImagen, SEEK_SET);

    cargarImagen(imgEntrada, matrizEntrada, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    for (int i = 0; i < cabeceraEntrada.alto; i++)
    {
        for (int j = 0; j < cabeceraEntrada.ancho; j++)
        {
             matrizSalida[j][cabeceraEntrada.alto - i - 1] = matrizEntrada[i][j];
        }
    }

    escribirImagen(imgSalida, matrizSalida, cabeceraEntrada.ancho, cabeceraEntrada.alto);

    modificarDimensiones(imgSalida, cabeceraEntrada.alto, cabeceraEntrada.ancho);

    destruirMatriz((void**)matrizEntrada, cabeceraEntrada.alto);
    destruirMatriz((void**)matrizSalida, cabeceraEntrada.ancho);

    fclose(imgEntrada);
    fclose(imgSalida);

    return OK;
}

void modificarDimensiones(FILE* img, int nuevoX, int nuevoY)
{
    fseek(img, 18, SEEK_SET);
    fwrite(&nuevoX, sizeof(unsigned int), 1, img);
    fwrite(&nuevoY, sizeof(unsigned int), 1, img);
}

void escribirCabecera(FILE* img, FILE* nueva, Metadata* cabeceraOriginal)
{
    char bytes[cabeceraOriginal->comienzoImagen];

    fread(&bytes, sizeof(bytes), 1, img);
    fwrite(&bytes, sizeof(bytes), 1, nueva);
}

void escribirImagen(FILE* img, Pixel** matrizImagen, int filas, int columnas)
{
    for(size_t f = 0; f < filas; f++)
    {
        fwrite(matrizImagen[f], sizeof(Pixel), columnas, img);
    }
}

void cargarImagen(FILE* img, Pixel** matrizImagen, int filas, int columnas)
{
    for(size_t f = 0; f < filas; f++)
    {
        fread(matrizImagen[f], sizeof(Pixel), columnas, img);
    }
}

int leerCabecera(FILE* img, Metadata *cabecera)
{
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

    fseek(img, 0, SEEK_SET);
    return OK;
}
