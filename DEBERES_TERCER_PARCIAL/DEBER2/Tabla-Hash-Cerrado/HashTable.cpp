#include "HashTable.h"

// Implementación para enteros
HashTableInt::HashTableInt(int size, int metodo) : size(size), metodo(metodo) {
    table.resize(size, -1);
}

int HashTableInt::hash1(int key) {
    return key % size;
}

int HashTableInt::hash2(int key) {
    return 7 - (key % 7); // Un segundo hash para doble hashing
}

int HashTableInt::resolverColision(int key, int intento) {
    if (metodo == 0) return (hash1(key) + intento) % size;         // Sondeo Lineal
    if (metodo == 1) return (hash1(key) + intento * intento) % size; // Sondeo Cuadrático
    return (hash1(key) + intento * hash2(key)) % size;             // Doble Hashing
}

void HashTableInt::insertar(int key) {
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(key, i);
        if (table[idx] == -1) {
            table[idx] = key;
            std::cout << "Insertado " << key << " en la posición " << idx << "\n";
            return;
        }
    }
    std::cout << "No se pudo insertar, tabla llena.\n";
}

bool HashTableInt::buscar(int key) {
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(key, i);
        if (table[idx] == -1) return false;
        if (table[idx] == key) return true;
    }
    return false;
}

void HashTableInt::eliminar(int key) {
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(key, i);
        if (table[idx] == key) {
            table[idx] = -1;
            std::cout << "Eliminado " << key << " de la posición " << idx << "\n";
            return;
        }
    }
    std::cout << "No se encontró el elemento para eliminar.\n";
}

void HashTableInt::mostrar() {
    std::cout << "Tabla Hash (Enteros):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "]: " << (table[i] == -1 ? "Vacio" : std::to_string(table[i])) << "\n";
    }
}

// Implementación para cadenas de texto
HashTableString::HashTableString(int size, int metodo) : size(size), metodo(metodo) {
    table.resize(size, ""); // Inicializamos con strings vacíos
}

int HashTableString::hashString(const std::string& key) {
    int hash = 0;
    // Recorrer la cadena de derecha a izquierda
    for (int i = key.size() - 1; i >= 0; --i) {
        hash = (hash << 4) + static_cast<int>(key[i]); // Equivale a: hash = hash * 16 + ascii(key[i])
    }
    return hash % size;
}

int HashTableString::resolverColision(int hashValue, int intento) {
    int h1 = hashValue % size;
    if (metodo == 0) {  // Sondeo lineal
        return (h1 + intento) % size;
    } else if (metodo == 1) {  // Sondeo cuadrático
        return (h1 + intento * intento) % size;
    } else if (metodo == 2) {  // Doble Hashing
        int q = 7; // q es un primo menor que size, en este caso 7 para size = 29
        int h2 = q - (hashValue % q);
        if (h2 == 0) h2 = 1; // Nos aseguramos de que h2 no sea cero
        return (h1 + intento * h2) % size;
    }
    return -1;
}

void HashTableString::insertar(const std::string& key) {
    int hashValue = hashString(key);
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(hashValue, i);
        if (table[idx] == "") {
            table[idx] = key;
            return;
        }
    }
    std::cout << "No se pudo insertar, tabla llena.\n";
}

bool HashTableString::buscar(const std::string& key) {
    int hashValue = hashString(key);
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(hashValue, i);
        if (table[idx] == "") return false;
        if (table[idx] == key) return true;
    }
    return false;
}

void HashTableString::eliminar(const std::string& key) {
    int hashValue = hashString(key);
    for (int i = 0; i < size; ++i) {
        int idx = resolverColision(hashValue, i);
        if (table[idx] == key) {
            table[idx] = "";
            std::cout << "Eliminado '" << key << "' de la posicion " << idx << "\n";
            return;
        }
    }
    std::cout << "No se encontrO el elemento para eliminar.\n";
}

void HashTableString::mostrar() {
    std::cout << "Tabla Hash (Cadenas):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "]: " << (table[i] == "" ? "Vacio" : table[i]) << "\n";
    }
}
