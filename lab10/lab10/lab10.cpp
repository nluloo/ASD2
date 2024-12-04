#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int N; // Количество муравьев = количество городов

vector<vector<int>> matrix;

vector<vector<float>> pheromons; 

struct Ant {
    vector<int> road;
    int distance = 0;
    vector<bool> visited = vector<bool>(N, false);
};

vector<int> bestRoad;
int bestDistance = INT_MAX;

int calculDist(vector<int> path) {
    int dist = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        dist += matrix[path[i]][path[i + 1]];
    }
    return dist;
}

Ant BestAnt(vector<Ant> ants) {
    int min = INT_MAX;
    int j = -1;
    for (int i = 0; i < ants.size(); i++) {
        if (min > ants[i].distance) {
            min = ants[i].distance;
            j = i;
        }
    }

    return ants[j];
}

void updPhero(float evapor, vector<Ant>& ants) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pheromons[i][j] *= (1.0f - evapor); // (1-p)
        }
    }

    for (int i = 0; i < ants.size(); i++) {
        for (int j = 0; j < ants[i].road.size() - 1; j++) {
            int from = ants[i].road[j];
            int to = ants[i].road[j + 1];
            pheromons[from][to] += 10.0f / ants[i].distance; // Q/L
            pheromons[to][from] += 10.0f / ants[i].distance;
        }
    }
}

vector<vector<int>> RandDist(int N) {
    vector<vector<int>> matrix(N, vector<int>(N, 0));  

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) { 
            int distance = rand() % 100 + 1; 
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }
    }

    return matrix;
}


void algoAnt( int N, int iter, float evapor, float alpha, float beta, float startPhero) {

    matrix = RandDist(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(8) << matrix[i][j];
        }
        cout << endl;
    }


    pheromons = vector<vector<float>>(N, vector<float>(N, startPhero));

    for (int i = 0; i < N; i++) {
        pheromons[i][i] = 0;
    }

    vector<vector<float>> visibility(N, vector<float>(N, 0.0f));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] != 0) {
                visibility[i][j] = 10.0f / matrix[i][j]; // Деления для представления более маленьких чисел
            }
        }
    }

    for (int t = 1; t <= iter; t++) {
        cout << t << "-я итерация" << endl;

        vector<Ant> ants(N);

        for (int k = 0; k < N; k++) {
            Ant& ant = ants[k];
            ant.road.push_back(k);
            ant.visited[ant.road.back()] = true;

            while (ant.road.size() < N) {
                int current = ant.road.back();

                vector<float> prob(N, 0.0f);
                float sumProb = 0.0f;

                for (int j = 0; j < N; j++) {
                    if (!ant.visited[j]) {
                        prob[j] = pow(pheromons[current][j], alpha) * pow(visibility[current][j], beta); // степень альфа и бета
                        sumProb += prob[j];
                    }
                }
                for (int j = 0; j < N; j++) {
                    prob[j] /= sumProb;
                }

                float randomValue = static_cast<float>(rand()) / RAND_MAX;
                float lentaProb = 0.0f;
                int nextCity = -1;

                for (int j = 0; j < N; j++) {
                    lentaProb += prob[j];
                    if (randomValue <= lentaProb) {
                        nextCity = j;
                        break;
                    }
                }

                if (nextCity != -1) {
                    ant.road.push_back(nextCity);
                    ant.visited[nextCity] = true;
                }
            }

            ant.distance = calculDist(ant.road);
        }

        updPhero(evapor, ants);


        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << fixed << setprecision(3) << setw(8) << pheromons[i][j];
            }
            cout << endl;
        }


        Ant bestAnt = BestAnt(ants);
        cout << "Лучший маршрут в итерации: ";
        for (int i = 0;  i < bestAnt.road.size(); i++) {
            cout << bestAnt.road[i] << " ";
        }
        cout << "======= Длина: " << bestAnt.distance << endl;

        if (bestAnt.distance < bestDistance) {
            bestDistance = bestAnt.distance;
            bestRoad = bestAnt.road;
        }
    }

    cout << "\nСамый лучший маршрут за все итерации: ";
    for (int i = 0; i < bestRoad.size(); i++) {
        cout << bestRoad[i] << " ";
    }
    cout << "======= Длина: " << bestDistance << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));


    int iterations;
    float evapor = 0.3f;
    float alpha;
    float beta;
    float startPhero;

    cout << "Введите количество городов: ";
    cin >> N;

    cout << "Введите количество итераций: ";
    cin >> iterations;

    cout << "Введите значение альфа (феромоны): ";
    cin >> alpha;

    cout << "Введите значение бета (расстояние): ";
    cin >> beta;

    cout << "Введите начальное значение феромонов: ";
    cin >> startPhero;

    algoAnt(N, iterations, evapor, alpha, beta, startPhero);

    return 0;
}
