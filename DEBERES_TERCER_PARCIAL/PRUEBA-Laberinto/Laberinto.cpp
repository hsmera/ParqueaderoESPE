#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <graphics.h>

using namespace std;

// Estructura del laberinto
vector<vector<int>> generarLaberinto(int n) {
    vector<vector<int>> laberinto(n, vector<int>(n, 0));

    srand(time(0));

    // Posición aleatoria de la entrada (1) y la salida (3)
    int entradaX = 0, entradaY = rand() % n;
    int salidaX = n - 1, salidaY = rand() % n;

    laberinto[entradaX][entradaY] = 1;  // Entrada
    laberinto[salidaX][salidaY] = 3;    // Salida

    // Generar caminos aleatorios
    for (int i = 0; i < n; i++) {
        int x = entradaX, y = entradaY;
        while (x < n - 1) {
            int move = rand() % 3;
            if (move == 0 && y > 0) y--;        // Izquierda
            else if (move == 1 && y < n - 1) y++; // Derecha
            else x++;                           // Abajo

            if (laberinto[x][y] == 0) laberinto[x][y] = 2;
        }
    }

    return laberinto;
}

// Guardar laberinto en un archivo
void guardarLaberinto(vector<vector<int>> &laberinto, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (auto &fila : laberinto) {
            for (int celda : fila) {
                archivo << celda << " ";
            }
            archivo << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Dibujar laberinto con graphics.h
void dibujarLaberinto(vector<vector<int>> &laberinto, int tamCelda) {
    int n = laberinto.size();
    int width = n * tamCelda, height = n * tamCelda;

    initwindow(width, height, "Laberinto");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x1 = j * tamCelda, y1 = i * tamCelda;
            int x2 = x1 + tamCelda, y2 = y1 + tamCelda;

            if (laberinto[i][j] == 0) { // Pared
                setfillstyle(SOLID_FILL, WHITE);
                bar(x1, y1, x2, y2);
            } else if (laberinto[i][j] == 1) { // Entrada
                setfillstyle(SOLID_FILL, GREEN);
                bar(x1, y1, x2, y2);
            } else if (laberinto[i][j] == 3) { // Salida
                setfillstyle(SOLID_FILL, RED);
                bar(x1, y1, x2, y2);
            }
        }
    }

    getch();
    closegraph();
}

int main() {
    int n;
    cout << "Ingrese el tamaño del laberinto: ";
    cin >> n;

    vector<vector<int>> laberinto = generarLaberinto(n);
    guardarLaberinto(laberinto, "laberinto.txt");

    dibujarLaberinto(laberinto, 30);

    return 0;
}
