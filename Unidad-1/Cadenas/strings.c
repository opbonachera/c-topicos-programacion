/* ARITMETICA DE PUNTEROS Y NORMALIZACION DE CADENAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compararStrings(char*, char*);
int mostrarPunteros(int*);
int intercambiarPunteros();

int main()
{
        // Comparar dos strings y decir si son iguales
        // Normalizar string
        char nombre[8] = "Ornella";

        //printf("Resultado de la comparacion: %d\n", compararStrings(&nombre,&nombre)); // Retorna n>0
        printf("Resultado de la comparacion: %d\n", compararStrings(&nombre,&"Paula")); // Retorna n<0

        int n[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        // mostrarPunteros(&n);
        //intercambiarPunteros();

        return 0;
}

int mostrarPunteros(int* p)
{
    printf("Puntero del arreglo: (dirección del primer elemento) %p %d \n", p);
    printf("Puntero al primer elemento: %p elemento %d \n", &p, *p);
    printf("Puntero al segundo elemento: %p elemento %d \n", &p + 1, *p+1); // Su dirección de memoria será 4 bytes mas grande ya que cada entero ocupa 4 bytes.

    return 0;
}

int intercambiarPunteros()
{
    int *p, *q, x=10;

    p=&x; // p toma la dirección de memoria de x
    q=p; // q toma la direccion de memoria de p por lo tanto de x

    printf("Elemento %d puntero %p\n", x, &x);
    printf("Elemento %d puntero %p\n", p, &p);
    printf("Elemento %d puntero %p\n", q, &q);

    *p = 6;

    printf("Puntero %p Elemento %d\n", x, x);
    printf("Puntero %p Elemento %d\n", p, *p);
    printf("Puntero %p Elemento %d\n", q, *q); // p: direccion de memoria *q: lo que esta en esa direccion

    return 0;
}

int compararStrings(char *s1, char *s2)
{
    printf("\n");
    printf("Comparando cadenas\n");
    while(*s1 != '\0' && *s2 != '\0')
    {
        printf("s1(%p) - s2(%p)\n", s1, s2);
        // Si lo que esta en el puntero *s1 es distinto a lo que esta en el caracter al que apunta *s2, devolvemos la diferencia
        // que como minimo sera -1
        // Lo que incrementamos es el puntero y de ahi vamos comparando el caracter al que apuntan sabiendo que la memoria es s
        if(*s1 != *s2)
            return (unsigned char)*s1 - (unsigned char)*s2;

        printf("s1(%p) - s2(%p)\n", s1, s2);
        s1++; s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

