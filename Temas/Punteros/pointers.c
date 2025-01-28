#include <stdlib.h>
#include <string.h>

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
    int i;
    for(int i=0;i<5;i++)
    {
        printf("%d\n",*p);
        p++;
    }
}

int strings()
{
//    char name[8];
//    int numbers[5];
//
//    name[0] = 'O';
//    name[1] = 'r';
//    name[2] = 'n';
//    name[3] = 'e';
//    name[4] = '\0';
//
//    printf("String length: (%s)\n", name);
//    printf("String content: (%d)\n", strlen(name));
//    printf("String size: (%d)\n", sizeof(name)); // 1 byte * 8
//
//    printString(&name);
//
//    printf("Result: %d\n", compareStrings("Ornela", "Ornella"));
//    printf("Result: %d\n", compareStrings("Ornella", "Ornella"));
    //compareStrings("Ornella", "Ornella");

    return 0;
}

int printString(char *p)
{
    printf("\n");
    printf("String content: \n");
    while(*p != '\0')
    {
        printf("%c", *p);
        p++;
    }
    return 0;
}

int matrix()
{
    int matrix[3][3] = {{1,2,3},
                        {4,5,6},
                        {7,8,9}};
    int C[3][2][2] = { { {1,2},{3,4} },
                       { {5,6},{7,8} },
                       { {9,10},{11,12} }};

    printf("%d\n", C); // All of them point to the first element
    printf("%d\n", *C);
    printf("%d\n", C[0]);
    printf("%d\n", &C[0][0]+1);

    return 0;
}

int printMatrix(const int *m)
{
    printf("Printing matrix...\n");
    for(int i=0; i<3;i++)
    {

        for(int j=0; j<3; j++)
        {
            printf("%d", *m);
            m++;
        }
        printf("\n");
    }
    return 0;
}

int memory()
{
    // (void *) malloc(size_t size)
//    void  *m = (int *)malloc(sizeof(int) * 5);
//    int   *c = (int *)calloc(3, sizeof(int));
//    int   *r = (int *)realloc(m, sizeof(int *5));

    //initArrayNumbers();
    initEmptyArray();
}

int initArrayNumbers()
{
    int n;

    printf("Enter size of array\n");
    scanf("%d", &n);

    int *A = (int*)malloc(n * sizeof(int));

    if(*A == NULL)
    {
        printf("Error allocating memory for new array. \n");
        return 1;
    }

    for(int i=0; i<n; i++)
        A[i] = i;

    for(int i=0; i<n; i++)
        printf("%d ", A[i]);

    printf("\nArray initialized correctly.\n");
    return 0;
}

int initEmptyArray()
{
    int n;

    printf("Enter size of new array\n");
    scanf("%d", &n);

    int *c = (int *)calloc(n, sizeof(int));

    if(*c == NULL)
    {
        printf("Error allocating memory for new array. \n");
        return 1;
    }

    for(int i=0; i<n; i++)
        printf("%d", c[i]);
    return 0;
}
