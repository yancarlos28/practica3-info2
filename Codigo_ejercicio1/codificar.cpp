#include <string>
#include "codificar.h"

using namespace std;


string codificarMetodo1(string binario, int n) {
    string codificado = "";
    int i = 0;
    string bloqueAnterior = "";

    while (i < binario.size()) {
        string bloque = binario.substr(i, n);

        if (i == 0) {
            // Primer bloque: se invierten todos los bits
            bloque = invertirBits(bloque);
        } else {
            // Contamos bits del bloque anterior (NO del actual)
            int cantidad1, cantidad0;
            contarBits(bloqueAnterior, cantidad1, cantidad0);

            if (cantidad1 == cantidad0) {
                // Igual cantidad → invertir todos los bits
                bloque = invertirBits(bloque);
            }
            else if (cantidad0 > cantidad1) {
                // Más ceros → invertir cada 2 bits
                for (int j = 0; j < bloque.size(); j += 2) {
                    bloque[j] = (bloque[j] == '1') ? '0' : '1';
                    if (j + 1 < bloque.size()) {
                        bloque[j + 1] = (bloque[j + 1] == '1') ? '0' : '1';
                    }
                }
            }
            else {
                // Más unos → invertir cada 3 bits
                for (int j = 0; j < bloque.size(); j += 3) {
                    bloque[j] = (bloque[j] == '1') ? '0' : '1';
                    if (j + 1 < bloque.size()) {
                        bloque[j + 1] = (bloque[j + 1] == '1') ? '0' : '1';
                    }
                    if (j + 2 < bloque.size()) {
                        bloque[j + 2] = (bloque[j + 2] == '1') ? '0' : '1';
                    }
                }
            }
        }

        codificado += bloque;
        bloqueAnterior = bloque;  // Guardamos este bloque para la próxima iteración
        i += n;                   // Avanzamos al siguiente bloque
    }

    return codificado;
}


string codificarMetodo2(string binario, int n) {
    string codificado = "";
    int i = 0;
    while (i < binario.size()) {
        string bloque = binario.substr(i, n);
        string bloqueCodificado = rotarDerecha(bloque);
        codificado += bloqueCodificado;
        i += n;
    }
    return codificado;
}
