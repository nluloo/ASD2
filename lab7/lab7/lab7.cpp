#include <iostream>
#include <stack>

using namespace std;

void createArr(int size, int** arr, int** dp, int** prev) {
    *arr = new int[size];
    *dp = new int[size];
    *prev = new int[size];
    int numbers;

    for (int i = 0; i < size; i++) {
        cin >> numbers;
        (*arr)[i] = numbers;
    }

    for (int i = 0; i < size; i++) {
        (*dp)[i] = 1;
        (*prev)[i] = -1;
    }

}

void calculDP(int size, int** arr, int** dp, int** prev) {
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if ((*arr)[j] < (*arr)[i]) {
                if ((*dp)[j] + 1 > (*dp)[i]) { // Если хочется выводить другие строки, поменять на >=
                    (*dp)[i] = (*dp)[j] + 1;
                    (*prev)[i] = j;
                }
            }
        }
    }
}

pair<int,int> max_Length(int size, int* dp) {
    int maxLength = 0;
    int markMax = 0;
    for (int i = 0; i < size; i++) {
        if (dp[i] > maxLength) {// Если хочется выводить другие строки, поменять на >=
            maxLength = dp[i];
            markMax = i;
        }
    }

    return pair<int, int>(maxLength, markMax);
}

void printMaxP(int size, int mark, int* arr, int* prev) {
    stack<int> q;
    int i = mark;
    while (i != -1) {
        q.push(arr[i]);
        i = prev[i];
    }

    cout << "\nМаксимальная подпоследовательность: ";
    while (!q.empty()) {
        cout << q.top() << ' ';
        q.pop();
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int* arr = nullptr;
    int* dp = nullptr;
    int* prev = nullptr;
    pair<int, int> maxLength;
    int size;
    int choice;
    bool flagW = false;
    cout << "1. Ввод последовательности\n2. Вычисление максимальной подпоследовательности\n3. Вывод prev" << endl;
    cin >> choice;
    do
    {
        switch (choice)
        {
        case 1:
            flagW = false;
            if (arr != nullptr) {
                delete[] arr;
            }
            if (dp != nullptr) {
                delete[] dp;
            }
            if (prev != nullptr) {
                delete[] prev;
            }
            system("cls");
            cout << "Введите размер последовательности: ";
            cin >> size;

            createArr(size, &arr, &dp, &prev);
            flagW = true;
            break;

        case 2:
            if (!flagW) {
                break;
            }
            calculDP(size, &arr, &dp, &prev);

            maxLength = max_Length(size, dp);

            cout << "Максимальная длина: " << maxLength.first << endl;
            printMaxP(size, maxLength.second, arr, prev);
            break;
        case 3:
            if (!flagW) {
                break;
            }
            for (int i = 0; i < size; i++) {
                cout << prev[i] << ' ';
            }
            break;
        }
        cout << "\n1. Ввод последовательности\n2. Вычисление максимальной подпоследовательности\n3. Вывод prev" << endl;
        cin >> choice;
    } while (choice != 0);

    delete[] arr;
    delete[] dp;
    delete[] prev;


    return 0;
}
