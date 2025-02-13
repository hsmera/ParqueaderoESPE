#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <conio.h> 

using namespace std;

class Graph {
private:
    map<int, list<int>> adjacency_list;
    int num_nodes;
    bool directed;

public:
    Graph(int nodes, bool isDirected) {
        num_nodes = nodes;
        directed = isDirected;
        generate_random_graph();
    }

    // Generación aleatoria del grafo
    void generate_random_graph() {
        srand(time(0));
        int edges = num_nodes + rand() % (num_nodes * 2); // Número aleatorio de aristas

        for (int i = 0; i < edges; i++) {
            int u = rand() % num_nodes;
            int v = rand() % num_nodes;
            if (u != v) {
                add_edge(u, v);
            }
        }
    }

    void add_edge(int u, int v) {
        adjacency_list[u].push_back(v);
        if (!directed) {
            adjacency_list[v].push_back(u);
        }
    }

    // BFS: Retorna el mapa de padres y nodos visitados
    map<int, pair<int, bool>> breadth_first_search(int start) {
        map<int, pair<int, bool>> result;
        queue<int> q;
        
        for (int i = 0; i < num_nodes; i++) {
            result[i] = {-1, false}; // Inicializamos todos los nodos como no visitados
        }

        q.push(start);
        result[start] = {-1, true};

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adjacency_list[node]) {
                if (!result[neighbor].second) {
                    q.push(neighbor);
                    result[neighbor] = {node, true}; // Guardamos el padre y marcamos como visitado
                }
            }
        }

        return result;
    }

    // Representación lógica del grafo
    void print_logical_representation() {
        cout << "Grafo generado con " << num_nodes << " nodos:\n";
        for (auto &node : adjacency_list) {
            cout << node.first << " -> ";
            for (auto &neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Lista de Adyacencia
    void print_adjacency_list() {
        cout << "Lista de Adyacencia:\n";
        for (auto &node : adjacency_list) {
            cout << node.first << " -> ";
            for (auto &neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Matriz de Adyacencia
    void print_adjacency_matrix() {
        vector<vector<int>> matrix(num_nodes, vector<int>(num_nodes, 0));

        for (auto &node : adjacency_list) {
            for (auto &neighbor : node.second) {
                matrix[node.first][neighbor] = 1;
            }
        }

        cout << "Matriz de Adyacencia:\n   ";
        for (int i = 0; i < num_nodes; i++) {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < num_nodes; i++) {
            cout << i << "  ";
            for (int j = 0; j < num_nodes; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Imprimir resultados de BFS
    void print_bfs_results(map<int, pair<int, bool>> bfs_result) {
        cout << "\n| Nodo | Parent | Visited |\n";
        cout << "|------|--------|---------|\n";
        for (int i = 0; i < num_nodes; i++) {
            cout << "|  " << i << "   |   " << (bfs_result[i].first == -1 ? "-" : to_string(bfs_result[i].first)) 
                 << "    |    " << (bfs_result[i].second ? "T" : "F") << "    |\n";
        }
    }
};

// Función para manejar el menú con flechas
int menu(vector<string> options) {
    int choice = 0;
    while (true) {
        system("cls"); // Limpiar pantalla en Windows

        for (size_t i = 0; i < options.size(); i++) {
            if (i == choice) {
                cout << " > " << options[i] << " <\n";
            } else {
                cout << "   " << options[i] << "\n";
            }
        }

        char key = _getch(); // Captura la tecla presionada
        if (key == 72 && choice > 0) { // Flecha arriba
            choice--;
        } else if (key == 80 && choice < options.size() - 1) { // Flecha abajo
            choice++;
        } else if (key == 13) { // Enter
            return choice;
        }
    }
}

int main() {
    while (true) {
        int graph_size_choice = menu({"Grafico Pequeno (7 nodos)", "Grafico Grande (17 nodos)", "Salir"});
        if (graph_size_choice == 2) break;

        int num_nodes = (graph_size_choice == 0) ? 7 : 17;
        int graph_type_choice = menu({"Grafico Dirigido", "Grafico No Dirigido"});
        bool isDirected = (graph_type_choice == 0);

        Graph graph(num_nodes, isDirected);

        system("cls");
        cout << "Ingrese el vertice inicial para BFS: ";
        int start_vertex;
        cin >> start_vertex;

        auto bfs_result = graph.breadth_first_search(start_vertex);

        int representation_choice = menu({"Representacion Logica", "Lista de Adyacencia", "Matriz de Adyacencia"});
        
        system("cls");
        if (representation_choice == 0) {
            graph.print_logical_representation();
        } else if (representation_choice == 1) {
            graph.print_adjacency_list();
        } else if (representation_choice == 2) {
            graph.print_adjacency_matrix();
        }

        graph.print_bfs_results(bfs_result);
        
        cout << "\nPresiona cualquier tecla para volver al menu...";
        _getch();
    }

    return 0;
}
