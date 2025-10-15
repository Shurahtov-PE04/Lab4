#include <iostream>
#include <vector>

using namespace std;

// Функция обхода в глубину (DFS - Depth First Search)
void dfs(int v, vector<bool>& visited, vector<vector<int>>& graph) {
    // Помечаем текущую вершину как посещенную
    visited[v] = true;

    // Проходим по всем соседям текущей вершины
    for (int u : graph[v]) {
        // Если соседняя вершина еще не посещена
        if (!visited[u]) {
            // Рекурсивно запускаем DFS из этой вершины
            dfs(u, visited, graph);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    int n = 5;
    vector<vector<int>> graph(n);

    /*
    Строим граф:
    0 -- 1 -- 2    3 -- 4
    */

    // Добавляем рёбра (каждое ребро добавляем в обе стороны, т.к. граф неориентированный)
    graph[0].push_back(1); // ребро 0-1
    graph[1].push_back(0); // ребро 1-0

    graph[1].push_back(2); // ребро 1-2
    graph[2].push_back(1); // ребро 2-1

    graph[3].push_back(4); // ребро 3-4
    graph[4].push_back(3); // ребро 4-3

    // Массив для отслеживания посещенных вершин (изначально все false)
    vector<bool> visited(n, false);
    int components = 0; 

    // Проходим по всем вершинам
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, visited, graph);
            components++;
        }
    }

    cout << "Количество компонент связности: " << components << endl;
    return 0;
}
