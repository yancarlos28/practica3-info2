#include "funciones_aplicacion.h"
#include "funciones_encriptar_desencriptar.h"
#include <fstream>   // solo para validar existencia del archivo

using namespace std;

static bool archivoExiste(const string& ruta) {
    ifstream f(ruta, ios::binary);
    return (bool)f;
}

bool ejecutarPipeline(string modo, int metodo, int n,
                      string archivoEntrada, string archivoSalida,
                      string &msgError)
{
    msgError.clear();

    // ---- Validaciones básicas (sin excepciones) ----
    if (!(modo == "enc" || modo == "dec")) {
        msgError = "Modo invalido (use 'enc' o 'dec').";
        return false;
    }
    if (!(metodo == 1 || metodo == 2)) {
        msgError = "Metodo invalido (use 1 o 2).";
        return false;
    }
    if (n <= 0) {
        msgError = "La semilla n debe ser > 0.";
        return false;
    }
    if (archivoEntrada.empty() || archivoSalida.empty()) {
        msgError = "Debe indicar archivo de entrada y salida.";
        return false;
    }
    if (!archivoExiste(archivoEntrada)) {
        msgError = "No se pudo abrir el archivo de entrada.";
        return false;
    }

    // ---- Lectura del archivo en bits ----
    string bits = leer_archivo_binario(archivoEntrada);
    // Nota: un archivo vacio es valido; produce 0 bloques.
    // Si quieres tratarlo como error, descomenta:
    // if (bits.empty()) { msgError = "Archivo de entrada vacio."; return false; }

    // ---- Partir en bloques ----
    int cantidadBloques = 0;
    string* bloques = partir_en_n(bits, n, cantidadBloques);
    if (bloques == nullptr && cantidadBloques > 0) {
        msgError = "Error al crear los bloques.";
        return false;
    }

    // ---- Procesar segun modo/metodo ----
    string* resultado = nullptr;

    if (modo == "enc") {
        if (metodo == 1)      resultado = codificarMetodo1(bloques, cantidadBloques);
        else /*metodo == 2*/  resultado = codificarMetodo2(bloques, cantidadBloques);
    } else { // "dec"
        if (metodo == 1)      resultado = decodificarMetodo1(bloques, cantidadBloques);
        else /*metodo == 2*/  resultado = decodificarMetodo2(bloques, cantidadBloques);
    }

    if (resultado == nullptr && cantidadBloques > 0) {
        delete[] bloques;
        msgError = "Error durante el procesamiento.";
        return false;
    }

    // ---- Unir y escribir archivo binario de salida ----
    string bitsFinal = unir_bloques(resultado, cantidadBloques);
    escribir_binario(bitsFinal, archivoSalida);

    // ---- Liberar memoria ----
    delete[] bloques;
    delete[] resultado;

    return true;
}


