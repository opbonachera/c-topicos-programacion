//#include "merge.h"
//
//void fusionarArchivos(const char *pathA,
//                      const char *pathB,
//                      const char *pathSalida)
//{
//    FILE *fpA;
//    FILE *fpB;
//    FILE *fpSalida;
//
//    fpA = fopen(pathA, "rb");
//    fpB = fopen(pathB, "rb");
//    fpSalida = fopen(pathSalida, "rb");
//
//    if(!fpA)
//    {
//        printf("Falla apertura de archivo(%s)", pathA);
//        fprintf("Falla apertura de archivo(%s)", pathA);
//        return MERGE_ERROR_A;
//    }
//
//    if(!fpB)
//    {
//        fclose(fpA);
//        printf("Falla apertura de archivo(%s)", pathA);
//        fprintf("Falla apertura de archivo(%s)", pathA);
//        return MERGE_ERROR_B;
//    }
//
//    if(!fpSalida)
//    {
//        fclose(fpA);
//        fclose(fpB);
//        printf("Falla apertura de archivo(%s)", pathA);
//        fprintf("Falla apertura de archivo(%s)", pathA);
//        return MERGE_ERROR_SALIDA;
//    }
//
//    combinarArchivos(fpA, fpB, fpSalida);
//    fclose(fpA);
//    fclose(fpB);
//    fclose(fpSalida);
//}
//
//void combinarArchivos(FILE *fpA,
//                      FILE *fpB,
//                      FILE *fpSal)
//{
//    tPersona datoA;
//    tPersona datoB;
//
//    fread(&datoA, sizeof(tPersona),1, fpA);
//    fread(&datoB, sizeof(tPersona),1, fpB);
//
//    long posA = ftell(fpA);
//    rewind(fpA);
//    long posB = ftell(fpB);
//    rewind(fpB);
//    // Volvemos al principio del archivo para asegurarnos de que estamos en el principio del archivo
//    while(!feof(fpA) && (!feof(fpB)))
//    {
//        if(datoA.dni > datoB.dni)
//        {
//            fwrite(&datoA, sizeof(tPersona), 1L, fpSal);
//            fread(&datoA, sizeof(tPersona), 1L, fpA);
//        }else
//        {
//            fwrite(&datoA, sizeof(tPersona), 1L, fpSal);
//            fread(&datoA, sizeof(tPersona), 1L, fpA);
//
//            fwrite(&datoA, sizeof(tPersona), 1L, fpSal);
//            fread(&datoA, sizeof(tPersona), 1L, fpB);
//        }
//    }
//    // Si alguno de los dos archivos se termina, seguiremos leyendo el otro
//    while(!feof(fpA))
//    {
//        fwrite(&datoA, sizeof(tPersona), 1L, fpSal);
//        fread(&datoA, sizeof(tPersona), 1L, fpSB);
//    }
//
//    while(!feof(fpA))
//    {
//        fwrite(&datoB, sizeof(tPersona), 1, fpB);
//        fread(&datoB, sizeof(tPersona), 1, fpB);
//    }
//
//    fseek(fpA, posA, SEEK_SET);
//    fseek(fpb, posb, SEEK_SET);
//    return MERGE_OK;
//}
