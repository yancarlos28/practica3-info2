#include "funciones_encriptar_desencriptar.h"
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
string unir_bloques(string* bloques, int cantidadBloques) {
    string resultado;
    for (int i = 0; i < cantidadBloques; i++)
        resultado += bloques[i];
    return resultado;
}
void escribir_binario(string bits, string nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);
    unsigned char byte = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        byte = (byte << 1) | (bits[i] == '1');
        if ((i + 1) % 8 == 0) {
            archivo.write(reinterpret_cast<char*>(&byte), 1);
            byte = 0;
        }
    }
    // último byte si no es múltiplo de 8
    size_t resto = bits.size() % 8;
    if (resto != 0) {
        byte <<= (8 - resto);
        archivo.write(reinterpret_cast<char*>(&byte), 1);
    }
    archivo.close();
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
// Invertir las posiciones múltiplos de k (1,2,3... ⇒ 1-based)
string invertirCadaKBits(string bloque, int k) {
    string res = bloque;
    for (int i = 0; i < (int)bloque.size(); ++i) {
        int pos1 = i + 1;                 // posición 1-basada
        if (pos1 % k == 0) {
            res[i] = (bloque[i] == '0') ? '1' : '0';
        }
    }
    return res;
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

string* decodificarMetodo1(string* codificados, int cantidadBloques) {
    string* decodificados = new string[cantidadBloques];
    if (cantidadBloques == 0) return decodificados;

    // Primer bloque: invertir todo
    decodificados[0] = invertirBits(codificados[0]);

    // Siguientes bloques
    for (int i = 1; i < cantidadBloques; i++) {
        int unos, ceros;
        contarBits(decodificados[i - 1], unos, ceros);

        if (unos == ceros) {
            decodificados[i] = invertirBits(codificados[i]);
        } else if (ceros > unos) {
            decodificados[i] = invertirCadaKBits(codificados[i], 2);
        } else {
            decodificados[i] = invertirCadaKBits(codificados[i], 3);
        }
    }
    return decodificados;
}

string decodificarBloqueMetodo2(string bloque) {
    int n = bloque.size();
    string resultado(n, '0');

    for (int i = 0; i < n - 1; i++) {
        resultado[i] = bloque[i + 1];
    }
    resultado[n - 1] = bloque[0];  // el primero pasa al final

    return resultado;
}

string* decodificarMetodo2(string* codificados, int cantidadBloques) {
    string* decodificados = new string[cantidadBloques];

    for (int i = 0; i < cantidadBloques; i++) {
        decodificados[i] = decodificarBloqueMetodo2(codificados[i]);
    }

    return decodificados;
}
