#include "archivos.h"
#include "estructuras.h"

int leerArchivo(char* nombreArchivo, Imprimir imprimir)
{
    FILE* archivo = fopen(nombreArchivo, "rb");

    if(!archivo)
    {
        printf("Ocurrio un error al leer el archivo.");
        return ERROR_LECTURA_ARCHIVO;
    }

    imprimir(archivo);

    fclose(archivo);

    return 0;
}

void imprimirLibro(FILE* archivoLibros)
{
    Libro libro;

    fread(&libro, sizeof(Libro), 1, archivoLibros);
    while(!feof(archivoLibros))
    {
        printf("Codigo %s \t| CodigoSocio %s \t| Cantidad %d\t |\n", libro.codigo, libro.nombre, libro.cantidad);
        fread(&libro, sizeof(Libro), 1, archivoLibros);
    }

    fseek(archivoLibros, 0, SEEK_SET);
}


void imprimirMovimiento(FILE* archivoMovimientos)
{
    MovLibro movimiento;

    fread(&movimiento, sizeof(MovLibro), 1, archivoMovimientos);
    while(!feof(archivoMovimientos))
    {
        printf("Codigo libro: %s | Cantidad: %d\n", movimiento.codigoLibro, movimiento.cantidad);
        fread(&movimiento, sizeof(MovLibro), 1, archivoMovimientos);
    }

    fseek(archivoMovimientos, 0, SEEK_SET);

}

int  archivoTextoABinario(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin)
{
    FILE* archivoTxt= fopen(nomArchTxt, "rb");
    FILE* archivoBin = fopen(nomArchBin, "wb");

    int ret = OK;
    char linea[500];

    void* reg = malloc(tamReg);

    if(!reg)
    {
        fclose(archivoBin);
        fclose(archivoTxt);
        return ERROR_RESERVA_MEMORIA;
    }

    fgets(linea, 500, archivoTxt);
    while(!feof(archivoTxt) && !esErrorFatal(ret))
    {
        ret = txtABin(linea, reg);

        if(ret == OK)
        {
            fwrite(reg, tamReg, 1, archivoBin);
        }

        fgets(linea, 500, archivoTxt);
    }

    free(reg);

    fclose(archivoTxt);
    fclose(archivoBin);

    return OK;
}

bool esErrorFatal(int ret)
{
    if(ret == ERROR_LINEA_LARGA)
    {
        return true;
    }

    return false;
}

int movimientoTxtVarABin(char* linea, void* reg)
{
    MovLibro* mov = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERROR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchr(linea, '|');
    strcpy(mov->codigoSocio, act + 1);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%d", &mov->cantidad);

    *act = '\0';
    strcpy(mov->codigoLibro, linea);

    return OK;
}

int compararCodigoMovimiento(const void* e1, const void* e2)
{
    MovLibro* movimiento1 = e1;
    MovLibro* movimiento2 = e2;

    return strcmp(movimiento1->codigoLibro, movimiento2->codigoLibro);
}

int compararCodigoLibro(void* e1, void* e2)
{
    Libro* elemento1 = e1;
    Libro* elemento2 = e2;

    return strcmp(elemento1->codigo, elemento2->codigo);
}


int actualizarArchivoLibros(const char* nomArchLibros, const char* nomArchMovimientos)
{
    FILE* archivoLibros = fopen(nomArchLibros, "rb");

    if(!archivoLibros)
    {
        return ERROR_LECTURA_ARCHIVO;
    }

    FILE* archivoMovimientos = fopen(nomArchMovimientos, "rb");
    if(!archivoMovimientos)
    {
        fclose(archivoLibros);
        return ERROR_LECTURA_ARCHIVO;
    }

    // Leo un movimiento
    // Leo un libro
    // Comparo sus codigos. Si son iguales, resto la cantidad del movimiento en la cantidad del libro.
    MovLibro movimiento;
    Libro libro;

    fread(&movimiento, sizeof(MovLibro), 1, archivoMovimientos);
    fread(&libro, sizeof(Libro), 1, archivoLibros);
    while(!feof(archivoMovimientos) && !feof(archivoLibros))
    {
        int comp = strcmpi(movimiento.codigoLibro, libro.codigo);

        // Si la comparacion  es 0 restar la cantidad
        // Si la comparacion  es menor, movimiento>libro leer
        // Si la compracacion es menor, movimiento<libro

        fread(&movimiento, sizeof(MovLibro), 1, archivoMovimientos);
        fread(&libro, sizeof(Libro), 1, archivoLibros);
    }

    return OK;
}

int ordenarArchivo(const char* nomArch, size_t tamReg)
{
    FILE* archivo = fopen(nomArch, "rb");

    if(!archivo)
    {
        return ERROR_LECTURA_ARCHIVO;
    }

    //vectorCrearDeArchivo(&);

}
