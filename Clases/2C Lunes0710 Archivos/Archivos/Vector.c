#include "Vector.h"

bool vectorDeArchivo(Vector* vector, size_t tamElemento, const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(!archivo)
    {
        printf("Ocurrio un error al abrir el archivo.\n");
        return ERROR_APERTURA_ARCHIVO;
    }

    // Se posiciona el puntero al final del archivo y se divide esa cantidad por el tamaño del elemento
    fseek(archivo, 0L, SEEK_END);
    int cantRegistros = ftell(archivo) / tamElemento;

    vector->v = malloc( cantRegistros * tamElemento);

    if(!vector->v)
    {
        printf("Ocurrio un error al reservar memoria.");
        return ERROR_RESERVA_MEMORIA;
    }

    // Se devuelve el puntero al inicio del archivo
    rewind(arch);

    fread(vector->v, tamElemento, cantRegistros, archivo);
    
    vector->ce  = cantRegistros;
    vector->cap = cantRegistros;
    vector->tamElemento = tamElemento;

    return true;
}

int compararEnteros(void* e1, void* e2)
{
    int* int1 = e1;
    int* int2 = e2;

    return int1 - int2;
}

int buscarVectorOrdenado(Vector* vector, void* elemento, Cmp cmp)
{
    void* ult = vector->ve + (vector->ce - 1) * vector->tamElemento; // Último elemento del vector
    void* posActual = vector->ve; // Primer elemento del vector

    while (posActual <= ult && cmp(elemento, posActual) > 0)
    {
        posActual += vector->tamElemento;
    }

    if (posActual > ult || cmp(elemento, posActual) != 0)
    {
        return -1; // Elemento no encontrado
    }

    memcpy(elemento, posActual, vector->tamElemento);

    return (posActual - vector->ve) / vector->tamElemento; 
}