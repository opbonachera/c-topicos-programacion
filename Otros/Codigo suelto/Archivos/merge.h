#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#include <stdio.h>
#include "persona.h"

#define MERGE_ERROR_A 1
#define MERGE_ERROR_B 2
#define MERGE_ERROR_SALIDA 3

void combinarArchivos(FILE *fpA,
                      FILE *fpB,
                      FILE *fpSal);

void fusionarArchivos(const char *pathA,
                      const char *pathB,
                      const char *pathSalida);

#endif // MERGE_H_INCLUDED
