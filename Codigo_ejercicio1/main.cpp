#include <iostream>
#include <string>
#include "funciones.h"

using namespace std;

int main() {
    short a,n,metodo;
    string archivoEntrada, archivoSalida;
    cout << "Opciones \n";
    cout << "1)Codificar\n2)Decodificar\n";
    cout << "Escoja la accion a realizar: \n";
    cin>>a;
    switch (a){
    case 1:
        cout<< "Indique el archivo de entrada: ";
        cin>>archivoEntrada;
        cout<< "Indique el archivo de salida: ";
        cin>>archivoSalida;
        cout << "Ingrese el tamanio del bloque: ";
        cin >> n;
        cout << "Ingrese el metodo (1 o 2): ";
        cin >> metodo;
        codificar(archivoEntrada,archivoSalida,n,metodo);
        break;
    case 2:
        cout<< "Indique el archivo de entrada: ";
        cin>>archivoEntrada;
        cout<< "Indique el archivo de salida: ";
        cin>>archivoSalida;
        cout << "Ingrese el tamanio del bloque: ";
        cin >> n;
        cout << "Ingrese el metodo (1 o 2): ";
        cin >> metodo;
        decodificar(archivoEntrada,archivoSalida,n,metodo);
        return 0;
}

}
