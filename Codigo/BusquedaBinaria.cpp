#include <iostream>
#include <list>
#include <string>
#include <functional>
#include "Registro.h"
#include "Auto.h"
#include "BusquedaBinaria.h"

// Función de búsqueda binaria para encontrar el primer registro con el prefijo dado
std::list<Registro>::const_iterator BusquedaBinaria::buscarPrimerRegistroConPrefijo(
    const std::list<Registro>& registros, const std::string& prefijo)
{
    auto inicio = registros.begin();
    auto fin = registros.end();

    while (inicio != fin)
    {
        auto medio = std::next(inicio, std::distance(inicio, fin) / 2);

        if (medio->getAutoPermitido().getPlaca().substr(0, prefijo.size()) == prefijo)
        {
            // Buscar más hacia atrás por si hay otro con el mismo prefijo
            fin = medio;
        }
        else if (medio->getAutoPermitido().getPlaca() < prefijo)
        {
            inicio = std::next(medio);
        }
        else
        {
            fin = medio;
        }
    }

    // Validamos si el prefijo realmente coincide
    if (inicio != registros.end() && inicio->getAutoPermitido().getPlaca().substr(0, prefijo.size()) == prefijo)
    {
        return inicio;
    }
    return registros.end();
}

// Función de búsqueda binaria para encontrar el último registro con el prefijo dado
std::list<Registro>::const_iterator BusquedaBinaria::buscarUltimoRegistroConPrefijo(
    const std::list<Registro>& registros, const std::string& prefijo)
{
    auto inicio = registros.begin();
    auto fin = registros.end();
    auto resultado = registros.end();

    while (inicio != fin)
    {
        auto medio = std::next(inicio, std::distance(inicio, fin) / 2);

        if (medio->getAutoPermitido().getPlaca().substr(0, prefijo.size()) == prefijo)
        {
            resultado = medio; // Guardamos la posición
            inicio = std::next(medio); // Seguimos buscando más adelante
        }
        else if (medio->getAutoPermitido().getPlaca() < prefijo)
        {
            inicio = std::next(medio);
        }
        else
        {
            fin = medio;
        }
    }

    return resultado;
}

// Función para mostrar todos los registros con el prefijo dado
void BusquedaBinaria::mostrarRegistros(const std::list<Registro>& registros, const std::string& prefijo)
{
    auto inicio = buscarPrimerRegistroConPrefijo(registros, prefijo);
    auto fin = buscarUltimoRegistroConPrefijo(registros, prefijo);

    if (inicio == registros.end())
    {
        std::cout << "No se encontraron autos permitidos con el prefijo " << prefijo << std::endl;
        return;
    }

    // Imprimir los autos con el prefijo
    for (auto it = inicio; it != std::next(fin); ++it)
    {
        std::cout << "Auto con placa: " << it->getAutoPermitido().getPlaca()
                  << ", Marca: " << it->getAutoPermitido().getMarca()
                  << ", Color: " << it->getAutoPermitido().getColor() << std::endl;
    }
}
