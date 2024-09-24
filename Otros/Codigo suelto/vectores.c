//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define esBlanco(x)((x==' ' || x== '\n' || x=='\t') ? (1) : (0))
//
//int initVec(int* vec, int ce)
//{
//    int i;
//    for(i=0;  i<ce; i++)
//    {
//        *vec = i+1;
//        vec++;
//    }
//    return 0;
//}
//
//int imprimirVec(int* vec, int ce)
//{
//    int i;
//    for(i=0; i<ce; i++)
//    {
//        printf("%d\n", *vec);
//        vec++;
//    }
//    return 0;
//}
//
//int insertarEnPosVec(int* vec, int pos, int el)
//{
//    *(vec + pos) = el;
//    return 0;
//}
//
//int insertarAlFinal(int* vec, int ce, int el)
//{
//    *(vec + ce) = el;
//    return 0;
//}
//
//int eliminarPrimeraAparicion(int* vec, int el, int ce)
//{
//    int i;
//    for(i=0; i<ce; i++)
//    {
//        if(*vec == el)
//        {
//            *(vec) = 0;
//            return 0;
//        }
//        vec++;
//    }
//    return el;
//}
//
//int eliminarTodasLasApariciones(int* vec, int el, int ce)
//{
//    int i;
//    for(i=0; i<ce; i++)
//    {
//        if(*vec == el)
//        {
//            *(vec) = 0;
//            return 0;
//        }
//        vec++;
//    }
//    return el;
//}
//
//int esPalindromo(const char* s1, const char* s2)
//{
//    s2 += strlen(s2);
//    while(*s1 != '\0' && *s2 != '\0')
//    {
//        if(*s1 == *s2)
//        {
//            s1++;
//            s2--;
//            printf("Iguales");
//        }else{
//            printf("No iguales");
//            return 0;
//        }
//    }
//    return 1;
//}
//
//int valorNumerico(char *s)
//{
//    return strlen(s);
//}
//
//char* normalizarCadena(char* dest, const char* orig)
//{
//    char* destInicial = dest;
//    // Primera posicion en la cadena
//
//    while(*orig)
//    // Mientras no sea el fin de la cadena
//    {
//        while(esBlanco(*orig))
//            orig++;
//        // Si es un espacio en blanco, un \t u otro avanzamos en la cadena original
//
//        if(*orig)
//        // Si no es retorno de carro
//        {
//            *dest = toupper(*orig);
//            // Capitalizamos la primera letra. Capitalizamos siempre que hayamos pasado por un espacio en blanco
//            dest++;
//            orig++;
//            // Avanzamos en ambas cadenas
//            while(!esBlanco(*orig) && *orig)
//            // Si no es un ' ', \t u otro y si no se terminó la cadena, ponemos en lowercase el siguiente caracter
//            {
//                *dest = tolower(*orig);
//                dest++;
//                orig++;
//                // Nos movemos en ambas cadenas
//            }
//
//            if(esBlanco(*orig))
//            {
//                // Si en la cadena original hay un espacio en blanco, lo copiamos a la nueva
//                *dest = ' ';
//                dest++;
//                orig++;
//            }
//        }
//    }
//
//    if(dest > destInicial && *(dest-1) == ' ') // Para saber si se movio el puntero
//        dest--;
//
//    *dest = '\0';
//
//    return dest;
//}
//#include "vectores.h"
