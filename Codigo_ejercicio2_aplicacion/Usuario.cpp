#include <iostream>
#include "Usuario.h"
using namespace std;
Usuario::Usuario() : saldo(0) {}
Usuario::Usuario(const string &doc, const string &cont, unsigned int sal): documento(doc), clave(cont), saldo(sal) {}

void Usuario::retirar(unsigned int cantidad) {
    const int comision=1000;
    if ((cantidad + comision) <= saldo) {
        saldo-=(comision+cantidad);
        cout << "Retiro exitoso." << endl;
        return;
    } else {
        cout << "Saldo insuficiente." << endl;
        return;
    }
}

unsigned int Usuario::consultar() {
    const unsigned int comision = 1000;
    if (saldo >= comision) {
        saldo -= comision;
        cout << "Consulta exitosa. Saldo actual: " << saldo << " COP\n";
        return saldo;
    } else {
        cout << "Saldo insuficiente para realizar la consulta.\n";
        return saldo;
    }
}

