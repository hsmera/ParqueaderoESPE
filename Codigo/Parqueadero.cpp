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

// Constructor: Inicializa el parqueadero
Parqueadero::Parqueadero() : head(nullptr) {
    inicializarEspacios();
    cargarDesdeArchivo();
}

// Destructor: Libera la memoria asignada
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

// Inicializar espacios en la lista doblemente enlazada circular
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

// Cargar estado del parqueadero desde el archivo
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

// Guardar estado del parqueadero en el archivo
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

// Mostrar el estado actual del parqueadero
void Parqueadero::mostrarEstado() const {
    Nodo* actual = head;
    cout << "\nEstado del Parqueadero:\n";

    // Imprime los primeros 6 espacios en la parte superior
    for (int i = 0; i < 6; ++i) {
        if (actual == nullptr) break;  // Si no hay más nodos, salimos
        cout << (actual->ocupado ? "\033[31m" : "\033[0m") << "[" << actual->id << "] ";
        actual = actual->siguiente;
    }
    cout << "\n";

    // Imprime los siguientes 6 espacios en la parte inferior
    for (int i = 0; i < 6; ++i) {
        if (actual == nullptr) break;  // Si no hay más nodos, salimos
        cout << (actual->ocupado ? "\033[31m" : "\033[0m") << "[" << actual->id << "] ";
        actual = actual->siguiente;
    }
    cout << "\033[0m\n";  // Resetea el color al valor por defecto
}

// Estacionar un auto en un espacio específico
bool Parqueadero::estacionarAuto(const string& placa, const string& espacioId) {
    Nodo* temp = head;

    // Verificar si la placa ya está estacionada en algún espacio
    do {
        if (temp->placa == placa) {
            cout << "El vehiculo con placa " << placa << " ya esta estacionado en el espacio " << temp->id << "." << endl;
            return false;
        }
        temp = temp->siguiente;
    } while (temp != head);

    // Reiniciar la búsqueda para ubicar el espacio especificado
    temp = head;
    do {
        if (temp->id == espacioId) {
            if (!temp->ocupado) {
                manejadorEspacios.ocuparEspacio(temp, placa);
                guardarEnArchivo();
                cout << "El vehiculo con placa " << placa << " fue estacionado en el espacio " << espacioId << "." << endl;
                return true;
            } else {
                cout << "El espacio " << espacioId << " ya esta ocupado." << endl;
                return false;
            }
        }
        temp = temp->siguiente;
    } while (temp != head);

    cout << "Espacio " << espacioId << " no encontrado." << endl;
    return false;
}

bool Parqueadero::retirarAuto(const string& placa) {
    Nodo* temp = head;
    do {
        if (temp->ocupado && temp->placa == placa) {
            manejadorEspacios.liberarEspacio(temp);
            guardarEnArchivo();
            return true;
        }
        temp = temp->siguiente;
    } while (temp != head);

    cout << "No se encontro un auto con la placa " << placa << "." << endl;
    return false;
}