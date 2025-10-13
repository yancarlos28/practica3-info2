#ifndef FUNCIONES_H
#define FUNCIONES_H
using namespace std;
#include <string>

// Lee un archivo en modo binario y devuelve su contenido crudo como std::string.
// Lanza std::runtime_error si no se puede abrir.
string leerArchivo(const string &nombreArchivo);

// Convierte los bytes leídos a una cadena de bits '0'/'1'.
// Cada byte produce 8 caracteres.
string convertirABinario(const string &bytes);

// Función combinada: lee el archivo y devuelve su representación binaria completa.
string archivoABinario(const string &nombreArchivo);

#endif // FUNCIONES_H
