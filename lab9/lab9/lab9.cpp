#include <iostream>
#include <vector>
#include <iomanip>
#include <set>


// ДОБАВИТЬ МЕТОДЫ СКРЕЩИВАНИЯ, ММУТАЦИИ, ДОБАВЛЕНИЕ ПОТОМКОВ В ПОПУЛЯЦИЮ 

using namespace std;

static int v = 8;

struct chromosome {
    vector<int> route;
    int distance = 0;


    void calcDist(vector<vector<int>> matr) {
        for (int i = 1; i < route.size(); i++) {
            distance += matr[route[i - 1]][route[i]];
        }
        //distance += matr[route.back()][route.front()];
    }

    bool operator<(const chromosome& other) const {
        return route < other.route; 
    }
};


/*vector<vector<int>> matrix = {
    { 0, 25, 40, 31, 27},
    { 5, 0, 17, 30, 25},
    { 19, 15, 0, 6, 1},
    { 9, 50, 24, 0, 6 },
    { 22, 8, 7, 10, 0 }
};*/

vector<vector<int>> matrix = {
    {0, 1, 15, 20, 25, 30, 35, 40},
    {12, 0, 1, 22, 27, 32, 37, 42},
    {14, 16, 0, 1, 28, 33, 38, 43},
    {17, 19, 21, 0, 1, 34, 39, 44},
    {22, 24, 26, 30, 0, 1, 41, 46},
    {27, 29, 31, 35, 38, 0, 1, 48},
    {32, 34, 36, 40, 43, 46, 0, 1},
    {1, 39, 41, 45, 48, 51, 54, 0}
};

void deleteCity(vector<vector<int>>& mat, int city) {
    mat.erase(mat.begin() + city);

    for (int i = 0; i < mat.size(); i++) {
        mat[i].erase(mat[i].begin() + city); 
    }
    v--;
}

void addCity(vector<vector<int>>& mat) {
    int length = 0;
    vector<int> buff(v + 1, 0);

    for (int i = 0; i < v; i++) {
        cout << "Введите расстояние от нового города до города " << i + 1 << ": ";
        cin >> length;
        buff[i] = length; 
    }

    mat.push_back(buff);

    for (int i = 0; i < v; i++) {
        cout << "Введите расстояние от города " << i + 1 << " до нового города: ";
        cin >> length;
        mat[i].push_back(length);
    }

    v++;
}

int rand_num(int start, int end)
{
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

bool contains(vector<int>& vec, int element) {
    return find(vec.begin(), vec.end(), element) != vec.end();
}

vector<int> createChromo() {
    chromosome buff;
    buff.route.push_back(0);
    while (true) {
        if (buff.route.size() == v) {
            buff.route.push_back(0);
            break;
        }
        int temp = rand_num(1, v);

        if (!contains(buff.route, temp)) {
            buff.route.push_back(temp);
        }
    }
    return buff.route;
}

void printPopul(vector<chromosome> population) {
    for (int i = 0; i < population.size(); i++) {
        cout << "Вывод " << i + 1 << " потомка\n ";
        cout << "Последовательность: ";
        for (int j = 0; j < population[i].route.size(); j++) {
            cout << population[i].route[j] + 1 << ' ';
        }
        cout << endl;
        cout << "Расстояние: " << population[i].distance << endl;
    }
}

chromosome crossing(chromosome rod1, chromosome rod2) {
    int point = 1;
    chromosome buff1;
    for (int i = 0; i < rod1.route.size(); i++) {
        if(i <= point) buff1.route.push_back(rod1.route[i]);
        else {
            for (int j = 0; j < rod2.route.size(); j++) {
                if (!contains(buff1.route, rod2.route[j])) {
                    buff1.route.push_back(rod2.route[j]);
                }
            }
            if (buff1.route.size() == rod2.route.size() - 1) break;
        }
    }

    buff1.route.push_back(0);
    buff1.calcDist(matrix);
    return buff1;

}

chromosome mutat(chromosome rod1, chromosome rod2) {

    chromosome buff;
    for (int i = 0; buff.route.size() != rod1.route.size() - 1; i++) {
        if (i > rod1.route.size() - 1) {
            int index = i % (rod1.route.size() - 1);

            if (index % 2 == 0) {
                if (!contains(buff.route, rod2.route[index])) {
                    buff.route.push_back(rod2.route[index]);
                    continue;
                }
            }
            else {
                if (!contains(buff.route, rod1.route[index])) {
                    buff.route.push_back(rod1.route[index]);
                    continue;
                }
            }
            continue;
        }
        if (i % 2 == 0) {
            if (!contains(buff.route, rod1.route[i])) {
                buff.route.push_back(rod1.route[i]);
            }
        }
        else {
            if (!contains(buff.route, rod2.route[i])) {
                buff.route.push_back(rod2.route[i]);
            }
        }
    }
    buff.route.push_back(0);
    buff.calcDist(matrix);

    return buff;
}

void min(vector<chromosome> pop) {
    int min = INT_MAX;
    chromosome buff;
    for (int i = 0; i < pop.size(); i++) {
        if (min > pop[i].distance) {
            min = pop[i].distance;
            buff = pop[i];
        }
    }

    cout << "Минимальный путь данной эволюции:\n";
    for (int i = 0; i < buff.route.size(); i++) {
        cout << buff.route[i] + 1 << ' ';
    }
    cout << " ---------- ";
    cout << "Длина пути: " << buff.distance << endl;
    cout << "\n===============================" << endl;

}

void genetic(int sizePopul, int countEvo, int countChild, int crossing1, float mutation) {
    srand(time(0));

    set<chromosome> populationSet;  
    chromosome buff;

    while(populationSet.size() != sizePopul) {
        buff.route = createChromo();
        buff.calcDist(matrix);
        populationSet.insert(buff);
        buff.distance = 0;
    }
    vector<chromosome> population(populationSet.begin(), populationSet.end());

    cout << "Начальная популяция\n";
    printPopul(population);
    min(population);

    for (int i = 1; i <= countEvo; i++) {
        int tempSize = populationSet.size();
        int b = 0;
        while (populationSet.size() != tempSize + countChild * crossing1 && b != 100) {// Если за 100 иттераций не найдет новый ген, то посылаем его
            chromosome child1 = population[rand_num(0, population.size())];
            chromosome child2 = population[rand_num(0, population.size())];
            populationSet.insert(crossing(child1, child2));
            populationSet.insert(crossing(child2, child1));
            b++;
        }

        if ((int)(mutation * 100) > rand_num(0, 100)) {
            cout << "Произошла мутация!!!!!" << endl;
            int newtempSize = populationSet.size();
            int a = 0;
            while (populationSet.size() != newtempSize + 1 && a != 20) { // Если за 20 иттераций не найдет новый ген, то посылаем его
                populationSet.insert(mutat(population[rand_num(0, population.size())], population[rand_num(0, population.size())]));
                a++;
            }
        }


        while (populationSet.size() != tempSize) {
            vector<chromosome> population(populationSet.begin(), populationSet.end());
            int max = 0;
            chromosome buff;
            for (int i = 0; i < population.size(); i++) {
                if (max < population[i].distance) {
                    buff = population[i];
                    max = population[i].distance;
                }
            }
            populationSet.erase(buff);
        }

        vector<chromosome> population(populationSet.begin(), populationSet.end());

        cout << '\n' << i << " поколение:\n";
        printPopul(population);
        min(population);

    }
}



int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));


    int sizePopul = 0, crossing = 0, countChild = 2, evolution = 0;
    float mutation = 0;


    cout << "Введите размер популяции: "; cin >> sizePopul;
    cout << "Введите количество эволюций: "; cin >> evolution;
    cout << "Количество родителей: " << countChild << endl;
    cout << "Введите количество скрещиваний: "; cin >> crossing;
    cout << "Введите шанс мутации: "; cin >> mutation;

    genetic(sizePopul, evolution, countChild, crossing, mutation);


    return 0;
}
