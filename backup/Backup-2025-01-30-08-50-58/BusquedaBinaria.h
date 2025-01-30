#ifndef BUSQUEDABINARIA_H
#define BUSQUEDABINARIA_H

#include <list>
#include <string>
#include "Registro.h"  // Asegúrate de que estas clases existan
#include "Auto.h"      // Asegúrate de que estas clases existan

class BusquedaBinaria {
public:
    // Función de búsqueda binaria para encontrar el primer registro con el prefijo dado
    static std::list<Registro>::const_iterator buscarPrimerRegistroConPrefijo(
        const std::list<Registro>& registros, const std::string& prefijo);
    
    static std::list<Registro>::const_iterator buscarUltimoRegistroConPrefijo(
        const std::list<Registro>& registros, const std::string& prefijo);

    // Función para mostrar todos los registros con el prefijo dado
    static void mostrarRegistros(const std::list<Registro>& registros, const std::string& prefijo);
};

#endif // BUSQUEDABINARIA_H
