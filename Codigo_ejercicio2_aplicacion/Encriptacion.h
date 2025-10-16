#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H
using namespace std;
#include <string>

string invertirBits(string bloque);

void contarBits(const string &bloque, int &cantidad1, int &cantidad0);

string codificar(string binario);

string decodificar(const string &codificado);

string binarioATexto(const string& bin);

string textoABinario(const string& texto);

#endif // ENCRIPTACION_H
