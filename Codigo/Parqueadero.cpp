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
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()


Parqueadero::Parqueadero(HistorialEstacionamiento *historial) : head(nullptr), historial(historial)
{
    inicializarEspacios();
    cargarDesdeArchivo();
}

Parqueadero::~Parqueadero()
{
    Nodo *temp = head;
    if (head)
    {
        do
        {
            Nodo *siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        } while (temp != head);
    }
}

void Parqueadero::inicializarEspacios()
{
    for (int i = 1; i <= capacidad; i++)
    {
        string id = (i < 10 ? "0" : "") + to_string(i);

        // 🔹 Simulación de distancia (puedes cambiar la lógica)
        int distancia = abs(i - 5) * 10; // Ejemplo: distancia en metros desde el espacio 5

        Nodo *nuevoEspacio = new Nodo(id, distancia);

        if (!head)
        {
            head = nuevoEspacio;
            head->siguiente = head;
            head->anterior = head;
        }
        else
        {
            Nodo *ultimo = head->anterior;
            ultimo->siguiente = nuevoEspacio;
            nuevoEspacio->anterior = ultimo;
            nuevoEspacio->siguiente = head;
            head->anterior = nuevoEspacio;
        }
    }
}

void Parqueadero::cargarDesdeArchivo()
{
    ifstream archivoEntrada(archivoParqueadero);
    if (!archivoEntrada.is_open())
    {
        cerr << "No se pudo abrir el archivo " << archivoParqueadero << ". Creando uno nuevo." << endl;
        return;
    }

    Nodo *temp = head;
    string linea;
    while (getline(archivoEntrada, linea))
    {
        stringstream ss(linea);
        string id, placa;
        bool ocupado;

        ss >> id >> ocupado >> placa;

        if (temp && temp->id == id)
        {
            temp->ocupado = ocupado;
            temp->placa = ocupado ? placa : "";
            temp = temp->siguiente;
        }
    }
    archivoEntrada.close();
}

void Parqueadero::guardarEnArchivo()
{
    ofstream archivoSalida(archivoParqueadero, ios::trunc);
    if (!archivoSalida.is_open())
    {
        cerr << "Error al abrir el archivo " << archivoParqueadero << " para guardar." << endl;
        return;
    }

    Nodo *temp = head;
    do
    {
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

    cout << "\n\033[33mReferencia (Entrada)\033[0m\n";  
    cout << "--------------------------------------\n";

    int totalEspacios = capacidad;
    int mitad = totalEspacios / 2; 

    for (int i = 0; i < mitad; ++i) {
        bool esReferencia = (std::stoi(actual->id) == 5);

        // Ajustamos la impresión para que "Entrada" esté en la misma línea que [05]
        if (esReferencia) {
            cout << "\033[33mEntrada \033[0m";  // Color verde
        } else {
            cout << "        ";  // Espaciado normal para mantener alineación
        }

        // Primera columna
        cout << (actual->ocupado ? "\033[31m" : "\033[32m")  
             << "[" << actual->id << "] "
             << "\033[0m"; 

        actual = actual->siguiente;
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

bool Parqueadero::estacionarAuto(const string &placa, string &espacioId)
{
    Nodo *espacioDisponible = nullptr;

    // Verificar si la placa ya está estacionada
    Nodo *temp = head;
    if (temp)
    {
        do
        {
            if (temp->ocupado && temp->placa == placa)
            {
                cout << "El vehiculo con placa " << placa << " ya esta estacionado en el espacio "
                     << temp->id << ".\n";
                return false;
            }
            temp = temp->siguiente;
        } while (temp != head);
    }

    // Buscar un espacio libre aleatoriamente
    espacioDisponible = obtenerEspacioAleatorio();
    
    if (espacioDisponible)
    {
        // Ocupar el espacio con la placa del vehículo
        manejadorEspacios.ocuparEspacio(espacioDisponible, placa);
        guardarEnArchivo(); // Guardar el estado después de la asignación

        espacioId = espacioDisponible->id; // Asignar el ID del espacio ocupado
        cout << "El vehiculo con placa " << placa << " fue estacionado en el espacio "
             << espacioDisponible->id << " (Distancia: " << espacioDisponible->distancia << " metros).\n";
        return true;
    }

    cout << "No hay espacios disponibles en este momento.\n";
    return false;
}

// Función para obtener un espacio libre aleatorio
Nodo* Parqueadero::obtenerEspacioAleatorio()
{
    vector<Nodo*> espaciosLibres;
    Nodo *temp = head;

    if (!temp) return nullptr;

    // Recorrer la lista para obtener los espacios disponibles
    do
    {
        if (!temp->ocupado)
        {
            espaciosLibres.push_back(temp);
        }
        temp = temp->siguiente;
    } while (temp != head);

    // Si no hay espacios libres, retornar nullptr
    if (espaciosLibres.empty()) return nullptr;

    // Inicializar la semilla aleatoria
    srand(time(0));

    // Seleccionar un índice aleatorio
    int index = rand() % espaciosLibres.size();

    return espaciosLibres[index];
}

bool Parqueadero::retirarAuto(const string &placa)
{
    Nodo *temp = head;
    do
    {
        if (temp->ocupado && temp->placa == placa)
        {
            // Intentar registrar la salida en el historial
            if (!this->historial->registrarSalida(placa))
            {
                cout << "Error: No se pudo registrar la salida en el historial. No se liberara el espacio." << endl;
                return false; // No libera el espacio si la salida no se registró
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

// 🔹 Función para convertir la lista circular en un array ordenado
vector<Nodo *> Parqueadero::convertirAArrayOrdenado()
{
    vector<Nodo *> espacios;

    Nodo *temp = head;
    if (!head)
        return espacios; // Si no hay espacios, retornar lista vacía

    do
    {
        if (!temp->ocupado)
        { // Solo considerar espacios disponibles
            espacios.push_back(temp);
        }
        temp = temp->siguiente;
    } while (temp != head);

    // Ordenar el vector por distancia
    sort(espacios.begin(), espacios.end(), [](Nodo *a, Nodo *b)
         { return a->distancia < b->distancia; });

    return espacios;
}

// 🔹 Búsqueda binaria en el array de nodos ordenados
Nodo *Parqueadero::buscarEspacioMasCercano()
{
    vector<Nodo *> espacios = convertirAArrayOrdenado();

    if (espacios.empty())
        return nullptr; // No hay espacios libres

    // Búsqueda binaria: siempre tomamos el primer elemento porque ya está ordenado
    return espacios[0];
}
