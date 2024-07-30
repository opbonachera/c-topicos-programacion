#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

#define OK 0
#define ERROR 1

#define esBlanco(ch) ((ch) == ' ' ? 1 : 0)
#define esEspacio(ch) ((ch) == '\n' ? 1 : 0)

char* normalizarCadena(char *cadenaDestino, char *cadenaOrigen);
int   imprimirCadena(char *cadena);
int   compararCadenas(char* s1, char* s2);

#endif // STRINGS_H_INCLUDED
