#include "utils.h"

int cmpCodDepositos( void* c1, void* c2)
{
    Stock* s1 = c1;
    Stock* s2 = c2;


    return strcmp(s1->codDeposito, s2->codDeposito);
}

void imprimirCodDeposito(void* dato, void* params)
{
    Stock* s1 = dato;
    printf("(%s)\n", s1->codDeposito);
}

int cargarVectorCodDepositos(const char* nombreArch, tVector* v)
{
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch)
        return 0;

    Stock stock;

    while (fread(&stock, sizeof(Stock), 1, arch))
    {
        insertarElemOrdenadoVector(v, stock.codDeposito, cmpCodDepositos);
    }


    fclose(arch);
    return 1;
}

int   actualizarStocksDepositos(const char* nombreArchStocks, int** matrizMovimientos, tVector* vectorCodDepostios)
{
    FILE* archStocks = fopen(nombreArchStocks, "r+b");
    if(!archStocks)
        return 0;

    Stock stockTmp;
    while(fread(&stockTmp, sizeof(Stock), 1, archStocks))
    {
        int indiceDep = obtenerIndiceElemVector(vectorCodDepostios, stockTmp.codDeposito, cmpCodDepositos);

        for(int i=0; i<vectorCodDepostios->ce; i++)
        {
            stockTmp.stock-=matrizMovimientos[indiceDep][i];
            stockTmp.stock+=matrizMovimientos[i][indiceDep];
        }

        fseek(archStocks, -sizeof(Stock), SEEK_CUR);
        fwrite(&stockTmp, sizeof(Stock), 1, archStocks);
        fflush(archStocks);
    }

    fclose(archStocks);
    return 1;
}

void generarArchivoStocks(const char* nombreArchStocks)
{
    FILE* f = fopen(nombreArchStocks, "wb");
    if(!f)
        return;

    Stock stock[4] = { {"C", 200}, {"A", 400}, {"D", 100}, {"B",500} };

    for(int i=0; i<4; i++)
    {
        fwrite(&stock[i], sizeof(Stock), 1, f);
    }


    fclose(f);
    return;
}

void mostrarArchivoStocks(const char* nombreArchStock)
{
    FILE* f = fopen(nombreArchStock, "rb");
    if(!f)
        return;

    Stock sTmp;
    while(fread(&sTmp, sizeof(Stock), 1, f))
    {
        printf("%s %d\n", sTmp.codDeposito, sTmp.stock);
    }

    fclose(f);
}
