#ifndef AUTOSPERMITIDOS_H
#define AUTOSPERMITIDOS_H

#include "Auto.h"
#include "Propietario.h"
#include "Registro.h"  // Incluir el encabezado de Registro
#include <vector>
#include <string>

class AutosPermitidos {
private:
    std::vector<Registro> registros;  // Vector de objetos Registro
    const std::string archivo = "autos_permitidos.txt";

    void cargarDesdeArchivo();
    void guardarEnArchivo();
    void guardarPropietarios();

public:
    AutosPermitidos();
    void agregarAuto(const Auto& autoPermitido, const Propietario& propietario);
    bool buscarAuto(const std::string& placa) const;
    void eliminarAuto(const std::string& placa);
    void mostrarAutos() const;
    void mostrarAutoPorPlaca(const string& placa) const;
    void mostrarPropietarios();
};

#endif // AUTOSPERMITIDOS_H
