#include <iostream>
#include <queue>
#include <stack>

using namespace std;

//#define TEST_MATRIX
//#define TEST_VERTEX_LIST
#define TEST_EDGE_LIST

#if defined(TEST_MATRIX) + \
    defined(TEST_VERTEX_LIST) + \
    defined(TEST_EDGE_LIST) > 1
#error Ошибка: Нельзя установить более одного макроса из списка
#endif

struct GRAPH {
#ifdef TEST_MATRIX
	int G[10][10] = {
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
		{1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{0, 0, 0, 0, 0, 1, 0, 0, 1, 0 },
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		{0, 0, 0, 1, 1, 0, 0, 0, 1, 0 },
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
		{0, 1, 1, 0, 0, 0, 1, 0, 0, 0 },
		{0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
	};
#endif
	int mark[10];

	GRAPH() {
		for (int i = 0; i < 10; i++) {
			mark[i] = 0;
		}
#ifdef TEST_EDGE_LIST
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				G[i][j] = 0;
			}
		}
		listEToMatrix();
#endif
#ifdef TEST_VERTEX_LIST
		listVToMatrix();
#endif
	};
#ifdef TEST_VERTEX_LIST
	int grav[22][2] =
	{
		{1,2},{2,1},
		{1,5},{5,1},
		{2,7},{7,2},
		{2,8},{8,2},
		{5,6},{6,5},
		{6,4},{4,6},
		{4,9},{9,4},
		{6,9},{9,6},
		{3,8},{8,3},
		{7,8},{8,7},
		{9,10},{10,9}

};

	int G[10][10];
	void listVToMatrix() {
		for (int i = 0; i < 22; i++) {
			int u = grav[i][0] - 1;
			int v = grav[i][1] - 1;
			G[u][v] = 1;
		}
	}
#endif

#ifdef TEST_EDGE_LIST
	int Elist[10][3]{
		{2,5,-1},
		{1,7,8},
		{8,-1,-1},
		{6,9,-1},
		{1,6,-1},
		{4,5,9},
		{2,8,-1},
		{2,3,7},
		{4,6,10},
		{9,-1,-1}
	};

	int G[10][10];
	void listEToMatrix() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 3; j++) {
				if (Elist[i][j] != -1) {
					G[i][Elist[i][j] - 1] = 1;
				}
			}
		}
	}
#endif

};

void BFS(GRAPH);
void DFS(GRAPH);

int main() {
	setlocale(LC_ALL, "ru");
	GRAPH gr;
	int u;
	cout << "1 - BFS\n2 - DFS" << endl;
	cin >> u;
	while (u != 0) {
		switch (u)
		{
		case 1:
			BFS(gr);
			break;
		case 2:
			DFS(gr);
			break;
		default:
			break;
		}
		cin >> u;
	}
	return 0;
}

void BFS(GRAPH gr) {
	queue<int> q;
	q.push(5);
	gr.mark[5] = 1;
	int d[10];
	int j = 0;
	while (!q.empty()) {
		int c = q.front();
		q.pop();
		d[j] = c + 1;
		for (int i = 0; i < 10; i++) {
			if (gr.G[c][i] == 1 && gr.mark[i] == 0) {	
				q.push(i);
				gr.mark[i] = 1; 
			}
		}
		j++;
	}
	cout << "BFS Массив посещенных вершин: ";
	for (int i = 0; i < 10; i++) {
		if (i != 9) {
			cout << d[i] << " -> ";
		}
		else {
			cout << d[i] << endl;
		}

	}
}

void DFS(GRAPH gr) {
	stack<int> s;

	s.push(0);
	gr.mark[0] = 1;
	int d[10];
	int j = 0;
	while (!s.empty()) {
		int c = s.top();
		s.pop();
		d[j] = c + 1;
		for (int i = 9; i >= 0; i--) {
			if (gr.G[c][i] == 1 && gr.mark[i] == 0) {
				s.push(i);
				gr.mark[i] = 1;
			}
		}
		j++;
	}
	cout << "DFS Массив посещенных вершин: ";
	for (int i = 0; i < 10; i++) {
		if (i != 9) {
			cout << d[i] << " -> ";
		}
		else {
			cout << d[i] << endl;
		}

	}
}
