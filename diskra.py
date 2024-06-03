import tkinter as tk
from tkinter import messagebox
import itertools
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np


def latin_composition(graph):
    n = len(graph)
    max_length = n

    # Создаем граф с использованием NetworkX
    G = nx.DiGraph()
    for i in range(n):
        for j in range(n):
            if graph[i][j] == 1:
                G.add_edge(i, j)

    print("Graph created with nodes and edges:")
    print(G.nodes)
    print(G.edges)

    # Инициализация начальной матрицы для путей длины 1
    L = np.empty((max_length + 1, n, n), dtype=object)
    for i in range(n):
        for j in range(n):
            if graph[i][j] == 1:
                L[1, i, j] = [[i, j]]
            else:
                L[1, i, j] = []

    # Вывод начальной матрицы L
    print("Initial matrix L[1]:")
    for i in range(n):
        for j in range(n):
            print(f"L[1][{i}][{j}]: {L[1, i, j]}")

    # Построение матриц L^(k) для k = 2, ..., max_length
    for k in range(2, max_length + 1):
        for i in range(n):
            for j in range(n):
                L[k, i, j] = []
                for r in range(n):
                    if L[k - 1, i, r] and L[1, r, j]:
                        for path1 in L[k - 1, i, r]:
                            for path2 in L[1, r, j]:
                                new_path = path1 + path2[1:]
                                if len(set(new_path[:-1])) == len(new_path[:-1]):  # Проверка простоты пути
                                    L[k, i, j].append(new_path)

    # Вывод матриц L
    for k in range(2, max_length + 1):
        print(f"Matrix L[{k}]:")
        for i in range(n):
            for j in range(n):
                print(f"L[{k}][{i}][{j}]: {L[k, i, j]}")

    # Нахождение всех контуров
    contours = []
    for k in range(2, max_length + 1):
        for i in range(n):
            for path in L[k, i, i]:
                if path not in contours:  # Избегаем дублирования
                    contours.append(path)


    for contour in contours:
        for i in range(len(contour)):
            contour[i] = str(int(contour[i]) + 1)


    print("Contours found:")
    for contour in contours:
        print(contour)

    return contours

class GraphApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Graph Contour Finder")
        self.root.geometry("1280x1024")

        self.matrix_size = 3
        self.max_size = 9

        # Матрица смежности
        self.adj_matrix = [[0] * self.matrix_size for _ in range(self.matrix_size)]

        # UI элементы
        self.create_widgets()

    def create_widgets(self):
        # Область для отображения графа
        self.graph_frame = tk.Frame(self.root, width=800, height=800, bg='white')
        self.graph_frame.grid(row=0, column=0, rowspan=4, padx=10, pady=10, sticky="nsew")

        # Матрица ввода
        self.matrix_frame = tk.Frame(self.root)
        self.matrix_frame.grid(row=0, column=1, padx=10, pady=10, sticky="n")

        self.matrix_entries = [[None] * self.max_size for _ in range(self.max_size)]
        for i in range(self.max_size):
            for j in range(self.max_size):
                entry = tk.Entry(self.matrix_frame, width=3, justify='center')
                entry.grid(row=i, column=j)
                entry.insert(0, '0')
                if i >= self.matrix_size or j >= self.matrix_size:
                    entry.grid_remove()
                self.matrix_entries[i][j] = entry

        # Размерность
        self.size_frame = tk.Frame(self.root)
        self.size_frame.grid(row=1, column=1, padx=10, pady=10, sticky="n")

        tk.Label(self.size_frame, text="Размерность:").pack(side=tk.LEFT)
        self.size_var = tk.IntVar(value=self.matrix_size)
        self.size_entry = tk.Entry(self.size_frame, textvariable=self.size_var, width=3)
        self.size_entry.pack(side=tk.LEFT)
        tk.Button(self.size_frame, text="Изменить", command=self.change_size).pack(side=tk.LEFT)

        # Кнопки
        self.buttons_frame = tk.Frame(self.root)
        self.buttons_frame.grid(row=2, column=1, padx=10, pady=10, sticky="n")

        tk.Button(self.buttons_frame, text="Очистить", command=self.clear_matrix).pack(side=tk.LEFT, padx=5)
        tk.Button(self.buttons_frame, text="Найти контуры", command=self.find_contours).pack(side=tk.LEFT, padx=5)

        # Вывод контуров
        self.contours_text = tk.Text(self.root, height=10, width=30)
        self.contours_text.grid(row=3, column=1, padx=10, pady=10, sticky="n")

    def change_size(self):
        try:
            size = int(self.size_entry.get())
            if 1 <= size <= self.max_size:
                self.matrix_size = size
                for i in range(self.max_size):
                    for j in range(self.max_size):
                        if i < size and j < size:
                            self.matrix_entries[i][j].grid()
                        else:
                            self.matrix_entries[i][j].grid_remove()
            else:
                messagebox.showerror("Ошибка", f"Размерность должна быть от 1 до {self.max_size}")
        except ValueError:
            messagebox.showerror("Ошибка", "Некорректное значение размерности")

    def clear_matrix(self):
        self.matrix_size = 3
        self.size_var.set(3)
        for i in range(self.max_size):
            for j in range(self.max_size):
                self.matrix_entries[i][j].grid_remove()
                self.matrix_entries[i][j].delete(0, tk.END)
                self.matrix_entries[i][j].insert(0, '0')
                if i < self.matrix_size and j < self.matrix_size:
                    self.matrix_entries[i][j].grid()
        self.contours_text.delete(1.0, tk.END)
        self.clear_graph()

    def get_adj_matrix(self):
        return [[int(self.matrix_entries[i][j].get()) for j in range(self.matrix_size)] for i in range(self.matrix_size)]

    def clear_graph(self):
        for widget in self.graph_frame.winfo_children():
            widget.destroy()

    def find_contours(self):
        self.clear_graph()
        self.adj_matrix = self.get_adj_matrix()

        contours = latin_composition(self.adj_matrix)
        self.contours_text.delete(1.0, tk.END)
        for contour in contours:
            self.contours_text.insert(tk.END, " -> ".join(map(str, contour)) + "\n")

        self.draw_graph()

    def draw_graph(self):
        G = nx.DiGraph()
        for i in range(self.matrix_size):
            for j in range(self.matrix_size):
                if self.adj_matrix[i][j] != 0:
                    G.add_edge(i + 1, j + 1)

        fig, ax = plt.subplots(figsize=(8, 8))
        pos = nx.spring_layout(G)
        nx.draw(G, pos, ax=ax, with_labels=True, node_size=700, node_color="lightblue", arrowsize=20)
        canvas = FigureCanvasTkAgg(fig, master=self.graph_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

if __name__ == "__main__":
    root = tk.Tk()
    app = GraphApp(root)
    root.mainloop()
