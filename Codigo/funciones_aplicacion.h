#ifndef FUNCIONES_APLICACION_H
#define FUNCIONES_APLICACION_H
#pragma once
#include <string>
using namespace std;

bool ejecutarPipeline(string modo, int metodo, int n,
                      string archivoEntrada, string archivoSalida,
                      string &msgError);
static bool archivoExiste(const string& ruta);

#endif // FUNCIONES_APLICACION_H

