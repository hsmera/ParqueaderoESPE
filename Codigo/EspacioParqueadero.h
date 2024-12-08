#ifndef ESPACIOPARQUEADERO_H
#define ESPACIOPARQUEADERO_H

#include <string>
using namespace std;

struct Nodo {
    string id; 
    bool ocupado; // true si está ocupado, false si está libre
    string placa;        
    string marca;       
    string color;        
    string nombrePropietario; 
    string cedula;       
    string correo;       
    string fechaHoraIngreso; 
    string fechaHoraSalida; 
    Nodo* siguiente; 
    Nodo* anterior; 
};

class EspacioParqueadero {
public:
    Nodo* crearListaCircular(int cantidad);   // Inicializa la lista circular con `cantidad` nodos
    Nodo* buscarEspacio(string id, Nodo* inicio); // Busca un espacio por ID
    bool placaYaEstacionada(const string& placa, Nodo* inicio);
    void ocuparEspacio(Nodo* espacio, const string& placa, Nodo* inicio);
    void liberarEspacio(Nodo* espacio);      // Marca un espacio como libre
    string obtenerEstado(Nodo* inicio);      // Devuelve el estado de todos los espacios
};

#endif
