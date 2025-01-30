#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <list>
#include "Auto.h"
#include "Registro.h"

using namespace std;

class Ordenamientos
{
public:
    // Algoritmos de ordenamiento
    static void shellSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);
    static void bubbleSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);
    static void quickSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);
    static void heapSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);
    static void radixSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);
    static void bucketSort(list<Registro> &registros, const function<bool(const Auto &, const Auto &)> &comparator);

    // Guardar autos ordenados en un archivo
    static void guardarEnArchivo(list<Registro> &registros, const string &nombreArchivo);

private:
    // Métodos auxiliares
    static int partition(std::list<Registro> &registros, std::list<Registro>::iterator low, std::list<Registro>::iterator high, const std::function<bool(const Auto &, const Auto &)> &comparator);
    static void quickSortHelper(std::list<Registro> &registros, std::list<Registro>::iterator low, std::list<Registro>::iterator high, const std::function<bool(const Auto &, const Auto &)> &comparator);
    static void heapify(list<Registro> &registros, int n, int i, const function<bool(const Auto &, const Auto &)> &comparator);
    static int obtenerClaveNumerica(const string &clave);
};

#endif // ORDENAMIENTOS_H
