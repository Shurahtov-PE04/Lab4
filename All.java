import java.util.*;

public class GraphAnalyzer {
    /**
     * Класс для анализа графовых структур и решения задач на графах
     */
    
    /**
     * Задача 1: Подсчет компонент связности в неориентированном графе
     * 
     * @param n количество вершин
     * @param edges список ребер
     * @return количество компонент связности
     */
    public int countConnectedComponents(int n, int[][] edges) {
        // Создаем список смежности для представления графа
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        // Заполняем граф (неориентированный - добавляем в обе стороны)
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        boolean[] visited = new boolean[n]; // Массив посещенных вершин
        int componentsCount = 0;            // Счетчик компонент
        
        // Обходим все вершины
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                componentsCount++;
                dfs(i, graph, visited); // Запускаем DFS для каждой новой компоненты
            }
        }
        
        return componentsCount;
    }
    
    /**
     * Вспомогательный метод для обхода графа в глубину
     */
    private void dfs(int node, List<List<Integer>> graph, boolean[] visited) {
        visited[node] = true;
        for (int neighbor : graph.get(node)) {
            if (!visited[neighbor]) {
                dfs(neighbor, graph, visited);
            }
        }
    }
    
    /**
     * Задача 2: Кратчайший путь в невзвешенном ориентированном графе
     * 
     * @param n количество вершин
     * @param edges список направленных ребер
     * @param start начальная вершина
     * @param end конечная вершина
     * @return длина кратчайшего пути или -1 если путь не существует
     */
    public int shortestPathLength(int n, int[][] edges, int start, int end) {
        // Создаем список смежности для ориентированного графа
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
        }
        
        // BFS для поиска кратчайшего пути
        boolean[] visited = new boolean[n];
        int[] distance = new int[n];
        Arrays.fill(distance, -1); // Инициализируем расстояния как -1 (недостижимо)
        
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        visited[start] = true;
        distance[start] = 0;
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            
            // Если достигли конечной вершины, возвращаем расстояние
            if (current == end) {
                return distance[current];
            }
            
            // Обходим соседей текущей вершины
            for (int neighbor : graph.get(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[current] + 1;
                    queue.offer(neighbor);
                }
            }
        }
        
        return -1; // Путь не найден
    }
    
    // Демонстрация работы
    public static void main(String[] args) {
        GraphAnalyzer analyzer = new GraphAnalyzer();
        
        // Тест для задачи 1
        int n1 = 5;
        int[][] edges1 = {{0, 1}, {1, 2}, {3, 4}};
        System.out.println("Количество компонент связности: " + 
                          analyzer.countConnectedComponents(n1, edges1));
        
        // Тест для задачи 2
        int n2 = 6;
        int[][] edges2 = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {4, 5}};
        int start = 0, end = 3;
        int pathLength = analyzer.shortestPathLength(n2, edges2, start, end);
        System.out.println("Длина кратчайшего пути от " + start + " до " + end + ": " + pathLength);
    }
}
