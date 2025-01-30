/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Proyecto Primer Parcial                             *
 * Autor:                          Kerlly Chiriboga,Heidy Mera                         *
 * Fecha de creacion:              06/12/2024                                          *
 * Fecha de modificacion:          06/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "Parqueadero.h"

Parqueadero::Parqueadero(HistorialEstacionamiento* historial) : head(nullptr), historial(historial) {
    inicializarEspacios();
    cargarDesdeArchivo();
}

Parqueadero::~Parqueadero() {
    Nodo* temp = head;
    if (head) {
        do {
            Nodo* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        } while (temp != head);
    }
}

void Parqueadero::inicializarEspacios() {
    for (int i = 1; i <= capacidad; i++) {
        string id = (i < 10 ? "0" : "") + to_string(i);
        Nodo* nuevoEspacio = manejadorEspacios.crearEspacio(id);

        if (!head) {
            head = nuevoEspacio;
            head->siguiente = head;
            head->anterior = head;
        } else {
            Nodo* ultimo = head->anterior;
            ultimo->siguiente = nuevoEspacio;
            nuevoEspacio->anterior = ultimo;
            nuevoEspacio->siguiente = head;
            head->anterior = nuevoEspacio;
        }
    }
}

void Parqueadero::cargarDesdeArchivo() {
    ifstream archivoEntrada(archivoParqueadero);
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo " << archivoParqueadero << ". Creando uno nuevo." << endl;
        return;
    }

    Nodo* temp = head;
    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string id, placa;
        bool ocupado;

        ss >> id >> ocupado >> placa;

        if (temp && temp->id == id) {
            temp->ocupado = ocupado;
            temp->placa = ocupado ? placa : "";
            temp = temp->siguiente;
        }
    }
    archivoEntrada.close();
}

void Parqueadero::guardarEnArchivo() {
    ofstream archivoSalida(archivoParqueadero, ios::trunc);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo " << archivoParqueadero << " para guardar." << endl;
        return;
    }

    Nodo* temp = head;
    do {
        archivoSalida << temp->id << " "
                      << temp->ocupado << " "
                      << (temp->ocupado ? temp->placa : "") << "\n";
        temp = temp->siguiente;
    } while (temp != head);

    archivoSalida.close();
}

void Parqueadero::mostrarEstado() const {
    Nodo* actual = head;
    if (!actual) {
        cout << "No hay espacios de estacionamiento disponibles.\n";
        return;
    }

    cout << "\n\033[33mReferencia (Entrada)\033[0m\n";  // Color amarillo para la referencia
    cout << "--------------------------------------\n";

    // Determinar el número total de espacios y la mitad para dividir en dos columnas
    int totalEspacios = capacidad;
    int mitad = totalEspacios / 2; 

    // Mostrar en dos columnas
    for (int i = 0; i < mitad; ++i) {
        // Primera columna
        cout << (actual->ocupado ? "\033[31m" : "\033[32m") // Rojo ocupado, verde libre
             << "[" << actual->id << "] "
             << "\033[0m";  // Reset color
        actual = actual->siguiente;

        // Espaciado para alinear las dos columnas
        cout << "     ";  

        // Segunda columna
        if (actual) {
            cout << (actual->ocupado ? "\033[31m" : "\033[32m") 
                 << "[" << actual->id << "] "
                 << "\033[0m";
            actual = actual->siguiente;
        }

        cout << endl;
    }

    cout << "--------------------------------------\n";
}

bool Parqueadero::estacionarAuto(const string& placa, string& espacioId) {
    Nodo* espacioDisponible = nullptr;

    if (espacioId.empty()) {
        // Si no se especifica un espacio, buscar el más cercano con búsqueda binaria
        espacioDisponible = buscarEspacioCercano();
    } else {
        // Buscar el nodo correspondiente al espacioId
        Nodo* temp = head;
        do {
            if (temp->id == espacioId) {
                if (!temp->ocupado) {
                    espacioDisponible = temp;
                } else {
                    cout << "El espacio " << espacioId << " ya esta ocupado.\n";
                    return false;
                }
                break;
            }
            temp = temp->siguiente;
        } while (temp != head);

        if (!espacioDisponible) {
            cout << "El espacio " << espacioId << " no existe.\n";
            return false;
        }
    }

    if (espacioDisponible) {
        // Ocupar el espacio con la placa del vehículo
        manejadorEspacios.ocuparEspacio(espacioDisponible, placa);
        guardarEnArchivo();  // Guardar el estado después de la asignación

        espacioId = espacioDisponible->id; // Actualizar espacioId con el ID asignado
        cout << "El vehiculo con placa " << placa << " fue estacionado en el espacio " << espacioId << ".\n";
        return true;
    }

    cout << "No hay espacios disponibles en este momento.\n";
    return false;
}

bool Parqueadero::retirarAuto(const string& placa) {
    Nodo* temp = head;
    do {
        if (temp->ocupado && temp->placa == placa) {
            // Intentar registrar la salida en el historial
            if (!this->historial->registrarSalida(placa)) {
                cout << "Error: No se pudo registrar la salida en el historial. No se liberara el espacio." << endl;
                return false;  // No libera el espacio si la salida no se registró
            }

            manejadorEspacios.liberarEspacio(temp);
            guardarEnArchivo();
            cout << "Vehiculo con placa " << placa << " retirado del espacio " << temp->id << "." << endl;
            return true;
        }
        temp = temp->siguiente;
    } while (temp != head);

    cout << "No se encontro un auto con la placa " << placa << "." << endl;
    return false;
}

Nodo* Parqueadero::buscarEspacioCercano() {
    Nodo* actual = head;
    do {
        if (!actual->ocupado) {  // Si el espacio está libre
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != head);
    
    return nullptr;  // Si no se encuentra un espacio libre
}