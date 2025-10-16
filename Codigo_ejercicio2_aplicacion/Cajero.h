#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "Usuario.h"
#include "Admin.h"
#include "Encriptacion.h"

using namespace std;

class Cajero {
private:
    Usuario usuarios[5];
    int numUsuarios=0;

    // Carga y descifra usuarios.bin en el array usuarios[]
    void cargarUsuarios();

    // Serializa usuarios[] y cifra en usuarios.bin
    void guardarUsuarios();

    // Busca usuario
    Usuario* buscarUsuario(const string &doc);

public:
    Cajero() : numUsuarios(0) {}
    void iniciar();
};

#endif // CAJERO_H

