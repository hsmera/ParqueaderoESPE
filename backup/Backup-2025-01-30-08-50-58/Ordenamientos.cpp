#include "Ordenamientos.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include "Registro.h"
#include "AutosPermitidos.h"  // Luego incluye AutosPermitidos.h


// ShellSort
void Ordenamientos::shellSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    int n = registros.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        auto it_gap = registros.begin();
        std::advance(it_gap, gap);

        for (auto it = it_gap; it != registros.end(); ++it)
        {
            auto temp = *it;
            auto it_j = it;

            auto it_compare = it;
            std::advance(it_compare, -gap);

            while (it_j != registros.begin() && comparator(temp.autoPermitido, it_compare->autoPermitido))
            {
                *it_j = *it_compare;
                std::advance(it_j, -gap);
                if (it_j != registros.begin())
                    std::advance(it_compare, -gap);
            }
            *it_j = temp;
        }
    }
}

// BubbleSort
void Ordenamientos::bubbleSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    for (auto it_i = registros.begin(); it_i != registros.end(); ++it_i)
    {
        for (auto it_j = registros.begin(), next = std::next(it_j); next != registros.end(); ++it_j, ++next)
        {
            if (comparator(next->autoPermitido, it_j->autoPermitido))
            {
                std::swap(*it_j, *next);
            }
        }
    }
}

// QuickSort
void Ordenamientos::quickSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    if (registros.size() <= 1)
        return;

    auto pivot = registros.back();
    registros.pop_back();

    std::list<Registro> left, right;

    for (const auto &item : registros)
    {
        if (comparator(item.autoPermitido, pivot.autoPermitido))
            left.push_back(item);
        else
            right.push_back(item);
    }

    quickSort(left, comparator);
    quickSort(right, comparator);

    registros = left;
    registros.push_back(pivot);
    registros.insert(registros.end(), right.begin(), right.end());
}

void Ordenamientos::heapSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    int n = registros.size();

    // Construir el heap inicial (max-heap)
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(registros, n, i, comparator);
    }

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; --i)
    {
        auto begin = registros.begin();
        auto end = registros.begin();
        std::advance(end, i);

        // Intercambiar el primer y último elemento del heap
        std::iter_swap(begin, end);

        // Reducir el tamaño del heap y aplicar heapify nuevamente
        heapify(registros, i, 0, comparator);
    }
}

void Ordenamientos::heapify(std::list<Registro> &registros, int n, int i, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    auto largest = i;      // Inicializar el nodo raíz como el más grande
    int left = 2 * i + 1;  // Hijo izquierdo
    int right = 2 * i + 2; // Hijo derecho

    // Iteradores para el nodo actual y los hijos
    auto it_largest = registros.begin();
    std::advance(it_largest, largest);

    auto it_left = registros.begin();
    if (left < n)
        std::advance(it_left, left);

    auto it_right = registros.begin();
    if (right < n)
        std::advance(it_right, right);

    // Comparar el hijo izquierdo con la raíz
    if (left < n && comparator(it_left->autoPermitido, it_largest->autoPermitido))
    {
        largest = left;
        it_largest = it_left;
    }

    // Comparar el hijo derecho con el más grande actual
    if (right < n && comparator(it_right->autoPermitido, it_largest->autoPermitido))
    {
        largest = right;
        it_largest = it_right;
    }

    // Si el nodo más grande no es la raíz
    if (largest != i)
    {
        auto it_root = registros.begin();
        std::advance(it_root, i);

        // Intercambiar el nodo raíz con el más grande
        std::iter_swap(it_root, it_largest);

        // Aplicar heapify al subárbol afectado
        heapify(registros, n, largest, comparator);
    }
}

// RadixSort
void Ordenamientos::radixSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    std::list<std::list<Auto>> buckets(10); // Asume 10 buckets para dígitos 0-9

    // Paso 1: Distribuir elementos en buckets según claves numéricas
    for (const auto &registro : registros)
    {
        int key = obtenerClaveNumerica(registro.autoPermitido.getPlaca()) % 10; // Obtén el dígito relevante
        auto it = std::next(buckets.begin(), key); // Accede al bucket correspondiente
        it->push_back(registro.autoPermitido); // Inserta en el bucket
    }

    // Paso 2: Combinar buckets de nuevo en la lista original
    registros.clear();
    for (const auto &bucket : buckets)
    {
        for (const auto &autoItem : bucket)
        {
            registros.push_back(Registro(autoItem, Propietario("Nombre", "Cedula", "Correo"))); // Reconstruye la lista de registros
        }
    }
}

// BucketSort
void Ordenamientos::bucketSort(std::list<Registro> &registros, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    int n = registros.size();
    if (n <= 0)
        return;

    std::list<std::list<Auto>> buckets(n);

    for (const auto &registro : registros)
    {
        const Auto &autoItem = registro.autoPermitido;
        int index = n * obtenerClaveNumerica(autoItem.placa) / 1000;

        if (index >= 0 && index < buckets.size())
        {
            auto it = std::next(buckets.begin(), index);
            it->push_back(autoItem);
        }
    }

    registros.clear();
    for (auto &bucket : buckets)
    {
        bucket.sort(comparator);

        for (const auto &autoItem : bucket)
        {
            registros.push_back(Registro(autoItem, Propietario("Nombre", "Cedula", "Correo")));
        }
    }
}

// Guardar en archivo
void Ordenamientos::guardarEnArchivo(std::list<Registro> &registros, const std::string &nombreArchivo)
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    for (const auto &registro : registros)
    {
        const Auto &autoItem = registro.autoPermitido;
        archivo << autoItem.placa << "," << autoItem.marca << "," << autoItem.color << std::endl;
    }

    archivo.close();
}

int Ordenamientos::obtenerClaveNumerica(const std::string &cadena)
{
    int claveNumerica = 0;
    for (char c : cadena)
    {
        claveNumerica += static_cast<int>(c); // Sumar valores ASCII de los caracteres
    }
    return claveNumerica;
}

int Ordenamientos::partition(std::list<Registro> &registros, std::list<Registro>::iterator low, std::list<Registro>::iterator high, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    Auto pivot = high->autoPermitido; // Seleccionar el último elemento como pivote
    auto i = low;                     // Punto para dividir los menores del pivote

    for (auto j = low; j != high; ++j)
    {
        if (comparator(j->autoPermitido, pivot))
        {
            std::swap(i->autoPermitido, j->autoPermitido); // Intercambiar elementos
            ++i;                                           // Avanzar el iterador
        }
    }
    std::swap(i->autoPermitido, high->autoPermitido); // Mover el pivote a su posición correcta
    return std::distance(registros.begin(), i);       // Retornar la posición del pivote
}

void Ordenamientos::quickSortHelper(std::list<Registro> &registros, std::list<Registro>::iterator low, std::list<Registro>::iterator high, const std::function<bool(const Auto &, const Auto &)> &comparator)
{
    if (std::distance(low, high) > 0)
    {
        auto pivotPos = partition(registros, low, high, comparator);
        auto pivotIt = std::next(registros.begin(), pivotPos);

        if (low != pivotIt) // Evitar desbordamiento
        {
            quickSortHelper(registros, low, std::prev(pivotIt), comparator);
        }

        if (pivotIt != high)
        {
            quickSortHelper(registros, std::next(pivotIt), high, comparator);
        }
    }
}
