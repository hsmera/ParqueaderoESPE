#ifndef AUTOSPERMITIDOS_H
#define AUTOSPERMITIDOS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class Auto {
public:
    string placa;
    string marca;
    string color;

    Auto(const string& placa, const string& marca, const string& color)
        : placa(placa), marca(marca), color(color) {}
};

class Propietario {
public:
    string nombre;
    string cedula;
    string correo;

    Propietario(const string& nombre, const string& cedula, const string& correo)
        : nombre(nombre), cedula(cedula), correo(correo) {}
};

class AutosPermitidos {
private:
    struct Registro {
        Auto autoPermitido;
        Propietario propietario;

        Registro(const Auto& autoPermitido, const Propietario& propietario)
            : autoPermitido(autoPermitido), propietario(propietario) {}
    };

    vector<Registro> registros;

    const string archivo = "autos_permitidos.txt";

    void cargarDesdeArchivo();
    void guardarEnArchivo();

public:
    AutosPermitidos();
    void agregarAuto(const Auto& autoPermitido, const Propietario& propietario);
    bool buscarAuto(const string& placa) const;
    void eliminarAuto(const string& placa);
    void mostrarAutos() const;
};

#endif // AUTOSPERMITIDOS_H
