#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();

struct StructMatrix
{
	int D[6][6] = {
		{0, 28, 21, 59, 12, 27},
		{7,  0, 24, INF, 21, 9},
		{9, 32, 0, 13, 11, INF},
		{8, INF, 5, 0, 16, INF},
		{14, 13, 15, 10, 0, 22},
		{15, 18, INF, INF, 6, 0}
	};
	int S[6][6] = {
		{0, 2, 3, 4, 5, 6},
		{1, 0, 3, 4, 5, 6},
		{1, 2, 0, 4, 5, 6},
		{1, 2, 3, 0, 5, 6},
		{1, 2, 3, 4, 0, 6},
		{1, 2, 5, 5, 5, 0}
	};

	void ReturnMatrix() {
		printf("Матрица расстояний:\n");
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
				cout << setw(5) << D[i][j];
			printf("\n");
		}
	}
	void ReturnEdge() {
		printf("Матрица путей:\n");
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
				cout << setw(5) << S[i][j];
			printf("\n");
		}
	}

	void WayTo(int start, int finish) {
		cout << "\nПуть из точки " << start << " в точку " << finish << ": ";
		finish--;
		cout << start-- << " -> ";

		for (int i = start; S[i][finish] - 1 != finish; i = S[i][finish] - 1) {
			cout << S[i][finish] << " -> ";
		}
		cout << ++finish << endl;
	}

	void printDistanceTo(int start, int finish) {
		cout << "\nРасстояние из точки " << start << " в точку " << finish << ": ";
		cout << D[--start][--finish] << endl;
	}

};

void floyd(StructMatrix& dist) {
	for (int v = 0; v < 6; v++) {
		for (int i = 0; i < 6; i++) {
			if (dist.D[i][v] != INF) {
				for (int j = 0; j < 6; j++) {
					if (dist.D[v][j] != INF && dist.D[i][j] > dist.D[i][v] + dist.D[v][j]) {
						dist.D[i][j] = dist.D[i][v] + dist.D[v][j];
						dist.S[i][j] = v + 1;
					}
				}
			}
		}
	}
}



int main() {
	setlocale(LC_ALL, "ru");
	StructMatrix a;
	int value;
	int start = 0, finish = 0;

	cout << "1. Применить алгоритм Флойда-Уоршелла" << endl;
	cout << "2. Вывести матрицу кратчайших расстояний" << endl;
	cout << "3. Вывести матрицу путей" << endl;
	cout << "4. Вывести путь из одной вершины в другую" << endl;
	cout << "5. Вывести расстояние пути из одной вершины в другую" << endl;
	cout << "0. Завершение программы" << endl;

	cin >> value;
	while (value != 0)
	{
		switch (value)
		{
		case 1:
			floyd(a);
			cout << "Алгоритм успешно применен!" << endl;
			break;
		case 2:
			a.ReturnMatrix();
			break;
		case 3:
			a.ReturnEdge();
			break;
		case 4:
			cout << "Введите начальную вершину: ";
			cin >> start;
			cout << "Введите конучную вершину: ";
			cin >> finish;
			a.WayTo(start, finish);
			break;
		case 5:
			cout << "Введите начальную вершину: ";
			cin >> start;
			cout << "Введите конучную вершину: ";
			cin >> finish;
			a.printDistanceTo(start, finish);
			break;
		default:
			cout << "error" << endl;
			break;
		}
		cin >> value;
	}

	return 0;
}