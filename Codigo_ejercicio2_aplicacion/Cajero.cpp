#include "Cajero.h"
#include <fstream>
#include <iostream>

using namespace std;

void Cajero::cargarUsuarios() {
    numUsuarios = 0;
    ifstream file("usuarios.bin", ios::binary);
    if (!file.is_open()) {
        cout << "No existe usuarios.bin\n";
        return;
    }

    // Leer contenido cifrado
    string cifrado;
    file.seekg(0, ios::end);
    cifrado.resize((size_t)file.tellg());
    file.seekg(0);
    file.read(&cifrado[0], cifrado.size());
    file.close();

    // Descifrar
    string binario = decodificar(cifrado);
    string plano = binarioATexto(binario);

    // Leer línea por línea
    size_t start = 0;
    while (start < plano.size() && numUsuarios < 20) {
        size_t nl = plano.find('\n', start);
        string linea = plano.substr(start, nl - start);
        start = (nl == string::npos ? plano.size() : nl + 1);

        size_t c1 = linea.find(',');
        size_t c2 = (c1 != string::npos) ? linea.find(',', c1 + 1) : string::npos;
        if (c1 == string::npos || c2 == string::npos) continue;

        string doc   = linea.substr(0, c1);
        string clave = linea.substr(c1 + 1, c2 - c1 - 1);
        unsigned int sal  = static_cast<unsigned int>(stoul(linea.substr(c2 + 1)));

        usuarios[numUsuarios++] = Usuario(doc, clave, sal);
    }

    cout << "Usuarios cargados:\n";
    for (int i = 0; i < numUsuarios; ++i) {
        cout << usuarios[i].getDoc() << " - " << usuarios[i].getClave() << " - " << usuarios[i].getSaldo() << "\n";
    }
}

void Cajero::guardarUsuarios() {
    string plano;
    for (int i = 0; i < numUsuarios; ++i) {
        plano += usuarios[i].getDoc() + "," +
                 usuarios[i].getClave() + "," +
                 to_string(usuarios[i].getSaldo()) + "\n";
    }
    string binario = textoABinario(plano);
    string cifrado = codificar(binario);

    ofstream file("usuarios.bin", ios::binary);
    if (!file.is_open()) {
        cout << "Error al guardar usuarios.bin\n";
        return;
    }
    file.write(cifrado.data(), (streamsize)cifrado.size());
    file.close();
}


// ------------------
// Busca usuario
// ------------------
Usuario* Cajero::buscarUsuario(const string &doc) {
    for (int i = 0; i < numUsuarios; ++i)
        if (usuarios[i].getDoc() == doc) return &usuarios[i];
    return nullptr;
}

// ------------------
// Flujo principal
// ------------------
void Cajero::iniciar() {
    cargarUsuarios();  // Ya no se pide la clave admin de entrada

    bool salir = false;
    while (!salir) {
        cout << "\n--- MENU INICIAL ---\n"
                  << "1) Modo administrador\n"
                  << "2) Modo usuario\n"
                  << "3) Salir\n"
                  << "Opcion: ";
        int modo;
        cin >> modo;

        switch (modo) {
        case 1: {
            Admin admin;
            string claveAdmin;
            cout << "Clave admin: ";
            cin >> claveAdmin;

            if (!admin.verificarAcceso(claveAdmin)) {
                cout << "Acceso denegado.\n";
                break;
            }

            bool salirAdmin = false;
            while (!salirAdmin) {
                cout << "\n--- MENU ADMIN ---\n"
                          << "1) Crear usuario\n"
                          << "2) Volver al menu principal\n"
                          << "Opcion: ";
                int opAdmin;
                cin >> opAdmin;

                switch (opAdmin) {
                case 1: {
                    if (numUsuarios >= 5) {
                        cout << "Capacidad maxima de usuarios alcanzada.\n";
                        break;
                    }
                    Usuario nuevo = admin.crearUsuario();
                    usuarios[numUsuarios++] = nuevo;
                    guardarUsuarios();
                    break;
                }
                case 2:
                    salirAdmin = true;
                    break;
                default:
                    cout << "Opción inválida.\n";
                }
            }
            break;
        }

        case 2: {
            string doc, clave;
            cout << "Documento: ";
            cin >> doc;
            cout << "Clave: ";
            cin >> clave;

            Usuario* usuarioEncontrado = buscarUsuario(doc);
            if (!usuarioEncontrado || usuarioEncontrado->getClave() != clave) {
                cout << "Credenciales inválidas.\n";
                break;
            }

            Usuario &u = *usuarioEncontrado;
            bool session = true;
            while (session) {
                cout << "\n--- MENU USUARIO ---\n"
                          << "1) Consultar saldo\n"
                          << "2) Retirar\n"
                          << "3) Salir\n"
                          << "Opcion: ";
                int op;
                cin >> op;
                if (op == 1) {
                    u.consultar();
                } else if (op == 2) {
                    unsigned int monto;
                    cout << "Monto a retirar: ";
                    cin >> monto;
                    u.retirar(monto);
                } else if (op == 3) {
                    session = false;
                } else {
                    cout << "Opción inválida.\n";
                }
            }
            guardarUsuarios();
            break;
        }

        case 3:
            salir = true;
            break;

        default:
            cout << "Opción inválida.\n";
        }
    }
}
