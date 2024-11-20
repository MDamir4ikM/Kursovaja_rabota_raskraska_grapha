import matplotlib.pyplot as plt
import networkx as nx

# Функция для чтения данных из файла
def read_graph_data(filename):
    with open(filename, 'r') as f:
        num_vertices = int(f.readline().strip())
        adjacency_matrix = [list(map(int, f.readline().strip().split())) for _ in range(num_vertices)]
        colors = list(map(int, f.readline().strip().split()))
    return num_vertices, adjacency_matrix, colors

# Функция для создания графа из матрицы смежности
def create_graph_from_adjacency_matrix(adjacency_matrix):
    G = nx.Graph()
    num_vertices = len(adjacency_matrix)
    G.add_nodes_from(range(num_vertices))
    for i in range(num_vertices):
        for j in range(num_vertices):
            if adjacency_matrix[i][j] == 1:
                G.add_edge(i, j)
    return G

# Функция для визуализации графа
def draw_graph(G, colors):
    color_map = [colors[node] for node in G.nodes()]
    pos = nx.spring_layout(G)  # Определение расположения вершин
    nx.draw(G, pos, with_labels=True, node_color=color_map, cmap=plt.cm.Set1)
    plt.show()

if __name__ == "__main__":
    num_vertices, adjacency_matrix, colors = read_graph_data("graph_data.txt")
    G = create_graph_from_adjacency_matrix(adjacency_matrix)
    draw_graph(G, colors)
