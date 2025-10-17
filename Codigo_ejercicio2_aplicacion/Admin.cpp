#include "Admin.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "Encriptacion.h"
using namespace std;

// Constructor vacío
Admin::Admin() {}


// utilidades simples
static bool leerArchivo(const string& path, string& out) {
    ifstream f(path, ios::binary);
    if (!f) return false;
    out.assign(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
    return true;
}
static bool escribirArchivo(const string& path, const string& data) {
    ofstream f(path, ios::binary | ios::trunc);
    if (!f) return false;
    f.write(data.data(), (std::streamsize)data.size());
    return (bool)f;
}

/* 1) Guardar la clave admin:
   - texto -> binario (8 bits por char)
   - codificar (n=7 dentro de tu implementación)
   - escribir a sudo.bin
*/
bool Admin::generarSudoCifrado(const string& clavePlano) {
    const string bin = textoABinario(clavePlano);
    const string cif = codificar(bin);   // tu codificar usa n=7
    return escribirArchivo(kRutaSudo, cif);
}

/* 2) Verificar acceso:
   - leer sudo.bin (cifrado)
   - decodificar (n=7) -> binario
   - binario -> texto (clave real)
   - comparar con la ingresada
*/
bool Admin::verificarAcceso(const string& claveIngresada) {

    string cifrado;
    if (!leerArchivo(kRutaSudo, cifrado)) {
        cerr << "[!] No se pudo abrir " << kRutaSudo << "\n";
        return false;
    }
    const string bin = decodificar(cifrado);   // n=7
    string claveReal = binarioATexto(bin);

    // recorta CR/LF al final (Windows)
    while (!claveReal.empty() && (claveReal.back()=='\n' || claveReal.back()=='\r'))
        claveReal.pop_back();

    return (claveIngresada == claveReal);
}



// Crea un nuevo usuario a partir de input de consola
Usuario Admin::crearUsuario() {
    string cedula, clave;
    unsigned int saldo;

    cout << "Ingrese la cedula del nuevo usuario: ";
    cin >> cedula;
    cout << "Ingrese la clave del nuevo usuario: ";
    cin >> clave;
    cout << "Ingrese el saldo del nuevo usuario: ";
    cin >> saldo;

    cout << "Usuario creado exitosamente.\n";
    return Usuario(cedula, clave, saldo);
}
