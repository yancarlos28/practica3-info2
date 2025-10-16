#include <string>
#include "decodificar.h"
using namespace std;


string decodificarMetodo1(string binario, int n) {
    string decodificado = "";
    string bloqueAnterior = "";

    for (int i = 0; i < (int)binario.size(); i += n) {
        string bloque = binario.substr(i, n);
        string bloqueRecuperado;

        if (i == 0) {
            bloqueRecuperado = invertirBits(bloque);
        } else {
            int cantidad1, cantidad0;
            contarBits(bloqueAnterior, cantidad1, cantidad0);

            if (cantidad1 == cantidad0) {
                bloqueRecuperado = invertirBits(bloque);
            } else if (cantidad0 > cantidad1) {
                bloqueRecuperado = bloque;
                for (int j = 0; j < (int)bloqueRecuperado.size(); j += 2) {
                    bloqueRecuperado[j] = (bloqueRecuperado[j] == '1') ? '0' : '1';
                    if (j + 1 < (int)bloqueRecuperado.size())
                        bloqueRecuperado[j + 1] = (bloqueRecuperado[j + 1] == '1') ? '0' : '1';
                }
            } else {
                bloqueRecuperado = bloque;
                for (int j = 0; j < (int)bloqueRecuperado.size(); j += 3) {
                    bloqueRecuperado[j] = (bloqueRecuperado[j] == '1') ? '0' : '1';
                    if (j + 1 < (int)bloqueRecuperado.size())
                        bloqueRecuperado[j + 1] = (bloqueRecuperado[j + 1] == '1') ? '0' : '1';
                    if (j + 2 < (int)bloqueRecuperado.size())
                        bloqueRecuperado[j + 2] = (bloqueRecuperado[j + 2] == '1') ? '0' : '1';
                }
            }
        }

        decodificado += bloqueRecuperado;
        bloqueAnterior = bloqueRecuperado;
    }

    // convertir bits a texto
    string texto = "";
    for (int i = 0; i + 7 < (int)decodificado.size(); i += 8) {
        unsigned char caracter = 0;
        for (int j = 0; j < 8; j++) {
            if (decodificado[i + j] == '1')
                caracter |= (1 << (7 - j));
        }
        texto += caracter;
    }
    return texto;
}

string decodificarMetodo2(string binario, int n) {
    string decodificado = "";
    for (int i = 0; i < (int)binario.size(); i += n) {
        string bloque = binario.substr(i, n);
        string bloqueRecuperado = rotarIzquierda(bloque);
        decodificado += bloqueRecuperado;
    }

    string texto = "";
    for (int i = 0; i + 7 < (int)decodificado.size(); i += 8) {
        unsigned char caracter = 0;
        for (int j = 0; j < 8; j++) {
            if (decodificado[i + j] == '1')
                caracter |= (1 << (7 - j));
        }
        texto += caracter;
    }
    return texto;
}
