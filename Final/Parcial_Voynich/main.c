#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef struct
{
    char palabra[100];
    int frecuencia;
}tPalabraFrecuencia;

int contieneSignoInterrogacion_ALU(const char* palabra);
int obtenerFrecuenciaManuscrito(FILE* arch, tVector* vector);

void imprimirInt(void* dato, void* params)
{
    printf("[%d]", *(int*)dato);
}

int cmpInt(const void* e1, const void* e2)
{
    return *(int*)e1 - *(int*)e2;
}

int cmpPalabraFrecuencia(const void* e1, const void* e2)
{
    const tPalabraFrecuencia* p1 = e1;
    const tPalabraFrecuencia* p2 = e2;

    return strcmp(p1->palabra, p2->palabra);
}

void imprimirPalabraFrecuencia(void* dato, void* params)
{
    tPalabraFrecuencia* f = dato;
    printf("Frecuencia [%d] | Palabra (%s)\n",f->frecuencia, f->palabra);
}
int main()
{
    tVector vector;

    vectorInicializar(&vector, sizeof(tPalabraFrecuencia));

    obtenerFrecuenciaManuscrito(NULL, &vector);

    vectorRecorrer(&vector, NULL, imprimirPalabraFrecuencia);
    vectorDestruir(&vector);
    return 0;
}

int obtenerFrecuenciaManuscrito(FILE* arch, tVector* vector)
{
    char linea[] = "VAS92.9FAE.9FAE.9FAE.AR.APAM.ZOE.ZOR9.QOR92.9.FOR.ZOE89\n";

        char palabra[200];

        char* finPalabra = linea + strlen(linea); // apunta al '\0'

        char* act = strrchr(linea, '\n');
        if(*act) *act='\n';

        act = &linea[strlen(linea) - 2];
        while (act >= linea - 1)
        {
            if (act < linea || *act == '.')
            {
                char* inicioPalabra = act + 1;
                size_t len = finPalabra - inicioPalabra;

                strncpy(palabra, inicioPalabra, len);
                palabra[len] = '\0';

                if (!contieneSignoInterrogacion_ALU(palabra))
                {
                    tPalabraFrecuencia busq;
                    strcpy(busq.palabra, palabra);
                    int indicePalabraBusq = vectorBusquedaBinaria(vector, &busq, cmpPalabraFrecuencia);

                    if(indicePalabraBusq != -1)
                    {
                        tPalabraFrecuencia* enc = (tPalabraFrecuencia*)obtenerElementoEnIndiceVector(vector, indicePalabraBusq);
                        enc->frecuencia++;

                    }else{
                        tPalabraFrecuencia ins;
                        ins.frecuencia=1;
                        strcpy(ins.palabra, palabra);
                        vectorInsertarElemOrdenado(vector, &ins, cmpPalabraFrecuencia);
                    }
                }

                finPalabra = act;
            }
            act--;
        }

    return OK;
}

int contieneSignoInterrogacion_ALU(const char* palabra)
{
    while (*palabra && *palabra != '.')
    {
        if (*palabra == '?')
            return 1;
        palabra++;
    }
    return 0;
}
