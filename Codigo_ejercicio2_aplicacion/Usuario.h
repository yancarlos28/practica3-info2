#ifndef USUARIO_H
#define USUARIO_H
#include<string>
using namespace std;

class Usuario
{
private:
    string documento;
    string clave;
    unsigned int saldo;

public:
    Usuario();
    Usuario(const string &doc, const string &cont, unsigned int sal);

    void setDoc(const string &doc) { documento = doc; }
    void setClave(const string &cont) { clave = cont; }
    void setSaldo(unsigned int sal) { saldo = sal; }

    string getDoc() const { return documento; }
    string getClave() const { return clave; }
    unsigned int getSaldo() const { return saldo; }

    void retirar(unsigned int cantidad);
    unsigned int consultar();
};

#endif // USUARIO_H
