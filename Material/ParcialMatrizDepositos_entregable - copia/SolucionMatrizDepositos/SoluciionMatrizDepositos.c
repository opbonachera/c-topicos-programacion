#include "SolucionMatrizDepositos.h"

#include <stdlib.h>
#include <stdio.h>

void generarStocks(const char* nombreStocks)
{
    Stock stocks[6] = {
        {"A", 150},
        {"B", 300},
        {"C", 120},
        {"D", 250},
        {"A", 180},
        {"B", 210}
    };

    FILE* archivo = fopen(nombreStocks, "wb");

    if(!archivo)
    {
        printf("No se pudo crear el archivo");
        return;
    }

    fwrite(&stocks, sizeof(Stock), sizeof(stocks) / sizeof(Stock), archivo);

    fclose(archivo);
}

void generarMovimientos(const char* nombreMovimientos)
{
     Movimiento movimientos[6] =
     {
        {"A", "B", 50},
        {"C", "D", 30},
        {"A", "C", 70},
        {"D", "A", 90},
        {"B", "C", 40},
        {"A", "D", 60}
    };

    FILE* archivo = fopen(nombreMovimientos, "wb");

    if(!archivo)
    {
        printf("No se pudo crear el archivo");
        return;
    }

    fwrite(&movimientos, sizeof(Movimiento), sizeof(movimientos) / sizeof(Movimiento), archivo);

    fclose(archivo);
}
void mostrarStocks(const char* nombreStocks)
{
    FILE* archivo = fopen(nombreStocks, "rb");

    if(!archivo)
    {
        return;
    }

    fseek(archivo, 0L, SEEK_END);
    int cantReg = ftell(archivo) / sizeof(Stock);

    Stock stock;
    fseek(archivo, 0, SEEK_SET);
    for(int i=0; i<cantReg; i++)
    {
        fread(&stock, sizeof(Stock), 1, archivo);
        printf("Cod depo: %s | Stock: %d\n", stock.codDeposito, stock.stock);
    }

    return;
}
void mostrarMovimientos(const char* nombreMovimientos)
{
    FILE* archivo = fopen(nombreMovimientos, "rb");
    if(!archivo)
    {
        return;
    }

    Movimiento movimiento;
    printf("\n");
    fread(&movimiento, sizeof(Movimiento), 1, archivo);
    while(!feof(archivo))
    {
        printf("Cod Dep Origen: %s | Cod Dep Destino: %s | Stock: %d\n", movimiento.depOrigen, movimiento.depDestino, movimiento.cantidad);
        fread(&movimiento, sizeof(Movimiento), 1, archivo);
    }

    fclose(archivo);
    return;
}

//int actualizarDepositos(const char* nombreArchivoStocks, const char* nombreArchivoMovimientos);
int crearVectorCodigosDepositos(const char* nombreStocks, Vector* codigosDepositos)
{
    // Existe un vector de stocks con los depositos que hay y su stock
    // Hacer un vector que asigne
}

void inicializarMatrizEnCero(int** matMovDeps, int filas, int columnas)
{
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
        {
            matMovDeps[i][j] = 0;
        }
    }
}

int cargarMatrizMovimientosDepositos(const char* nombreMovimientos, int** matMovDeps, Vector* codigosDepositos)
{
    int tempMatrix[4][4] = {
        {0, 50, 30, 20},
        {10, 0, 200, 40},
        {15, 25, 0, 0},
        {75, 10, 0, 0}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matMovDeps[i][j] = tempMatrix[i][j];
        }
    }

    return 0;
}

//int procesarMatrizMovimientosDepositosActualizandoStocks(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks);

int cmpCodDep(const void* e1, const void* e2)
{
    const CodigoDeposito* d1 = e1;
    const CodigoDeposito* d2 = e2;

    return d1->codDeposito - d2->codDeposito;
}
