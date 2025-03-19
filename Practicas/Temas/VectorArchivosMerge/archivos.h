#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

bool generarArchivoProductos(const char* nomArch);
bool generarArchivoMovimientos(const char* nomArch);
bool generarIndice(const char* nomArch, const char* nomIdx);
bool mostrarArchivo(const char* nomArch);
bool actualizarPrecioProductos(const char* nomArch, float porc);
int cmpIndProd(const void* e1, const void* e2);
bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc);
bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs);
void procesarProductoNuevo();
bool generarArchivoEmpleadosBin(const char* nomArch);
void mostrarArchivoEmpleadosBin(const char* nomArch);
int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt);
void empleadoBinATxtVar(const void* reg, FILE* archTxt);
void empleadoBinATxtFijo(const void* reg, FILE* archTxt);
void empleadoTxtVarABin(char* linea, void* reg);
void empleadoTxtFijoABin(char* linea, void* reg);

#endif // ARCHIVOS_H_INCLUDED
