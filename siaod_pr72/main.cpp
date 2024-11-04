#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Определяем количество вершин в графе
const int num_vertices = 6;

// Определяем большое значение, чтобы представлять бесконечность (нет прямого пути)
const int inf = numeric_limits<int>::max();

// Реализация алгоритма Флойда-Уоршалла
void floyd_warshall(vector<vector<int>>& graph) {
    // Копируем граф в матрицу расстояний
    vector<vector<int>> distance = graph;

    // Обновляем расстояния на основе промежуточных вершин
    for (int k = 0; k < num_vertices; k++) {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                // Обновляем distance[i][j] на минимальное значение между текущим
                // и путем через вершину k
                if (distance[i][k] != inf && distance[k][j] != inf) {
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
                }
            }
        }
    }

    // Выводим матрицу кратчайших путей
    cout << "Матрица кратчайших путей:" << endl;
    for (const auto& row : distance) {
        for (const auto& dist : row) {
            if (dist == inf) {
                cout << "inf ";
            } else {
                cout << dist << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    // Инициализация матрицы смежности графа
    vector<vector<int>> graph = {
        {0, 2, 4, inf, inf, inf},
        {inf, 0, 3, 4, inf, inf},
        {inf, inf, 0, 7, inf, inf},
        {inf, inf, inf, 0, 6, 4},
        {inf, inf, inf, inf, 0, 2},
        {inf, inf, inf, inf, inf, 0}
    };

    // Запуск алгоритма
    floyd_warshall(graph);

    return 0;
}
