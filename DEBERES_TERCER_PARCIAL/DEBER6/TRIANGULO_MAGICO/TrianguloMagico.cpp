#include <iostream>
#include <graphics.h>
#include <vector>
#include <algorithm>

using namespace std;

// Función para verificar si una combinación de 3 números suma un valor dado
bool sumaValida(vector<int> nums, int suma) {
    return (nums[0] + nums[1] + nums[2]) == suma;
}

// Función para encontrar combinaciones válidas de esquinas
vector<int> encontrarEsquinas(int suma) {
    vector<int> impares = {1, 3, 5};
    vector<int> pares = {2, 4, 6};
    
    if (sumaValida(impares, suma)) return impares;
    if (sumaValida(pares, suma)) return pares;

    return {}; // Retorna vacío si no encuentra solución
}

// Función para encontrar los números restantes para el centro
vector<int> encontrarCentro(int suma, vector<int> esquinas) {
    vector<int> numeros = {1, 2, 3, 4, 5, 6};
    vector<int> centro;

    // Filtrar los números no usados en las esquinas
    for (int num : numeros) {
        if (find(esquinas.begin(), esquinas.end(), num) == esquinas.end()) {
            centro.push_back(num);
        }
    }

    // Buscar combinación válida
    do {
        if (sumaValida({esquinas[0], centro[0], esquinas[1]}, suma) &&
            sumaValida({esquinas[0], centro[1], esquinas[2]}, suma) &&
            sumaValida({esquinas[1], centro[2], esquinas[2]}, suma)) {
            return centro;
        }
    } while (next_permutation(centro.begin(), centro.end()));

    return {};
}

// Función para dibujar el triángulo mágico
void dibujarTriangulo(vector<int> esquinas, vector<int> centro) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Coordenadas de los círculos con las posiciones corregidas
    int x[] = {300, 250, 350, 200, 300, 400};
    int y[] = {100, 200, 200, 300, 300, 300};

    // Asignación corregida de valores en su nueva posición
    int valores[6] = {esquinas[0], centro[0], centro[1], esquinas[1], centro[2], esquinas[2]};

    // Dibujar círculos y colocar números
    for (int i = 0; i < 6; i++) {
        circle(x[i], y[i], 30);
        char num[2];
        sprintf(num, "%d", valores[i]);
        outtextxy(x[i] - 5, y[i] - 5, num);
    }

    getch();
    closegraph();
}

int main() {
    int sumaMagica;
    cout << "Ingrese la suma magica de cada lado: ";
    cin >> sumaMagica;

    // Paso 1: Calcular suma de las esquinas
    int sumaEsquinas = 3 * sumaMagica - 21;
    cout << "Paso 1: Suma de esquinas = " << sumaEsquinas << endl;

    // Paso 2: Encontrar combinaciones válidas para las esquinas
    vector<int> esquinas = encontrarEsquinas(sumaEsquinas);
    if (esquinas.empty()) {
        cout << "No se encontro solucion para las esquinas" << endl;
        return 0;
    }
    cout << "Paso 2: Esquinas encontradas -> " << esquinas[0] << " (a), " << esquinas[1] << " (b), " << esquinas[2] << " (c)" << endl;

    // Paso 3: Encontrar los números restantes para completar el triángulo
    vector<int> centro = encontrarCentro(sumaMagica, esquinas);
    if (centro.empty()) {
        cout << "No se encontro solucion para el centro." << endl;
        return 0;
    }
    cout << "Paso 3: Numeros centrales encontrados -> " << centro[0] << ", " << centro[1] << ", " << centro[2] << endl;

    // Mostrar el proceso de cálculo
    cout << "\nVerificacion de sumas magicas:\n";
    cout << "a + _ + c = " << esquinas[0] << " + " << centro[1] << " + " << esquinas[2] << " = " << sumaMagica << endl;
    cout << "a + _ + b = " << esquinas[0] << " + " << centro[0] << " + " << esquinas[1] << " = " << sumaMagica << endl;
    cout << "b + _ + c = " << esquinas[1] << " + " << centro[2] << " + " << esquinas[2] << " = " << sumaMagica << endl;

    // Mostrar el triángulo mágico en la consola con la nueva distribución
    cout << "\nTriangulo magico construido:\n";
    cout << "      " << esquinas[0] << endl;
    cout << "    " << centro[0] << "   " << centro[1] << endl;
    cout << "  " << esquinas[1] << "   " << centro[2] << "   " << esquinas[2] << endl;

    // Dibujar el triángulo mágico con la distribución correcta
    dibujarTriangulo(esquinas, centro);

    return 0;
}
