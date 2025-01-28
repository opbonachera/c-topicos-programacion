#include "Vector.h"
#include "archivos.h"
bool vectorDeArchivo(Vector* vector, size_t tamElemento, const char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(!archivo)
    {
        printf("Ocurrio un error al abrir el archivo.\n");
        return 2;
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
    rewind(archivo);

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
    void* ult = vector->v + (vector->ce - 1) * vector->tamElemento; // Último elemento del vector
    void* posActual = vector->v; // Primer elemento del vector

    while (posActual <= ult && cmp(elemento, posActual) > 0)
    {
        posActual += vector->tamElemento;
    }

    if (posActual > ult || cmp(elemento, posActual) != 0)
    {
        return -1; // Elemento no encontrado
    }

    memcpy(elemento, posActual, vector->tamElemento);

    return elemento;
}

int buscarVectorOrdenadoBin(Vector* vector, void* elemento, size_t inicio, size_t fin, Cmp cmp)
{
    if (inicio <= fin)
    {

        size_t mitad_idx = inicio + (fin - inicio) / 2;
        void* mitad = (char*)vector->v + mitad_idx * vector->tamElemento;

        int comparison = cmp(elemento, mitad);

        if (comparison == 0)
        {
            return mitad_idx;
        }
        else if (comparison < 0)
        {
            return buscarVectorOrdenadoBin(vector, elemento, inicio, mitad_idx - 1, cmp);
        }
        else
        {
            return buscarVectorOrdenadoBin(vector, elemento, mitad_idx + 1, fin, cmp);
        }
    }

    return -1;
}

int compararIndiceProducto(IndiceProducto* prod1, IndiceProducto* prod2)
{
    IndiceProducto* indp1 = prod1;
    IndiceProducto* indp2 = prod2;

    return indp1->codigo - indp2->codigo;
}
