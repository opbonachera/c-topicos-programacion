#ifndef POINTERS_H_INCLUDED
#define POINTERS_H_INCLUDED

int pointers();
int arrays();
int strings();
int matrix();
int memory();

int initArrayNumbers();
int initEmptyArray();
void printArray(int*);
void printAddress(int *p);
void printValue(int *p);
int* incrementPointer(int *p, int cant);
int printString(char *p);
int compareStrings(const char *s1, const char *s2);
char* normalizarCadena(char *dest, const char *orig);
int printMatrix(const int* m);

#endif // POINTERS_H_INCLUDED
