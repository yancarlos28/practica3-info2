#include <fstream>
#include <iostream>
#include <string>
#include "funciones.h"

using namespace std;


void codificar(string archivoEntrada, string archivoSalida, short n, short metodo) {
    ifstream entrada(archivoEntrada);

    if (!entrada) {
        cerr << "Error: No se pudo abrir el archivo " << archivoEntrada << endl;
        return;
    }

    string texto = "";
    char c;
    while (entrada.get(c)) {
        texto += c;
    }
    entrada.close();

    // Convertir texto a binario
    string binario = "";
    for (char c : texto) {
        for (int i = 7; i >= 0; i--) {
            binario += ((c >> i) & 1) ? '1' : '0';
        }
    }

    string binarioCodificado;
    if (metodo == 1) {
        binarioCodificado = codificarMetodo1(binario, n);
    } else if (metodo == 2) {
        binarioCodificado = codificarMetodo2(binario, n);
    } else {
        cerr << "Método no válido." << endl;
        return;
    }

    // Guardar archivo de salida binario
    ofstream salida(archivoSalida, ios::binary);
    if (!salida) {
        cerr << "Error: No se pudo abrir el archivo de salida " << archivoSalida << endl;
        return;
    }

    salida.write(binarioCodificado.c_str(), binarioCodificado.size());
    salida.close();

    cout << "Archivo codificado guardado como: " << archivoSalida << endl;
}

// =======================
// FUNCION DECODIFICAR
// =======================
void decodificar(string archivoEntrada, string archivoSalida, short n, short metodo) {
    ifstream entrada(archivoEntrada, ios::binary);
    if (!entrada) {
        cerr << "Error: no se pudo abrir el archivo de entrada." << endl;
        return;
    }

    // Leer bits del archivo
    string binario;
    char bit;
    while (entrada.read(&bit, 1)) {
        if (bit == '0' || bit == '1')
            binario += bit;
    }
    entrada.close();

    string texto;

    if (metodo == 1) {
        texto = decodificarMetodo1(binario, n);
    } else if (metodo == 2) {
        texto = decodificarMetodo2(binario, n);
    } else {
        cerr << "Método no válido." << endl;
        return;
    }

    ofstream salida(archivoSalida);
    if (!salida) {
        cerr << "Error: no se pudo abrir el archivo de salida." << endl;
        return;
    }

    salida << texto;
    salida.close();

    cout << "Archivo decodificado guardado como: " << archivoSalida << endl;
}

