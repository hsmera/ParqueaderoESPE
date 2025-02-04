// main.cpp
#include "HashTable.h"

int main() {
    int size, choice, key;
    std::cout << "Enter size of hash table: ";
    std::cin >> size;
    HashTable ht(size);

    // No crear un hilo adicional, mover renderización al bucle principal
    while (true) {
        std::cout << "\n1. Insert\n2. Delete\n3. Find\n4. Display\n5. Exit\nEnter choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                ht.insert(key);
                break;
            case 2:
                std::cout << "Enter key to delete: ";
                std::cin >> key;
                ht.remove(key);
                break;
            case 3:
                std::cout << "Enter key to find: ";
                std::cin >> key;
                if (ht.find(key))
                    std::cout << "Key found!" << std::endl;
                else
                    std::cout << "Key not found!" << std::endl;
                break;
            case 4:
                ht.display();
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }

        // Renderizar la tabla
        ht.drawTable();
    }

    return 0;
}
