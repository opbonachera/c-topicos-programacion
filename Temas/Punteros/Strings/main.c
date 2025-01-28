#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"

int main()
{
    char str[] = "ornneLla pAUla";
    char ornella[] = "ornella";

    imprimirCadena(&str);
    normalizarCadena(&str, &str);
    imprimirCadena(&str);

    printf("resultado: %d\n", compararCadenas( &ornella, &str ));
    return 0;
}
