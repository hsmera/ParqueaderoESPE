#include "Propietario.h"

Propietario::Propietario() : nombre(""), cedula(""), correo("") {}
Propietario::Propietario(string nombre, string cedula, string correo)
    : nombre(nombre), cedula(cedula), correo(correo) {}

string Propietario::getNombre() const { return nombre; }
string Propietario::getCedula() const { return cedula; }
string Propietario::getCorreo() const { return correo; }
void Propietario::setNombre(const string& nombre) { this->nombre = nombre; }
void Propietario::setCedula(const string& cedula) { this->cedula = cedula; }
void Propietario::setCorreo(const string& correo) { this->correo = correo; }

string Propietario::toString() const {
    return nombre + "," + cedula + "," + correo;
}
