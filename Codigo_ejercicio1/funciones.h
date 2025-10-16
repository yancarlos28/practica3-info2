#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
using namespace std;

#include "codificar.h"
#include "decodificar.h"

// Funciones principales
void codificar(string archivoEntrada, string archivoSalida, short n, short metodo);
void decodificar(string archivoEntrada, string archivoSalida, short n, short metodo);

#endif
