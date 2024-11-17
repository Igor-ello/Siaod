#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

// Функция для вывода графа в виде дерева
void printGraphAsTree(const vector<vector<int>>& graph, int node, int level = 0, vector<bool> visited = {}) {
    if (visited.empty()) visited.resize(graph.size(), false);
    visited[node] = true;

    // Печатаем текущий узел с отступом
    cout << string(level * 3, ' ') << "|__" << (node + 1) << endl;  // +1 для отображения нумерации с 1

    // Рекурсивно обходим всех соседей узла, если они не были посещены
    for (int i = 0; i < graph[node].size(); ++i) {
        if (graph[node][i] != INF && !visited[i]) {
            printGraphAsTree(graph, i, level + 1, visited);
        }
    }
}

// Функция для нахождения кратчайших путей методом Флойда
void floydWarshall(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Вывод кратчайших путей
    cout << "Кратчайшие пути между всеми парами вершин:" << endl;
    for (int i = -1; i < n; i++) {
        cout << i + 1 << " |";
        for (int j = 1; j < n; j++) {
            if (i == -1)
                cout << "____" << j+1;
            else if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << endl;
    }
}

// Функция для ручного заполнения графа
void inputGraph(vector<vector<int>>& graph) {
    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    // Инициализация матрицы смежности
    graph.assign(n, vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0; // Расстояние до самого себя всегда 0
    }

    cout << "Введите рёбра в формате: начальная_вершина конечная_вершина вес" << endl;
    cout << "Для завершения ввода, введите -1 -1 -1" << endl;

    while (true) {
        int u, v, weight;
        cout << "Ребро: ";
        cin >> u >> v >> weight;

        if (u == -1 && v == -1 && weight == -1) {
            break;  // Завершаем ввод рёбер
        }

        if (u <= 0 || v <= 0 || u > n || v > n) {
            cout << "Ошибка: Вершины должны быть от 1 до " << n << endl;
            continue;
        }

        // Устанавливаем вес ребра (уменьшаем на 1 для индексации с 0)
        graph[u - 1][v - 1] = weight;
    }
}

// Функция для автоматического заполнения графа предопределенными значениями
void exampleGraph(vector<vector<int>>& graph) {
    graph = {
        // 1    2    3    4    5    6
        {  0,   2,   4,   5, INF, INF}, // 1
        {INF,   0, INF,   4,   3, INF}, // 2
        {INF, INF,   0, INF, INF,   7}, // 3
        {INF, INF, INF,   0,   6,   4}, // 4
        {INF, INF, INF, INF,   0,   2}, // 5
        {INF, INF, INF, INF, INF,   0}  // 6
    };
}

int main() {
    int type;
    vector<vector<int>> graph;

    cout << "Введите способ заполнения графа (1-пример, 2-ручной): ";
    cin >> type;
    if (type == 1) {
        // Заполнение графа предопределенными значениями
        exampleGraph(graph);
    } else if (type == 2) {
        inputGraph(graph);
    } else cout << "Нет такого способа!";

    // Вывод графа в виде дерева
    cout << "Граф в виде дерева:" << endl;
    printGraphAsTree(graph, 0);

    // Запуск алгоритма Флойда
    floydWarshall(graph);

    return 0;
}
