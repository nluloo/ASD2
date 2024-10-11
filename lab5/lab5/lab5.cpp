#include <iostream>
#include <vector>
#include <iomanip>

#define INF 1000000
#define V 8


// теперь правильно
using namespace std;


struct matrix {
	int matr[8][8] =
	{
		{0, 2, INF, 8, 2, INF, INF, INF},
		{2, 0, 3, 10, 5, INF, INF, INF},
		{INF, 3, 0, INF, 12, INF, INF, 7},
		{8, 10, INF, 0, 14, 3, 1, INF},
		{2, 5, 12, 14, 0, 11, 4, 8},
		{INF, INF, INF, 3, 11, 0, 6, INF},
		{INF, INF, INF, 1, 4, 6, 0, 9},
		{INF, INF, 7, INF, 8, INF, 9, 0}
	};
	
	int way[8][8] =
	{
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1},
	};

	void init_way() {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				way[i][j] = -1;
			}
		}
	}

	int count_edge() { // Для неориентированного графа
		int count = 0;
		for (int i = 0; i < 7; i++) {
			for (int j = i + 1; j < 8; j++) {
				if (matr[i][j] != INF && matr[i][j] != 0) {
					count++;
				}
			}
		}
		return count;
	}
	int edge = count_edge();
	int y = edge - V + 1;
	int curr_edges = edge - y;
};

bool isValidEdge(int u, int v, vector<bool> visited) {
	if (u == v) {
		return false;
	}
	if (visited[u] == false && visited[v] == false) {
		return false;
	}
	else if (visited[u] == true && visited[v] == true) {
		return false;
	}
	return true;
}

void prim(matrix& m, int edge) {
	vector<bool> visited(8, false);

	visited[--edge] = true;

	int sum = 0;
	for (int count = 0; count < m.curr_edges; count++) {
		int min = INF, a = -1, b = -1;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (m.matr[i][j] < min && isValidEdge(i, j, visited)) {
						min = m.matr[i][j];
						a = i;
						b = j;
				}
			}
		}
		if (a != -1 && b != -1) {
			printf("Ребро %d: %d - %d вес: %d \n",count + 1, a + 1, b + 1, min);
			sum += min;
			m.way[a][b] = m.matr[a][b];
			m.way[b][a] = m.matr[b][a];
			visited[b] = visited[a] = true;
		}
	}
	cout << "Минимальное расстояние: " << sum << endl;
}

int parent[8];
int find(int i) {
	while (parent[i] != i) {
		i = parent[i];
	}
	return i;
}

void add_parent(int i, int j) {
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}

void kruskala(matrix& m) {
	int sum = 0;

	for (int i = 0; i < 8; i++) {
		parent[i] = i;
	}

	for (int count = 0; count < m.curr_edges; count++) {
		int min = INF, a = -1, b = -1;
		for(int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {
				if (find(i) != find(j) && m.matr[i][j] < min) {
					min = m.matr[i][j];
					a = i;
					b = j;
				}
			}
		}
		if (a != -1 && b != -1) {
			add_parent(a, b);
			printf("Ребро %d: %d - %d вес: %d \n", count + 1, a + 1, b + 1, min);
			sum += min;
			m.way[a][b] = m.matr[a][b];
			m.way[b][a] = m.matr[b][a];
		}
	}
	cout << "Минимальное расстояние: " << sum << endl;
}

void print_MST_matrix(matrix m) {
	cout << "Матрица минимального остовного дерева (MST):\n";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m.way[i][j] == -1) {
				cout << setw(5) << "INF";
			}
			else {
				cout << setw(5) << m.way[i][j];
			}
		}
		cout << endl;
	}
}

int main() {
	setlocale(LC_ALL, "ru");

	matrix m;
	int choise, edge;
	cout << "1. Алгоритм Прима" << endl << "2. Алгоритм Краскала" << endl << "3. Вывод матрицы остовного дерева" << endl <<  "4. Обнуление матрицы остовного дерева" << endl <<  "5. Цикломатическое число" << endl;
	cin >> choise;
	while (choise != 0)
	{
		switch (choise)
		{
		case 1:
			cout << "Введите начальную вершину: ";
			cin >> edge;
			prim(m, edge);
			break;
		case 2:
			kruskala(m);
			break;
		case 3:
			print_MST_matrix(m);
			break;
		case 4:
			m.init_way();
			print_MST_matrix(m);
			break;
		case 5:
			cout << "Цикломатическое число: " << m.y << endl;
			break;
			case 6:
				system("cls");
				break;
		default:
			break;
		}
		cout << "\n1. Алгоритм Прима" << endl << "2. Алгоритм Краскала" << endl << "3. Вывод матрицы остовного дерева" << endl << "4. Обнуление матрицы остовного дерева" << endl << "5. Цикломатическое число" << endl;

		cin >> choise;
	}
	
	return 0;
}
