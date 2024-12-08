#include "HistorialEstacionamiento.h"

// Constructor: carga el historial desde el archivo
HistorialEstacionamiento::HistorialEstacionamiento() {
    cargarDesdeArchivo();
}

// Obtener la fecha y hora actual como string
string HistorialEstacionamiento::obtenerFechaHoraActual() const {
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

// Cargar historial desde el archivo
void HistorialEstacionamiento::cargarDesdeArchivo() {
    ifstream archivoEntrada(archivoHistorial);
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo " << archivoHistorial << ". Creando uno nuevo." << endl;
        return;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string placa, espacioId, fechaHoraIngreso, fechaHoraSalida;

        getline(ss, placa, ',');
        getline(ss, espacioId, ',');
        getline(ss, fechaHoraIngreso, ',');
        getline(ss, fechaHoraSalida, ',');

        historial.emplace_back(placa, espacioId, fechaHoraIngreso, fechaHoraSalida);
    }
    archivoEntrada.close();
}

// Guardar historial en el archivo
void HistorialEstacionamiento::guardarEnArchivo() {
    ofstream archivoSalida(archivoHistorial, ios::trunc);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo " << archivoHistorial << " para guardar." << endl;
        return;
    }

    for (const auto& registro : historial) {
        archivoSalida << registro.placa << ","
                      << registro.espacioId << ","
                      << registro.fechaHoraIngreso << ","
                      << registro.fechaHoraSalida << "\n";
    }
    archivoSalida.close();
}

// Registrar la entrada de un auto
void HistorialEstacionamiento::registrarEntrada(const string& placa, const string& espacioId) {
    string fechaHora = obtenerFechaHoraActual();
    historial.emplace_back(placa, espacioId, fechaHora);
    guardarEnArchivo();
    cout << "Entrada registrada: Placa " << placa << ", Espacio " << espacioId 
         << ", Fecha/Hora: " << fechaHora << endl;
}

// Registrar la salida de un auto
void HistorialEstacionamiento::registrarSalida(const string& placa) {
    for (auto& registro : historial) {
        if (registro.placa == placa && registro.fechaHoraSalida.empty()) {
            registro.fechaHoraSalida = obtenerFechaHoraActual();
            guardarEnArchivo();
            cout << "Salida registrada: Placa " << placa 
                 << ", Fecha/Hora Salida: " << registro.fechaHoraSalida << endl;
            return;
        }
    }
    cout << "No se encontró una entrada activa para la placa " << placa << "." << endl;
}

// Mostrar todo el historial
void HistorialEstacionamiento::mostrarHistorial() const {
    if (historial.empty()) {
        cout << "No hay registros en el historial." << endl;
        return;
    }

    cout << "Historial de Estacionamiento:\n";
    for (const auto& registro : historial) {
        cout << "Placa: " << registro.placa 
             << ", Espacio: " << registro.espacioId 
             << ", Ingreso: " << registro.fechaHoraIngreso 
             << ", Salida: " << (registro.fechaHoraSalida.empty() ? "Aún en el parqueadero" : registro.fechaHoraSalida)
             << endl;
    }
}

// Buscar historial por placa
string HistorialEstacionamiento::buscarHistorial(const string& placa) const {
    string resultado;
    for (const auto& registro : historial) {
        if (registro.placa == placa) {
            resultado += "Placa: " + registro.placa 
                      + ", Espacio: " + registro.espacioId 
                      + ", Ingreso: " + registro.fechaHoraIngreso 
                      + ", Salida: " + (registro.fechaHoraSalida.empty() ? "Aún en el parqueadero" : registro.fechaHoraSalida) 
                      + "\n";
        }
    }
    return resultado.empty() ? "No se encontró historial para la placa " + placa : resultado;
}
