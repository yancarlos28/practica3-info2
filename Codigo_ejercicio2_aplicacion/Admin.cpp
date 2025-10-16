#include "Admin.h"
#include <iostream>
#include <fstream>
using namespace std;
// Constructor vacío
Admin::Admin() {}

// Verifica la clave ingresada contra la que está en el archivo sudo.txt
bool Admin::verificarAcceso(const string& claveIngresada) {
    ifstream archivo("sudo.txt");
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir sudo.txt";
        return false;
    }


    string claveGuardada;
    getline(archivo, claveGuardada);
    archivo.close();

    return claveIngresada == claveGuardada;
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
