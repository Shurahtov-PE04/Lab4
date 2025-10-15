from collections import deque, defaultdict

class GraphProcessor:
    """
    Класс для обработки графовых структур и решения задач связности и поиска путей
    """
    
    def count_connected_components(self, n, edges):
        """
        Задача 1: Подсчет компонент связности в неориентированном графе
        
        Args:
            n: количество вершин
            edges: список ребер в формате [(u, v), ...]
            
        Returns:
            Количество компонент связности
        """
        # Создаем список смежности для представления графа
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)  # Граф неориентированный
        
        visited = [False] * n  # Массив для отслеживания посещенных вершин
        components_count = 0    # Счетчик компонент связности
        
        def dfs(node):
            """Вспомогательная функция для обхода в глубину"""
            visited[node] = True
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    dfs(neighbor)
        
        # Обходим все вершины
        for node in range(n):
            if not visited[node]:
                components_count += 1
                dfs(node)  # Запускаем DFS для каждой непосещенной вершины
                
        return components_count
    
    def shortest_path_length(self, n, edges, start, end):
        """
        Задача 2: Кратчайший путь в невзвешенном ориентированном графе
        
        Args:
            n: количество вершин
            edges: список направленных ребер
            start: начальная вершина
            end: конечная вершина
            
        Returns:
            Длина кратчайшего пути или -1 если путь не существует
        """
        # Создаем список смежности для ориентированного графа
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
        
        # BFS для поиска кратчайшего пути в невзвешенном графе
        visited = [False] * n
        distance = [-1] * n  # -1 означает, что вершина недостижима
        queue = deque()
        
        # Инициализируем начальную вершину
        queue.append(start)
        visited[start] = True
        distance[start] = 0
        
        while queue:
            current = queue.popleft()
            
            # Если достигли конечной вершины, возвращаем расстояние
            if current == end:
                return distance[current]
            
            # Обходим всех соседей
            for neighbor in graph[current]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    distance[neighbor] = distance[current] + 1
                    queue.append(neighbor)
        
        return -1  # Путь не найден

# Демонстрация работы
if __name__ == "__main__":
    processor = GraphProcessor()
    
    # Тест для задачи 1 (неориентированный граф)
    n1 = 5
    edges1 = [(0, 1), (1, 2), (3, 4)]  # Две компоненты: [0,1,2] и [3,4]
    print(f"Количество компонент связности: {processor.count_connected_components(n1, edges1)}")
    
    # Тест для задачи 2 (ориентированный граф)
    n2 = 6
    edges2 = [(0, 1), (1, 2), (2, 3), (0, 4), (4, 5)]
    start, end = 0, 3
    path_length = processor.shortest_path_length(n2, edges2, start, end)
    print(f"Длина кратчайшего пути от {start} до {end}: {path_length}")
