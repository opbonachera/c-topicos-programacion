#include <stdio.h>
#include <stdlib.h>

#include "palabra.h"
#include "vector.h"

/* VERSION 1: Guardo las palabras con la cantidad de veces que aparecen DISTINTAS palabras con la misma longitud */

void procesarArchivo(const char* nombreArch, tVector* vPalabras);
void imprimirInt(void* e, void* params);
void imprimirPalabra(void* e1, void* params);
int cmpInt(const void* e1, const void* e2);
int cmpPalabras(const void* e1, const void* e2);
void escribirPalabrasLongMax(const char* nombreArch, tVector* vPalabras);

int main()
{
    tVector vPalabras;
    vectorInicializar(&vPalabras, sizeof(char[TAM_MAX_PALABRA]));

    procesarArchivo("palabras.txt", &vPalabras);

    escribirPalabrasLongMax("salida.txt", &vPalabras);
    vectorDestruir(&vPalabras);

    return 0;
}

void escribirPalabrasLongMax(const char* nombreArch, tVector* vPalabras)
{
    FILE* arch = fopen(nombreArch, "w");
    if(!arch)
        return;

    fprintf(arch, "Cantidad de apariciones de la palabra de longitud maxima: %d\n", vPalabras->ce);
    for(int i=0; i<vPalabras->ce; i++)
    {
        char* palabra = vPalabras->vec + (i * vPalabras->tamElem);
        fprintf(arch, "(%s)\n", palabra);
    }

    fclose(arch);
}

void procesarArchivo(const char* nombreArch, tVector* vPalabras)
{
    FILE* arch = fopen(nombreArch, "r");
    if(!arch)
        return;

    tSecPal  sPal;
    tPalabra pal;

    char linea[TAM_LINEA];
    while(fgets(linea, TAM_LINEA, arch))
    {
        tSecPalCrear(&sPal, linea);

        while(!tSecPalFin(&sPal))
        {
            tSecPalLeer(&sPal, &pal);

            if(vectorVacio(vPalabras))
                vectorInsEnOrden(vPalabras, &pal.palabra, cmpPalabras);

            else
            {
                char* ultPalabra   = (char*)vPalabras->vec + (vPalabras->ce - 1) * vPalabras->tamElem;

                int longUltPalabra = strlen(ultPalabra);
                int longPalabraAct = strlen(pal.palabra);

                if(longPalabraAct == longUltPalabra)
                    vectorInsEnOrden(vPalabras, &pal.palabra, cmpPalabras);

                else if(longPalabraAct > longUltPalabra)
                {
                    vectorVaciar(vPalabras);
                    vectorInsEnOrden(vPalabras, &pal.palabra, cmpPalabras);
                }
            }
        }


        tSecPalCerrar(&sPal);
    }
}

int cmpInt(const void* e1, const void* e2)
{
    return *(const int*)e1 - *(const int*)e2;
}

void imprimirInt(void* e, void* params)
{
    printf("[%d]\n", *(int*)e);
}


int cmpPalabras(const void* e1, const void* e2)
{
    const char* p1 = e1;
    const char* p2 = e2;

    return strcmp(p1, p2);
}

void imprimirPalabra(void* e1, void* params)
{
    char* palabra = e1;
    printf("(%s)", palabra);
}
