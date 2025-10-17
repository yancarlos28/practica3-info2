#ifndef ADMIN_H
#define ADMIN_H

#include "Usuario.h"
using namespace std;

class Admin {
private:
    string claveAdmin;
    inline static const string kRutaSudo = "sudo.bin";

public:
    Admin();
    // crea/actualiza sudo.bin a partir de una clave en claro
    static bool generarSudoCifrado(const string& clavePlano);

    bool verificarAcceso(const string& claveIngresada);
    Usuario crearUsuario();
};

#endif // ADMIN_H
