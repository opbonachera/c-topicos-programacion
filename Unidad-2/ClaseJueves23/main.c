#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculadora.h"

int sumar(int a,int b);
int multiplicar(int a, int b);
int compararEntero(const void *a, const void *b);


int main()
{
    //    int result = calcular(2,3,sumar);
    //    printf("El resultado de la suma es %d\n", result);
    //
    //    result = calcular(2,3,multiplicar);
    //    printf("El resultado de la multiplicacion es %d\n", result);

    // Ordenamiento del vector con qsort
    //    int vec[] = {3,4,5,2,1};
    //    size_t cant = sizeof(vec) / sizeof(int);
    //
    //    printVector(vec,cant);
    //
    //    qsort(vec, cant, sizeof(int), compararEntero); // La funcion qsort ordena areas de memoria, recibe punteros a void
    //
    //    printf("\n");
    //    printVector(vec,cant);

    // Vector dinamico
    tVector v;

    vectorCrear(&v, sizeof(int));
    return 0;
}

//int compararEntero(const void *a, const void *b)
//{
//    // Casteamos a int ya que la funcion qsort recibe void (areas de memoria) y nosotros estamos trabajando con enteros
//    const int *punteroA = (const int *)a;
//    const int *punteroB = (const int *)b;
//
//    return *punteroB - *punteroA;
//}
//
//int sumar(int a, int b)
//{
//    return a + b;
//}
//
//int multiplicar(int a, int b)
//{
//    return a * b;
//}

