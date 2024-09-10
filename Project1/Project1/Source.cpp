#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void hanoi(int, int, int, int);
int sum = 0;

int main() {
	setlocale(LC_ALL, "ru");
	int N, k, i = 1; // Количество дисков, rонечный стержень из 3
	cout << "Введите количество дисков: ";
	cin >> N;
	if (N <= 0) {
		cout << "Error" << endl;
		return 1;
	}
	cout << "Введите номер стержня, на который должны переместиться диски (2 или 3): ";
	cin >> k;
	if (k < 1 || k > 3) {
		cout << "Error" << endl;
		return 1;
	}
	int hlp = 6 - k - i; // Вспомогающий стержень
	if (k != 1) {
		auto start_value = chrono::high_resolution_clock::now();
		hanoi(N, i, k, hlp);
		auto end_value = chrono::high_resolution_clock::now();
		chrono::duration<double, nano> difference_value = end_value - start_value;
		cout << "Win!" << endl;
		cout << "\nВремя выполнения: " << difference_value.count() << " наносекунд\n" << endl;
	}
	else {
		cout << "Win!" << endl;
	}
	cout << sum << " шагов" << endl;

	return 0;
}

void hanoi(int N, int i, int k, int hlp) {
	sum++;
	if (N == 1) {
		cout << "Переместить диск " << N << " с " << i << " на " << k << endl;
	}
	else {
		hanoi(N - 1, i, hlp, k);
		cout << "Переместить диск " << N << " с " << i << " на " << k << endl;
		hanoi(N - 1, hlp, k, i);
	}
}