#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

// Funciones compartidas por ambos módulos
string invertirBits(string bloque);
void contarBits(const string &bloque, int &cantidad1, int &cantidad0);

// Rotaciones
string rotarDerecha(string bloque);
string rotarIzquierda(const string &bloque);

#endif
