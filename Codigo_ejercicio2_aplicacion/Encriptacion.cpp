#include "Encriptacion.h"
#include <string>
using namespace std;
string invertirBits(string bloque) {
    for (size_t i = 0; i < bloque.size(); i++) {
        bloque[i]=(bloque[i]=='1')?'0':'1';
    }
    return bloque;
}

void contarBits(const string &bloque, int &cantidad1, int &cantidad0){
    cantidad1 = 0;
    cantidad0 = 0;
    for (char bit : bloque) {
        if (bit == '1') cantidad1++;
        else cantidad0++;
    }
}


string codificar(string binario) {
    int n=7;
    string codificado = "";
    size_t i = 0;
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
                for (size_t j = 0; j < bloque.size(); j += 2) {
                    bloque[j] = (bloque[j] == '1') ? '0' : '1';
                    if (j + 1 < bloque.size()) {
                        bloque[j + 1] = (bloque[j + 1] == '1') ? '0' : '1';
                    }
                }
            }
            else {
                // Más unos → invertir cada 3 bits
                for (size_t j = 0; j < bloque.size(); j += 3) {
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


string decodificar(const string &codificado) {
    string original;
    int n = 7;
    int len = codificado.size();
    for (int i = 0; i < len; i += n) {
        string bloque = codificado.substr(i, n);
        if (i == 0) {
            bloque = invertirBits(bloque);
        } else {
            string prevCod = codificado.substr(i - n, n);
            int c1, c0;
            contarBits(prevCod, c1, c0);
            if (c1 == c0) {
                bloque = invertirBits(bloque);
            } else if (c0 > c1) {
                // en cifrado invertíamos cada 2 bits → aquí hacemos lo mismo para revertir
                for (int j = 0; j < (int)bloque.size(); j += 2) {
                    bloque[j] = (bloque[j] == '1') ? '0' : '1';
                    if (j + 1 < (int)bloque.size())
                        bloque[j+1] = (bloque[j+1] == '1') ? '0' : '1';
                }
            } else {
                // en cifrado invertíamos cada 3 bits → aquí lo mismo
                for (int j = 0; j < (int)bloque.size(); j += 3) {
                    bloque[j] = (bloque[j] == '1') ? '0' : '1';
                    if (j + 1 < (int)bloque.size())
                        bloque[j+1] = (bloque[j+1] == '1') ? '0' : '1';
                    if (j + 2 < (int)bloque.size())
                        bloque[j+2] = (bloque[j+2] == '1') ? '0' : '1';
                }
            }
        }
        original += bloque;
    }
    return original;
}
string textoABinario(const string& texto) {
    string bin;
    for (char c : texto) {
        for (int i = 7; i >= 0; --i) {
            bin += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return bin;
}
string binarioATexto(const string& bin) {
    string texto;
    for (size_t i = 0; i + 7 < bin.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c = (c << 1) | (bin[i + j] - '0');
        }
        texto += c;
    }
    return texto;
}

