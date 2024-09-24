#include "binario.h"
#include <stdio.h>

int crearArchivoBinarioEjemplo(const char *ruta)
{
    FILE *fp = fopen(ruta,"wb");
    if(!fp)
        return ERROR;

    t_persona seruGiran[4] =
    {
        {10, "Pedro","Aznar", 10.1},
        {20, "Oscar","Moro", 8.1},
        {30, "David","Lebon", 50.1},
        {40, "Charly","Garcia", 40.1},
    };

    for(int i=0; i<4; i++)
    {
        fwrite(&seruGiran[i], sizeof(t_persona), 1, fp);
    }

    fclose(fp);
    return TODO_OK;
}
