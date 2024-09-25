#include <iostream>
#include <limits>

using namespace std;

const char vertices[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };

struct GRAPH {
    int G[9][9] = { // A B C D E F G H I
        {0, 7,10, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 9,27, 0, 0},
        {10,0, 0, 0,31, 8, 0, 0, 0},
        {0, 0, 0, 0,32, 0, 0,17, 21},
        {0, 0,31,32, 0, 0, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0,11, 0},
        {0,27, 0, 0, 0, 0, 0, 0,15},
        {0, 0, 0,17, 0,11, 0, 0,15},
        {0, 0, 0,21, 0, 0,15,15, 0},
    };

};

int minDistance(int dist[], bool mark[]) {
    int min = numeric_limits<int>::max();
    int minIndex = -1;

    for (int v = 0; v < 9; v++) {
        if (!mark[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void Dekstr(GRAPH&, int);

int main() {
    setlocale(LC_ALL, "ru");
    GRAPH g;
    char select;
    cout << "Введите вершину (A - I) | 0 - Завершить программу: ";
    cin >> select;

    while (select != '0') {
        switch (select) {
        case 'A': Dekstr(g, 0); break;
        case 'B': Dekstr(g, 1); break;
        case 'C': Dekstr(g, 2); break;
        case 'D': Dekstr(g, 3); break;
        case 'E': Dekstr(g, 4); break;
        case 'F': Dekstr(g, 5); break;
        case 'G': Dekstr(g, 6); break;
        case 'H': Dekstr(g, 7); break;
        case 'I': Dekstr(g, 8); break;
        default: cout << "Error" << endl;
        }
        cout << "\nВведите вершину (A - I): ";
        cin >> select;
    }

    return 0;
}

void Dekstr(GRAPH& g, int number) {
    const int INF = numeric_limits<int>::max();
    int dist[9];
    bool sptSet[9]; 

    for (int i = 0; i < 9; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }

    dist[number] = 0;

    for (int count = 0; count < 9 - 1; count++) {
        int u = minDistance(dist, sptSet); 
        sptSet[u] = true;  // Помечаем вершину как пройденную

        // Обновляем расстояния до соседей
        for (int v = 0; v < 9; v++) {
            if (!sptSet[v] && g.G[u][v] && dist[u] != INF && dist[u] + g.G[u][v] < dist[v]) {
                dist[v] = dist[u] + g.G[u][v];
            }
        }
    }

    cout << "Расстояния от вершины " << vertices[number] << ":" << endl;
    for (int i = 0; i < 9; i++) {
            cout << "Вершина " << vertices[i] << ": " << dist[i] << endl;
    }
}
