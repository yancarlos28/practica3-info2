#include "utilidades.h"
#include <string>
using namespace std;


string invertirBits(string bloque) {
    for (char &bit : bloque) {
        bit = (bit == '0') ? '1' : '0';
    }
    return bloque;
}

void contarBits(const string &bloque, int &cantidad1, int &cantidad0) {
    cantidad1 = 0;
    cantidad0 = 0;
    for (char bit : bloque) {
        if (bit == '1') cantidad1++;
        else if (bit == '0') cantidad0++;
    }
}

//  Rota a la derecha un bit (último pasa al principio)

string rotarDerecha(string bloque) {
    if (bloque.empty()) return bloque;
    char ultimo = bloque.back();
    bloque.pop_back();
    bloque.insert(bloque.begin(), ultimo);
    return bloque;
}


string rotarIzquierda(const string &bloque) {
    if (bloque.empty()) return bloque;
    string rotado = bloque.substr(1) + bloque[0];
    return rotado;
}
