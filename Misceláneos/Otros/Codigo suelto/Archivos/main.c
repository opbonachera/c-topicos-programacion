#include <stdio.h>
#include "binario.h"

int main()
{
    // Transformamos  el archivo binario a texto
    if(crearArchivoBinarioEjemplo(ARCH_BIN)== ERROR)
        return ERROR;

    FILE *fpOrigen = fopen(ARCH_BIN, "rb");
    FILE *fpDestino = fopen(ARCH_TXT, "wt");

    if(!fpOrigen || !fpDestino)
    {
        fclose(fpOrigen);
        fclose(fpDestino);
        return ERROR;
    }


    t_persona persona;
    fread(&persona, sizeof(t_persona),1,fpOrigen);

    while(!feof(fpOrigen))
    {
        fread(&persona, sizeof(t_persona),1,fpOrigen);
        fprintf(fpDestino, "%d_%s_%s_%.2f\n",persona.legajo, persona.apellido, persona.nombre, persona.sueldo);
        printf("Leyendo: legajo (%s_%s_%d)\n", persona.nombre, persona.apellido,persona.legajo);
    }
    printf("Todo bien.\n");
    return TODO_OK;
}
