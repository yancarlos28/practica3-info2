#include "funciones.h"
#include <fstream>
#include <bitset>

//funcion leer archivo a binario y lo retorna en string
string leer_archivo_binario(string nombreArchivo){

    ifstream archivo(nombreArchivo, ios::binary);
    //if (!archivo.is_open()) {
        //cout << "Error: no se pudo abrir el archivo." << endl;
        //;
    //}

    unsigned char byte;
    string binarioCompleto; // aquí guardaremos todos los bits

    while (archivo.read(reinterpret_cast<char*>(&byte), 1)) {
        bitset<8> bits(byte);              // convierte el byte a binario
        binarioCompleto += bits.to_string(); // concatena los 8 bits al string
    }
    archivo.close();

    return binarioCompleto;
}

//funcion para partir en bloques el string en un arreglo de string segun la semilla n
string* partir_en_n(string archivo_binario, int n, int &cantidadBloques) {
    int longitud = archivo_binario.size();

    // calculamos cuántos bloques habrá
    cantidadBloques = longitud / n;
    if (longitud % n != 0) cantidadBloques++;

    // creamos un arreglo dinámico de strings
    string *bloques = new string[cantidadBloques];

    // llenamos el arreglo con los bloques de n bits
    int indice = 0;
    for (int i = 0; i < longitud; i += n) {
        string bloque = archivo_binario.substr(i, n);
        if (bloque.size() < n)  // rellenamos con '0' el último bloque
            bloque.append(n - bloque.size(), '0');
        bloques[indice] = bloque;
        indice++;
    }

    return bloques; // devolvemos el arreglo
}
//invierte cada bloque si esta en 0 a 1 y si es 1 a 0
string invertirBits(string bloque) {
    for (int i = 0; i < bloque.size(); i++) {
        bloque[i] = (bloque[i] == '0') ? '1' : '0';
    }
    return bloque;
}
//contar cuantos ceros y unos tiene cada bloque
void contarBits(string bloque, int &unos, int &ceros) {
    unos = 0;
    ceros = 0;
    for (int i = 0; i < bloque.size(); i++) {
        if (bloque[i] == '1') unos++;
        else ceros++;
    }
}
//invertir cada k bits para el metodo 1
string invertirCadaKBits(string bloque, int k) {
    string resultado = bloque;
    bool invertir = true; // alternamos entre invertir y dejar igual

    for (int i = 0; i < bloque.size(); i += k) {
        if (invertir) {
            for (int j = i; j < i + k && j < bloque.size(); j++) {
                resultado[j] = (bloque[j] == '0') ? '1' : '0';
            }
        }
        invertir = !invertir;
    }
    return resultado;
}
//codificar por el metodo 1
string* codificarMetodo1(string *bloques, int cantidadBloques) {
    string *codificados = new string[cantidadBloques];

    if (cantidadBloques == 0) return codificados;

    // Primer bloque: invertir todos los bits
    codificados[0] = invertirBits(bloques[0]);

    // Los siguientes dependen del bloque anterior SIN CODIFICAR
    for (int i = 1; i < cantidadBloques; i++) {
        int unos, ceros;
        contarBits(bloques[i - 1], unos, ceros);

        if (unos == ceros) {
            codificados[i] = invertirBits(bloques[i]);
        } else if (ceros > unos) {
            codificados[i] = invertirCadaKBits(bloques[i], 2);
        } else { // más 1s que 0s
            codificados[i] = invertirCadaKBits(bloques[i], 3);
        }
    }
    return codificados;
}

string codificarBloqueMetodo2(string bloque) {
    int n = bloque.size();
    string resultado(n, '0');  // crea una cadena con n caracteres '0'

    resultado[0] = bloque[n - 1];     // primer bit ← último
    for (int i = 1; i < n; i++) {
        resultado[i] = bloque[i - 1]; // los demás se recorren a la derecha
    }

    return resultado;
}

string* codificarMetodo2(string *bloques, int cantidadBloques) {
    string *codificados = new string[cantidadBloques];

    for (int i = 0; i < cantidadBloques; i++) {
        codificados[i] = codificarBloqueMetodo2(bloques[i]);
    }

    return codificados;
}
