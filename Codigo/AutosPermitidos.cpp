#include "AutosPermitidos.h"

void AutosPermitidos::cargarDatos() {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }
    
    string linea;
    while (getline(file, linea)) {
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        size_t pos3 = linea.find(',', pos2 + 1);
        size_t pos4 = linea.find(',', pos3 + 1);
        size_t pos5 = linea.find(',', pos4 + 1);

        string placa = linea.substr(0, pos1);
        string marca = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string color = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        string nombre = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        string cedula = linea.substr(pos4 + 1, pos5 - pos4 - 1);
        string correo = linea.substr(pos5 + 1);

        Auto autoObj(placa, marca, color);
        Propietario propietario(nombre, cedula, correo);

        autosPermitidos.push_back(make_pair(autoObj, propietario));
    }
    file.close();
}

void AutosPermitidos::guardarDatos() const {
    ofstream file(archivo, ios::trunc);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    for (const auto& pair : autosPermitidos) {
        file << pair.first.toString() << "," << pair.second.toString() << endl;
    }
    file.close();
}

void AutosPermitidos::agregarAuto(const Auto& autoObj, const Propietario& propietario) {
    for (const auto& pair : autosPermitidos) {
        if (pair.first.getPlaca() == autoObj.getPlaca()) {
            cerr << "Error: Ya existe un auto con la placa " << autoObj.getPlaca() << endl;
            return;
        }
    }
    
    autosPermitidos.push_back(make_pair(autoObj, propietario));
    guardarDatos();
    cout << "Auto agregado correctamente." << endl;
}

void AutosPermitidos::mostrarAutos() const {
    for (const auto& pair : autosPermitidos) {
        cout << "Placa: " << pair.first.getPlaca()
             << ", Marca: " << pair.first.getMarca()
             << ", Color: " << pair.first.getColor()
             << ", Propietario: " << pair.second.getNombre()
             << ", Cedula: " << pair.second.getCedula()
             << ", Correo: " << pair.second.getCorreo() << endl;
    }
}

bool AutosPermitidos::eliminarAuto(const string& placa) {
    for (auto it = autosPermitidos.begin(); it != autosPermitidos.end(); ++it) {
        if (it->first.getPlaca() == placa) {
            autosPermitidos.erase(it);
            guardarDatos(); // Actualizar archivo
            cout << "Auto con placa " << placa << " eliminado correctamente." << endl;
            return true;
        }
    }
    cout << "No se encontró un auto con la placa: " << placa << endl;
    return false;
}

bool AutosPermitidos::buscarAuto(const string& placa) const {
    for (const auto& pair : autosPermitidos) {
        if (pair.first.getPlaca() == placa) {
            cout << "Auto encontrado: " << endl;
            cout << "Placa: " << pair.first.getPlaca()
                 << ", Marca: " << pair.first.getMarca()
                 << ", Color: " << pair.first.getColor()
                 << ", Propietario: " << pair.second.getNombre()
                 << ", Cedula: " << pair.second.getCedula()
                 << ", Correo: " << pair.second.getCorreo() << endl;
            return true;
        }
    }

    cout << "No se encontró un auto con la placa: " << placa << endl;
    return false;
}