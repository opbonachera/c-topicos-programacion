#include "archivos.h"

int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, TxtABin txtABin, size_t tamReg)
{
    FILE* archTxt=fopen(nomArchTxt, "r");
    if(!archTxt)
        return ERROR_ARCHIVO;

    FILE* archBin = fopen(nomArchBin, "wb");
    if(!archBin)
    {
        fclose(archTxt);
        return ERROR_ARCHIVO;
    }

    void* reg = malloc(tamReg);
    if(!reg)
    {
        fclose(archBin);
        fclose(archTxt);
        return ERROR_MEMORIA;
    }

    char linea[100];
    fgets(linea, 100, archTxt);
    while(!feof(archTxt))
    {
        txtABin(linea, reg);
        fwrite(reg, tamReg, 1, archBin);
        fgets(linea, 100, archTxt);
    }

    free(reg);
    fclose(archBin);
    fclose(archTxt);
    return OK;
}

void crearProductosCorBin(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if (!f) return;

    Producto productos[] = {
        {"COR001", "Placa madre ATX", 15450.75, 10},
        {"COR002", "Memoria DDR4 16GB", 12300.00, 25},
        {"COR003", "Disco SSD 1TB", 25600.50, 15}
    };

    fwrite(productos, sizeof(Producto), 3, f);
    fclose(f);
}

void crearProductosChuTxt(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wt");
    if (!f) return;

    fprintf(f, "%s|%s|%.2f|%d\n", "CHU003", "Fuente 600W", 9600.50, 20);
    fprintf(f, "%s|%s|%.2f|%d\n", "CHU004", "Microprocesador Ryzen", 45200.00, 12);
    fprintf(f, "%s|%s|%.2f|%d\n", "CHU002", "Gabinete gamer ATX", 18700.90, 5);
    fprintf(f, "%s|%s|%.2f|%d\n", "CHU003", "Fuente 600W", 9600.50, 20);

    fclose(f);
}

void crearClientesCorBin(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if (!f) return;

    Cliente clientes[] = {
        {102, "Gomez Laura"},
        {103, "Fernandez Matias"},
        {101, "Perez Julieta"},
        {101, "Perez Julieta"},
        {101, "Perez Julieta"},
    };

    fwrite(clientes, sizeof(Cliente), 5, f);
    fclose(f);
}

void crearClientesChuBin(const char* nombreArchivo)
{
    FILE* f = fopen(nombreArchivo, "wb");
    if (!f) return;

    Cliente clientes[] = {
        {203, "Munoz Ricardo"},
        {201, "Rojas Camila"},
        {201, "Rojas Camila"},
        {202, "Navarro Esteban"},
        {202, "Navarro Esteban"}
    };

    fwrite(clientes, sizeof(Cliente), 5, f);
    fclose(f);
}
