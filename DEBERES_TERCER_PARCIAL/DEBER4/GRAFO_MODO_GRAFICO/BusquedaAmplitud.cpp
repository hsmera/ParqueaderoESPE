#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Validaciones.h"

using namespace std;

class Graph
{
private:
    map<int, list<int>> adjacency_list;
    int num_nodes;
    bool directed;

public:
    Graph(int nodes, bool isDirected)
    {
        num_nodes = nodes;
        directed = isDirected;
        generate_random_graph();
    }

    // Generación aleatoria del grafo
    void generate_random_graph()
    {
        srand(time(0));
        int edges = num_nodes + rand() % (num_nodes * 2); // Número aleatorio de aristas

        for (int i = 0; i < edges; i++)
        {
            int u = rand() % num_nodes;
            int v = rand() % num_nodes;
            if (u != v)
            {
                add_edge(u, v);
            }
        }
    }

    void add_edge(int u, int v)
    {
        adjacency_list[u].push_back(v);
        if (!directed)
        {
            adjacency_list[v].push_back(u);
        }
    }

    // BFS: Retorna el mapa de padres y nodos visitados
    map<int, pair<int, bool>> breadth_first_search(int start)
    {
        map<int, pair<int, bool>> result;
        queue<int> q;

        for (int i = 0; i < num_nodes; i++)
        {
            result[i] = {-1, false}; // Inicializamos todos los nodos como no visitados
        }

        q.push(start);
        result[start] = {-1, true};

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adjacency_list[node])
            {
                if (!result[neighbor].second)
                {
                    q.push(neighbor);
                    result[neighbor] = {node, true}; // Guardamos el padre y marcamos como visitado
                }
            }
        }

        return result;
    }

    // Representación lógica del grafo
    void print_logical_representation()
    {
        cout << "Grafo generado con " << num_nodes << " nodos:\n";
        for (auto &node : adjacency_list)
        {
            cout << node.first << " -> ";
            for (auto &neighbor : node.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Lista de Adyacencia
    void print_adjacency_list()
    {
        cout << "Lista de Adyacencia:\n";
        for (auto &node : adjacency_list)
        {
            cout << node.first << " -> ";
            for (auto &neighbor : node.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Matriz de Adyacencia
    void print_adjacency_matrix()
    {
        vector<vector<int>> matrix(num_nodes, vector<int>(num_nodes, 0));

        for (auto &node : adjacency_list)
        {
            for (auto &neighbor : node.second)
            {
                matrix[node.first][neighbor] = 1;
            }
        }

        cout << "Matriz de Adyacencia:\n   ";
        for (int i = 0; i < num_nodes; i++)
        {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < num_nodes; i++)
        {
            cout << i << "  ";
            for (int j = 0; j < num_nodes; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Imprimir resultados de BFS
    void print_bfs_results(map<int, pair<int, bool>> bfs_result)
    {
        cout << "\n| Nodo  | Parent  | Visited |\n";
        cout << "|-------|---------|---------|\n";
        for (int i = 0; i < num_nodes; i++)
        {
            cout << "|  " << i << "    |   " << (bfs_result[i].first == -1 ? "-" : to_string(bfs_result[i].first))
                 << "     |    " << (bfs_result[i].second ? "T" : "F") << "    |\n";
        }
    }

    void draw_graph(sf::RenderWindow &window, bool is_directed)
    {
        vector<sf::CircleShape> nodes(num_nodes);
        map<int, sf::Vector2f> positions;
        float centerX = 300, centerY = 300, radius = 200;
    
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error cargando la fuente!" << std::endl;
            return;
        }
    
        // Crear los nodos y calcular posiciones en círculo
        for (int i = 0; i < num_nodes; i++)
        {
            float angle = i * (2 * M_PI / num_nodes);
            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);
            positions[i] = sf::Vector2f(x, y);
    
            nodes[i].setRadius(30);
            nodes[i].setFillColor(sf::Color::Blue);
            nodes[i].setOrigin(30, 30);
            nodes[i].setPosition(x, y);
        }
    
        window.clear(sf::Color::White);
    
        // Dibujar conexiones (curvas)
        for (const auto &pair : adjacency_list)
        {
            int u = pair.first;
            for (int v : pair.second)
            {
                sf::VertexArray curve(sf::LineStrip, 20);  // Más puntos para suavizar curva
                sf::Vector2f p0 = positions[u];
                sf::Vector2f p2 = positions[v];
                sf::Vector2f control = (p0 + p2) / 2.f + sf::Vector2f(30, -30);  // Punto de control para curvatura
    
                for (int i = 0; i < 20; i++) {
                    float t = i / 19.0f;
                    float x = (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * control.x + t * t * p2.x;
                    float y = (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * control.y + t * t * p2.y;
                    curve[i].position = sf::Vector2f(x, y);
                    curve[i].color = sf::Color::Black;
                }
                window.draw(curve);
    
                // Solo dibujar flechas si el grafo es dirigido
                if (is_directed) {
                    float dx = p2.x - p0.x;
                    float dy = p2.y - p0.y;
                    float angle = atan2(dy, dx);
                    float arrowSize = 10;
    
                    sf::Vector2f arrowEnd = p2 - sf::Vector2f(30 * cos(angle), 30 * sin(angle));  // Ajustar para no estar sobre el nodo
    
                    sf::Vertex arrow[] = {
                        sf::Vertex(arrowEnd, sf::Color::Black),
                        sf::Vertex(arrowEnd - sf::Vector2f(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6)), sf::Color::Black),
                        sf::Vertex(arrowEnd - sf::Vector2f(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6)), sf::Color::Black)
                    };
                    window.draw(arrow, 3, sf::Triangles);
                }
            }
        }
    
        // Dibujar nodos
        for (int i = 0; i < num_nodes; i++)
        {
            window.draw(nodes[i]);
    
            // Dibujar el número dentro del nodo
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            text.setPosition(positions[i].x - 10, positions[i].y - 10);
            window.draw(text);
        }
    
        window.display();
    }          

    void draw_adjacency_list(sf::RenderWindow &window, const map<int, list<int>> &adjacency_list)
    {
        const int cell_size = 40; 
        const int padding = 10;   
        int x_offset = 50;
        int y_offset = 50;
        sf::Font font;
        
        if (!font.loadFromFile("arial.ttf")) { 
            std::cerr << "Error cargando la fuente!" << std::endl;
            return;
        }

        for (auto &node : adjacency_list)
        {
            int y = y_offset + node.first * (cell_size + padding);

            sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
            cell.setPosition(x_offset, y);
            cell.setFillColor(sf::Color::White);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(node.first));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            text.setPosition(x_offset + (cell_size / 2) - 10, y + (cell_size / 2) - 10);
            window.draw(text);

            int x_pos = x_offset + cell_size + padding;
            for (int neighbor : node.second)
            {
                sf::RectangleShape neighbor_cell(sf::Vector2f(cell_size, cell_size));
                neighbor_cell.setPosition(x_pos, y);
                neighbor_cell.setFillColor(sf::Color::White);
                neighbor_cell.setOutlineThickness(1);
                neighbor_cell.setOutlineColor(sf::Color::Black);
                window.draw(neighbor_cell);

                sf::Text neighbor_text;
                neighbor_text.setFont(font);
                neighbor_text.setString(std::to_string(neighbor));
                neighbor_text.setCharacterSize(20);
                neighbor_text.setFillColor(sf::Color::Black);
                neighbor_text.setPosition(x_pos + (cell_size / 2) - 10, y + (cell_size / 2) - 10);
                window.draw(neighbor_text);
    
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x_offset + cell_size, y + cell_size / 2), sf::Color::Black), 
                    sf::Vertex(sf::Vector2f(x_pos, y + cell_size / 2), sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);

                sf::Vertex arrow[] = {
                    sf::Vertex(sf::Vector2f(x_pos, y + cell_size / 2), sf::Color::Black), 
                    sf::Vertex(sf::Vector2f(x_pos - 10, y + cell_size / 2 - 5), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x_pos - 10, y + cell_size / 2 + 5), sf::Color::Black)
                };
                window.draw(arrow, 3, sf::Triangles);
    
                x_pos += cell_size + padding; 
            }
        }
    }      

    void draw_adjacency_matrix(sf::RenderWindow &window, const vector<vector<int>> &matrix)
    {
        const int cell_size = 40;
        const int padding = 10;
        int x_offset = 50;
        int y_offset = 50;
        sf::Font font;
        
        if (!font.loadFromFile("arial.ttf")) { 
            std::cerr << "Error cargando la fuente!" << std::endl;
            return;
        }

        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            sf::Text column_index;
            column_index.setFont(font);
            column_index.setString(std::to_string(j));
            column_index.setCharacterSize(20);
            column_index.setFillColor(sf::Color::Black);
            column_index.setPosition(x_offset + j * (cell_size + padding) + 12, y_offset - 30); 
            window.draw(column_index);
        }
 
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            sf::Text row_index;
            row_index.setFont(font);
            row_index.setString(std::to_string(i));
            row_index.setCharacterSize(20);
            row_index.setFillColor(sf::Color::Black);
            row_index.setPosition(x_offset - 30, y_offset + i * (cell_size + padding) + 10);
            window.draw(row_index);
    
            for (size_t j = 0; j < matrix[i].size(); ++j)
            {
                sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
                cell.setPosition(x_offset + j * (cell_size + padding), y_offset + i * (cell_size + padding));
                cell.setFillColor(sf::Color::White);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);
    
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(matrix[i][j]));
                text.setCharacterSize(20);
                text.setFillColor(sf::Color::Black);
                text.setPosition(x_offset + j * (cell_size + padding) + 12, y_offset + i * (cell_size + padding) + 10);
                window.draw(text);
            }
        }
    }

    map<int, list<int>> get_adjacency_list() const
    {
        return adjacency_list;
    }

    vector<vector<int>> get_adjacency_matrix() const
    {
        vector<vector<int>> matrix(num_nodes, vector<int>(num_nodes, 0));
        for (auto &node : adjacency_list)
        {
            for (auto &neighbor : node.second)
            {
                matrix[node.first][neighbor] = 1;
            }
        }
        return matrix;
    }
};

// Función para manejar el menú con flechas
int menu(vector<string> options)
{
    int choice = 0;
    while (true)
    {
        system("cls");

        for (size_t i = 0; i < options.size(); i++)
        {
            if (i == choice)
            {
                cout << " > " << options[i] << " <\n";
            }
            else
            {
                cout << "   " << options[i] << "\n";
            }
        }

        char key = _getch();
        if (key == 72 && choice > 0)
        {
            choice--;
        }
        else if (key == 80 && choice < options.size() - 1)
        { 
            choice++;
        }
        else if (key == 13)
        { 
            return choice;
        }
    }
}

int main()
{
    while (true)
    {
        int graph_size_choice = menu({"Grafico Pequenio (7 nodos)", "Grafico Grande (17 nodos)", "Salir"});
        if (graph_size_choice == 2)
            break;

        int num_nodes = (graph_size_choice == 0) ? 7 : 17;
        int graph_type_choice = menu({"Grafico Dirigido", "Grafico No Dirigido"});
        bool isDirected = (graph_type_choice == 0);
        
        Graph graph(num_nodes, isDirected);  // Pasar isDirected correctamente
        
        system("cls");
        int start_vertex;
        Validaciones<int> validador;
        start_vertex = validador.ingresar("Ingrese el vertice inicial para BFS: ", "entero");
        auto bfs_result = graph.breadth_first_search(start_vertex);

        int representation_choice = menu({"Representacion Logica", "Lista de Adyacencia", "Matriz de Adyacencia"});

        system("cls");
        if (representation_choice == 0)
        {
            graph.print_logical_representation();
        }
        else if (representation_choice == 1)
        {
            graph.print_adjacency_list();
        }
        else if (representation_choice == 2)
        {
            graph.print_adjacency_matrix();
        }

        graph.print_bfs_results(bfs_result);

        if (representation_choice == 0)
        {
            sf::RenderWindow window(sf::VideoMode(600, 600), "Grafo generado");
            graph.draw_graph(window,isDirected);

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
            }
        }
        else
            if (representation_choice == 1)
            {
                sf::RenderWindow window(sf::VideoMode(600, 600), "Lista de Adyacencia");

                window.clear(sf::Color::White);
                graph.draw_adjacency_list(window, graph.get_adjacency_list());
                window.display();

                while (window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }
                }
            }
            else if (representation_choice == 2)
            {
                sf::RenderWindow window(sf::VideoMode(600, 600), "Matriz de Adyacencia");

                window.clear(sf::Color::White);
                graph.draw_adjacency_matrix(window, graph.get_adjacency_matrix());
                window.display();

                while (window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }
                }
            }

        cout << "\nPresiona cualquier tecla para volver al menu...";
        _getch();
    }

    return 0;
}
