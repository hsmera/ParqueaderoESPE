#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
using namespace std;

class Propietario {
public:
    string nombre;
    string cedula;
    string correo;

    Propietario(const string& nombre, const string& cedula, const string& correo);
};

#endif // PROPIETARIO_H
