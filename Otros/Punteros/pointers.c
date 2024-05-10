#include <stdlib.h>

#include "pointers.h"

void printAddress(int *p)
{
    printf("Address: %p\n",&p);
}

void printValue(int *p)
{
    printf("Address: %d | Value: %d\n", p, *p);
}

int* incrementPointer(int *p, int cant)
{
    return p+=cant;
}

int pointers()
{
//    int a = 10;
//    int *p = &a; // P takes address of a
//
//    *(p+1)=67; // p+1 in memory gets assigned the value 67
//
//    printf("Size of integer is %d byte(s)\n", sizeof(int));
//    printf("Address: %d - value:%d\n", p, *p);
//    printf("Address: %d - value:%d\n", p+1, *(p+1)); // Pointer incremented by 4 bytes
//
//    printf("\n");
//    char *pC; // Pointer to char
//    pC = (char*)p;
//    pC = "a";
//
//    printf("Size of char is %d byte(s)\n", sizeof(char));
//    printf("Address: %d - value:%d\n", pC, *pC);
//    printf("Address: %d - value:%d\n", pC+1, *(pC+1)); // Pointer incremented by 1 byte
//    printf("Character: %c\n", *pC);

//    int x = 5;      // Stores an integer
//    int *p = &x;    // P gets the address of x
//    *p = 6;         //  In the address of p we store the integer 6
//
//    printValue(p);
//
//    int **q = &p;   // q is a pointer to a pointer. Points to the pointer that points to x
//    int ***r = &q;  // r is a pointer to a pointer that points to a pointer. r points to a pointer that points to
//    // a pointer that points to a pointer that points to x
//    // p points to x
//    // q points to p
//    // r points to q
//
//    printf("*p: %d\n",*p); // Prints whats stored in p
//    printf("*q: %d\n",*q); // Prints the memory address of p
//    printf("*(*q) %d\n",*(*q)); // Prints whats stored in q
//    printf("*(*r) %d\n",*(*r)); // Prints the memory address of r
//    printf("*(*(*r)) %d\n",*(*(*r)) ); // Prints whats stored in r
    return 0;
}

int arrays()
{
    int arr[5] = {1,2,3,4,5};

    printArray(&arr);
    return 0;
}

void printArray(int *p)
{
    for(int i=0;i<5;i++)
    {
        printf("%d\n",*p);
        p++;
    }
}
