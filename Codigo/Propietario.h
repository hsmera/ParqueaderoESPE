#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <string>
using namespace std;

class Propietario {
private:
    string nombre;
    string cedula;
    string correo;

public:
    Propietario();
    Propietario(string nombre, string cedula, string correo);

    string getNombre() const;
    string getCedula() const;
    string getCorreo() const;
    void setNombre(const string& nombre);
    void setCedula(const string& cedula);
    void setCorreo(const string& correo);

    string toString() const; // Representación como cadena
};

#endif

