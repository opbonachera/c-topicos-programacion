#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct{
    void* v;
    int   tamElem;
    int   ce;
    int   cap;
}Vector;

int vectorInicializar(Vector* vec, int tamElem, int ce);
void vectorVaciar(Vector* vec);
void vectorDestruir(Vector* vec);
int vectorRedimensionar(Vector* vec, int factorRedimension);

void vectorAsignarEnteros(Vector* v);
void vectorOrdenar();
void vectorOrdAgregarElemento();
void vectorOrdEliminarElemento();

#endif // VECTOR_H_INCLUDED
