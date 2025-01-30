#ifndef BACKUP_H
#define BACKUP_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <conio.h>

using namespace std;
namespace fs = filesystem;

class Backup {
public:
    void realizarBackupTodos();
    void realizarBackupEspecifico();
    void eliminarArchivo();
    void recuperarBackup();
    string obtenerNombreBackup();
};

#endif
