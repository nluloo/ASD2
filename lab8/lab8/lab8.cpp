#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct Item {
    string name;
    int weight = 0;
    int price = 0;

    Item(string name, int w, int p) {
        this->name = name;
        this->weight = w;
        this->price = p;
    }
};

vector<Item> finish;

void FindAns(vector<Item>& items, int** matrix, int we, int N) {
    if (N == 0 || we == 0) {
        return;
    }
    if (matrix[N][we] != matrix[N - 1][we]) {
        cout << items[N - 1].name << " (Вес: " << items[N - 1].weight << ", Цена: " << items[N - 1].price << ")" << endl;
        finish.push_back(items[N - 1]);
        FindAns(items, matrix, we - items[N - 1].weight, N - 1);
    }
    else {
        FindAns(items, matrix, we, N - 1);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int we = 13;
    int N;

    cout << "Введите количество предметов: ";
    cin >> N;

    vector<Item> items;

    for (int i = 0; i < N; i++) {
        string name;
        cout << "Введите название " << i + 1 << " предмета: ";
        cin >> name;
        int w, p;
        cout << "Введите вес и цену: ";
        cin >> w >> p;
        items.push_back(Item(name, w, p));
    }

    int** matrix = new int* [N + 1];
    for (int i = 0; i <= N; i++) {
        matrix[i] = new int[we + 1](); // нули
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= we; j++) {
            if (j >= items[i - 1].weight) {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i - 1][j - items[i - 1].weight] + items[i - 1].price);
            }
            else {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }


    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= we; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    cout << "Выбранные предметы для максимальной стоимости:" << endl;
    FindAns(items, matrix, we, N);
    int maxPrice = 0;
    for (int i = 0; i < finish.size(); i++) {
        maxPrice += finish[i].price;
    }
    cout << "Максимальная цена рюкзака: " << maxPrice << endl;

    for (int i = 0; i <= N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}