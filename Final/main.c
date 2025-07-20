#include <stdio.h>
#include <string.h>

int main()
{
    char linea[100] = "ORNELLAA.PAULA.BONACHEERA.ORIANA.SOL.BONACHERA.DIEGO.FLOR.GILDA\n";

    char* act = strchr(linea, '\n');
    *act='\0';
    printf("(%s)", linea);

    char* punto = strrchr(linea, '.');
    while(punto)
    {
        printf("(%s)\n", punto + 1);
        *punto = '\0';
        punto = strrchr(linea, '.');
    }

    printf("(%s)\n", linea);
    return 0;
}
