#include "prueba.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "TDA.h"


int Procesar_lote_texto(const char *nom_Arch)
{
    char linea[MAXLINE];
    TDA_Vector buffer;
    FILE *file = fopen(nom_Arch,"rt");
    if(!file)
        return 0;
    ///pedir espacio para las palabra
    if(!TDA_Construir(&buffer,sizeof(tPalabras)))
    {
        fclose(file);
        return 0;
    }
    ///inicio del procesamiento
    while(fgets(linea,MAXLINE-1,file))
    {
        EliminarSalto_linea(linea);
        TrozarLinea(linea,&buffer);
    }
    TDA_sort(&buffer,Mas_frecuente);
    TDA_10_mas_frecuentes(&buffer);
    TDA_map(&buffer,Mostrar_palabra);
    TDA_Destruir(&buffer);
    fclose(file);
    return 1;
}

void EliminarSalto_linea(char *linea)
{
    char *salto = linea+strlen(linea)-1;
    if(*salto=='\n')
        *salto = '\0';
}

char* Copia_cadena(char *cad_destino, const char *cad_origen, unsigned bytes)
{
    char *ini = cad_destino;
    int i = 0;
    while(i<bytes && *cad_origen)
    {
        *cad_destino = *cad_origen;
        cad_destino++;
        cad_origen++;
        i++;
    }
    *cad_destino='\0';
    return ini;
}

void Mostrar_palabra(void *info)
{
    tPalabras *buffer = (tPalabras*)info;
    printf("%s %d\n", buffer->palabra, buffer->cant_apariciones);
}

int Comparar_cadenas(const void *a, const void *b)
{
    char *p_a = (char*)a;
    char *p_b = (char*)b;
    return strcmpi(p_a,p_b);
}

int Mas_frecuente(const void *a, const void *b)
{
    tPalabras *p_a = (tPalabras*)a;
    tPalabras *p_b = (tPalabras*)b;
    return (p_a->cant_apariciones>p_b->cant_apariciones) ? 1 : 0;
}

int Intercambio_generico(void *a, void *b, unsigned tamanio)
{
    char *p_a = (char*)a;
    char *p_b = (char*)b;
    char aux;
    int i;
    for(i=0;i<tamanio;i++)
    {
        aux = *p_a;
        *p_a = *p_b;
        *p_b = aux;
        p_a++;
        p_b++;
    }
    return 1;
}
