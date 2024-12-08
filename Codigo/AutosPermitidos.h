#ifndef AUTOS_PERMITIDOS_H
#define AUTOS_PERMITIDOS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Auto.h"
#include "Propietario.h"
using namespace std;

class AutosPermitidos {
private:
    vector<pair<Auto, Propietario>> autosPermitidos; 
    const string archivo = "autos_permitidos.txt";   

const vector<pair<Auto, Propietario>>& getAutosPermitidos() const {
    return autosPermitidos;
}

public:
    void cargarDatos();                      
    void guardarDatos() const;               
    void agregarAuto(const Auto& autoObj, const Propietario& propietario); 
    void mostrarAutos() const;
    bool eliminarAuto(const string& placa);  
    bool buscarAuto(const string& placa) const; 
};

#endif