#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class GraphSolver {
    /**
     * Класс для решения графовых задач на C++
     */
    
public:
    /**
     * Задача 1: Подсчет компонент связности в неориентированном графе
     * 
     * @param n количество вершин
     * @param edges вектор ребер
     * @return количество компонент связности
     */
    int countConnectedComponents(int n, vector<vector<int>>& edges) {
        // Создаем список смежности
        vector<list<int>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u); // Граф неориентированный
        }
        
        vector<bool> visited(n, false); // Вектор для отслеживания посещенных вершин
        int componentsCount = 0;        // Счетчик компонент связности
        
        // Вспомогательная лямбда-функция для DFS
        auto dfs = [&](int node, auto&& dfs_ref) -> void {
            visited[node] = true;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    dfs_ref(neighbor, dfs_ref);
                }
            }
        };
        
        // Обходим все вершины
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                componentsCount++;
                dfs(i, dfs); // Запускаем DFS для каждой непосещенной вершины
            }
        }
        
        return componentsCount;
    }
    
    /**
     * Задача 2: Кратчайший путь в невзвешенном ориентированном графе
     * 
     * @param n количество вершин
     * @param edges вектор направленных ребер
     * @param start начальная вершина
     * @param end конечная вершина
     * @return длина кратчайшего пути или -1 если путь не существует
     */
    int shortestPathLength(int n, vector<vector<int>>& edges, int start, int end) {
        // Создаем список смежности для ориентированного графа
        vector<list<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        
        // BFS для поиска кратчайшего пути
        vector<bool> visited(n, false);
        vector<int> distance(n, -1); // -1 означает, что вершина недостижима
        queue<int> q;
        
        // Инициализируем начальную вершину
        q.push(start);
        visited[start] = true;
        distance[start] = 0;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            // Если достигли конечной вершины, возвращаем расстояние
            if (current == end) {
                return distance[current];
            }
            
            // Обходим всех соседей
            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[current] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        return -1; // Путь не найден
    }
};

// Демонстрация работы
int main() {
    GraphSolver solver;
    
    // Тест для задачи 1
    int n1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {3, 4}};
    cout << "Количество компонент связности: " 
         << solver.countConnectedComponents(n1, edges1) << endl;
    
    // Тест для задачи 2
    int n2 = 6;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {4, 5}};
    int start = 0, end = 3;
    int pathLength = solver.shortestPathLength(n2, edges2, start, end);
    cout << "Длина кратчайшего пути от " << start << " до " << end << ": " 
         << pathLength << endl;
    
    return 0;
}
