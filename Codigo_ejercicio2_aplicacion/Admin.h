#ifndef ADMIN_H
#define ADMIN_H

#include "Usuario.h"
using namespace std;

class Admin {
private:
    string claveAdmin;

public:
    Admin();

    bool verificarAcceso(const string& claveIngresada);
    Usuario crearUsuario();
};

#endif // ADMIN_H
