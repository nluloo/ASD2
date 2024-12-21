#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

#define COUNT_BOXES 100
#define COUNT_COMPLETE_BOXES 50


bool SearchBox(vector<int> box) {
	int result = 0;
	for (int prisoner = 0; prisoner < COUNT_BOXES; prisoner++) {
		bool found = false;
		for (int boxes = 0; boxes < COUNT_COMPLETE_BOXES; boxes++) {
			int randomBox = rand() % COUNT_BOXES;

			if (box[randomBox] == prisoner) {
				found = true;
				break;
			}
		}

		if (!found) { // Хоть один не находит
			return false;
		}

	}

	return true;
}

bool AlgoSearch(vector<int> box) {
	for (int prisoner = 0; prisoner < COUNT_BOXES; prisoner++) {
		bool found = false;
		int temp = prisoner;
		for (int boxes = 0; boxes < COUNT_COMPLETE_BOXES; boxes++) {
			if (box[temp] == prisoner) {
				found = true;
				break;
			}
			else {
				temp = box[temp];
			}
		}
		if (!found) {
			return false;
		}
	}

	return true;	
}


int main() {
	srand(time(0));

	vector<int> box;

	for (int i = 0; i < COUNT_BOXES; i++) {
		box.push_back(i);
	}
	
	int N;
	cin >> N;

	int lob = 0;
	int algo = 0;
	for (int i = 0; i < N; i++) {
		random_shuffle(box.begin(), box.end());
		
		if (SearchBox(box)) {
			lob++;
		}

		if (AlgoSearch(box)) {
			algo++;
		}
	}

	cout << "LOB: " << lob << endl;
	cout << "Algo: " << algo << endl;

	return 0;
}