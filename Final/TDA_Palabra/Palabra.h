#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#define OK 1
#define ERROR_LECTURA_PALABRA 0

#define TAM_PAL 30

#define esLetra(c) ( ((c)>='a' && (c)<='z') || ((c) >= 'A' && (c) <= 'Z') )
#define aMayuscula(c) ( ((c)>='a' && (c)<='z') ? c - ('a' - 'A') : (c))
#define aMinuscula(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + ('a' - 'A') : (c))

typedef struct
{
    char vPalabra[TAM_PAL];
}tPalabra;

typedef struct
{
    char* cursor;
    int   finSec;
}secPalabra;

int  secuenciaCrear(secPalabra* s, const char* cadena);
int  leerPalabra(secPalabra* sLect, tPalabra* palabra);
int  secuenciaFin(const secPalabra* s);
int  mostrarPalabra(const tPalabra* pal);
int  escribirCarecter(secPalabra* sEsc, char* c);
void secuenciaCerrar(secPalabra* s);
void palabraATitulo(tPalabra* palabra);
int  palabraEscribir(secPalabra* sEsc, tPalabra* palabra);
#endif // PALABRA_H_INCLUDED
