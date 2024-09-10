#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void hanoi(int, int, int, int);
int sum = 0;

int main() {
	setlocale(LC_ALL, "ru");
	int N, k, i = 1; // ���������� ������, r������� �������� �� 3
	cout << "������� ���������� ������: ";
	cin >> N;
	if (N <= 0) {
		cout << "Error" << endl;
		return 1;
	}
	cout << "������� ����� �������, �� ������� ������ ������������� ����� (2 ��� 3): ";
	cin >> k;
	if (k < 1 || k > 3) {
		cout << "Error" << endl;
		return 1;
	}
	int hlp = 6 - k - i; // ������������ ��������
	if (k != 1) {
		auto start_value = chrono::high_resolution_clock::now();
		hanoi(N, i, k, hlp);
		auto end_value = chrono::high_resolution_clock::now();
		chrono::duration<double, nano> difference_value = end_value - start_value;
		cout << "Win!" << endl;
		cout << "\n����� ����������: " << difference_value.count() << " ����������\n" << endl;
	}
	else {
		cout << "Win!" << endl;
	}
	cout << sum << " �����" << endl;

	return 0;
}

void hanoi(int N, int i, int k, int hlp) {
	sum++;
	if (N == 1) {
		cout << "����������� ���� " << N << " � " << i << " �� " << k << endl;
	}
	else {
		hanoi(N - 1, i, hlp, k);
		cout << "����������� ���� " << N << " � " << i << " �� " << k << endl;
		hanoi(N - 1, hlp, k, i);
	}
}