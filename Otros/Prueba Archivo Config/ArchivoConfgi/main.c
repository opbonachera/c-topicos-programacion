#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

int main() {
    FILE* archivo = fopen("filtros.conf", "rb");

    if (!archivo) {
        printf("Hubo un error al abrir el archivo.\n");
        return 1;
    }

    char linea[256];


    while (fgets(linea, sizeof(linea), archivo)) {

        char* act = strchr(linea, '\n');

        if (!act)
        {
            return 2; // ERROR_LINEA_LARGA
        }

        *act = '\0';

        char* filtro = linea;
        char* parametro = strchr(linea, '=');

        if (parametro)
        {
            *parametro = '\0';
        }
    }
    fclose(archivo);
    return 0;
}
