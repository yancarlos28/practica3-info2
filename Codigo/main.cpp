#include <iostream>
#include <string>
#include "funciones_encriptar_desencriptar.h"
#include "funciones_aplicacion.h"
using namespace std;

int main()
{
    int num_modo,metodo, semilla;
    string archivo_fuente, archivo_salida;
    string msgError;

    cout << "Seleccione una opcion:\n";
    cout << "1: Codificar\n";
    cout << "2: Decodificar\n> ";
    cin >> num_modo;

    cout << "Ingrese el valor de la semilla (n): ";
    cin >> semilla;

    cout << "Seleccione el metodo a usar o utilizado:\n";
    cout << "1: Primer metodo \n";
    cout << "2: Segundo metodo \n> ";
    cin >> metodo;

    cout << "Ingrese el nombre del archivo fuente: ";
    cin >> archivo_fuente;

    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> archivo_salida;


    // ahora elegimos el modo
    string modo = (num_modo == 1 ? "enc" : "dec");

    // llamamos a la función que hace todo
    if (!ejecutarPipeline(modo, metodo, semilla, archivo_fuente, archivo_salida, msgError)) {
        cout << "Error: " << msgError << endl;
        return 1;
    }

    cout << "\nProceso completado correctamente.\n";
    return 0;
}
