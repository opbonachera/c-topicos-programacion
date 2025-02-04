#include "indice.h"
#include "archivos.h"
#include "retorno.h"
#include "vector.h"



int generarIndice(const char* nomArch, const char* nomArchIndice)
{
    FILE* archivo = fopen(nomArch, "rb");

    if(!archivo)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    FILE* archivoIndice = fopen(nomArchIndice, "wb");
    if(!archivoIndice)
    {
        fclose(archivo);
        return ERROR_APERTURA_ARCHIVO;
    }

    Indice indice;
    Producto producto;
    int nroRegistro=0;

    fread(&producto, sizeof(Producto), 1, archivo);
    while(!feof(archivo))
    {
        indice.codigo = producto.codigo;
        indice.nroRegistro = nroRegistro;
        nroRegistro++;

        fwrite(&indice, sizeof(Indice), 1, archivoIndice);
        fread(&producto, sizeof(Producto), 1, archivo);
    }

    fclose(archivoIndice);
    fclose(archivo);

    return OK;
}

int mostrarIndice(const char* nomArchIndice)
{
    FILE* archivoIndice = fopen(nomArchIndice, "rb");

    if(!archivoIndice)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    Indice indice;
    fread(&indice, sizeof(indice), 1, archivoIndice);
    while(!feof(archivoIndice))
    {
        printf("Codigo: %d | Numero de Registro: %d\n", indice.codigo, indice.nroRegistro);
        fread(&indice, sizeof(indice), 1, archivoIndice);
    }

    fclose(archivoIndice);
    return OK;
}

int cmpIndice(void* e1, void* e2)
{
    const Indice* elemento1 = e1;
    const Indice* elemento2 = e2;

    return elemento1->codigo - elemento2->codigo;
}
