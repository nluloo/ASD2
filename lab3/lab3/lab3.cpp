#include <iostream>
#include <queue>

#include <chrono>

using namespace std;

const char vertices[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

struct GRAPH {
	int G[9][9] = { // A B C D E F G H I
		{0, 7,10, 0, 0, 0, 0, 0, 0},
		{7, 0, 0, 0, 0, 9,27, 0, 0},
		{10,0, 0, 0,31, 8, 0, 0, 0},
		{0, 0, 0, 0,32, 0, 0,17, 21},
		{0, 0,31,32, 0, 0, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0,11, 0},
		{0,27, 0, 0, 0, 0, 0, 0, 15},
		{0, 0, 0,17, 0,11, 0, 0, 15},
		{0, 0, 0,21, 0, 0,15,15, 0},
	};

	bool mark[10];

	GRAPH() {
		for (int i = 0; i < 10; i++) {
			mark[i] = false;
		}
	}
};

void Dekstr(GRAPH, int);

int main() {
	setlocale(LC_ALL, "ru");
	GRAPH g;
	char select;
	cout << "Введите вершину (A - I) | 0 - Завершить программу: ";
	cin >> select;
	
	do
	{
		switch (select)
		{
		case 'A':
			Dekstr(g, 0);
			break;
		case 'B':
			Dekstr(g, 1);
			break;
		case 'C':
			Dekstr(g, 2);
			break;
		case 'D':
			Dekstr(g, 3);
			break;
		case 'E':
			Dekstr(g, 4);
			break;
		case 'F':
			Dekstr(g, 5);
			break;
		case 'G':
			Dekstr(g, 6);
			break;
		case 'H':
			Dekstr(g, 7);
			break;
		case 'I':
			Dekstr(g, 8);
			break;
		default:
			cout << "Error" << endl;
		}
		cout << "\nВведите вершину (A - I): ";
		cin >> select;
	} while (select != '0');
	


	return 0;
}

void Dekstr(GRAPH g, int number = 0) { // ПЕРЕПРОВЕТИЬ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
	const int INF = numeric_limits<int>::max();
	int dist[9] = { INF,INF,INF,INF ,INF,INF ,INF,INF ,INF};

	dist[number] = 0;
	queue<int> q;
	q.push(number);
	g.mark[number] = true;  // Отмечаем вершину как посещённую

	while (!q.empty()) {
		int u = q.front();  // Берём вершину из очереди
		q.pop();

		for (int v = 0; v < 9; v++) {
			if (g.G[u][v] != 0 && !g.mark[v]) {  // Если есть связь и вершина не посещена
				int newDist = dist[u] + g.G[u][v];
				if (newDist < dist[v]) {  // Если нашли более короткий путь
					dist[v] = newDist;
					q.push(v);  // Добавляем вершину в очередь для дальнейшей обработки
					g.mark[u] = true;
				}
			}
		}
	}

	cout << "Расстояния от вершины " << vertices[number] << ":" << endl;
	for (int i = 0; i < 9; i++) {
		cout << "Вершина " << vertices[i] << ": " << dist[i] << endl;
	}
}