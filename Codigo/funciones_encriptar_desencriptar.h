#ifndef FUNCIONES_ENCRIPTAR_DESENCRIPTAR_H
#define FUNCIONES_ENCRIPTAR_DESENCRIPTAR_H

#include <string>
using namespace std;

// Convierte el archivo binario a una cadena de bits ("0"/"1")
string leer_archivo_binario(string nombreArchivo);

// Une un arreglo de bloques en una sola cadena de bits
string unir_bloques(string* bloques, int cantidadBloques);

// Escribe una cadena de bits a un archivo binario
void escribir_binario(string bits, string nombreArchivo);

// Parte la cadena binaria en bloques de tamaño n (rellena el último con '0' si es necesario)
// Devuelve un arreglo dinámico de strings y deja en cantidadBloques el total de bloques
string* partir_en_n(string archivo_binario, int n, int &cantidadBloques);

// Invierte cada bit del bloque
string invertirBits(string bloque);

// Cuenta 1s y 0s en el bloque (resultados por referencia)
void contarBits(string bloque, int &unos, int &ceros);

// Invierte los bits en posiciones múltiplos de k (1-based)
string invertirCadaKBits(string bloque, int k);

// Codificación método 1 (reglas según conteo del bloque anterior sin codificar)
string* codificarMetodo1(string* bloques, int cantidadBloques);

// Codifica un bloque con el método 2 (rotación: primero ← último, resto se desplaza)
string codificarBloqueMetodo2(string bloque);

// Codificación método 2 para todos los bloques
string* codificarMetodo2(string* bloques, int cantidadBloques);

// Decodificación método 1
string* decodificarMetodo1(string* codificados, int cantidadBloques);

// Decodifica un bloque del método 2 (inversa de la rotación)
string decodificarBloqueMetodo2(string bloque);

// Decodificación método 2 para todos los bloques
string* decodificarMetodo2(string* codificados, int cantidadBloques);

#endif // FUNCIONES_ENCRIPTAR_DESENCRIPTAR_H

