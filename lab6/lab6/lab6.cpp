#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include "Windows.h"

using namespace std;


struct CodeHuff {
    vector<bool> str_code;
    unordered_map<char, vector<bool>> huffmanCode;
    string str_decode;

    void Read_Code() {
        for (bool bit : str_code) {
            cout << bit;
        }
        cout << endl;
    }

    void Read_Decode() {
        cout << "Декодированная строка: " << str_decode << endl;
    }

    void PrintFrequency(string input) {
        unordered_map<char, int> freq;

        for (char ch : input) {
            freq[ch]++;
        }

        cout << "\nЧастота символов:\n";
        for (auto& pair : freq) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void Codes_Chars(string text) {
        vector<pair<char, int>> freqList;
        for (auto pair : huffmanCode) {
            freqList.emplace_back(pair.first, pair.second.size());
        }

        sort(freqList.begin(), freqList.end(), [](pair<char, int> a, pair<char, int> b) {
            return a.second < b.second;
            });

        for (auto p : freqList) {
            char ch = p.first;
            cout << ch << " - ";
            for (bool bit : huffmanCode[ch]) {
                cout << bit;
            }
            cout << endl;
        }
    }
} code;

struct Node {
    char ch;
    int freq;
    Node* left, * right;
};

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

Node* addNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void encode(Node* root, vector<bool> ch, unordered_map<char, vector<bool>>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = ch;
    }

    ch.push_back(0);
    encode(root->left, ch, huffmanCode);
    ch.pop_back();

    ch.push_back(1);
    encode(root->right, ch, huffmanCode);
    ch.pop_back();
}

void decode(Node* root, int& index, const vector<bool>& codee) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        code.str_decode += root->ch;
        return;
    }

    if (index >= codee.size()) {
        return;
    }

    if (codee[index] == 0) {
        decode(root->left, ++index, codee);
    }
    else {
        decode(root->right, ++index, codee);
    }
}

void makeTreeHuff(string text) {
    unordered_map<char, int> freq;

    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto& pair : freq) {
        pq.push(addNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(addNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, vector<bool>> huffmanCode;
    vector<bool> emptyVec;
    encode(root, emptyVec, huffmanCode);
    code.huffmanCode = huffmanCode;

    for (char ch : text) {
        for (bool bit : huffmanCode[ch]) {
            code.str_code.push_back(bit);
        }
    }

    int index = 0;
    while (index < code.str_code.size()) {
        decode(root, index, code.str_code);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    string input = "";
    bool inFlag = false;
    bool codeFlag = false;
    int choise;
    cout << "1. Ввод строки\n2.Кодирование алгоритмом Хаффмана\n3.Таблица кодов символов введенной строки\n4.Декодировать строку\n5.Сэкономленные символы\n6.Частота символов\n? ";
    cin >> choise;
    cin.ignore();
    do {
        switch (choise) {
        case 1:
            getline(cin, input);
            inFlag = true;
            break;
        case 2:
            if (!inFlag) {
                cout << "Для того, чтобы закодировать строку, нужно ее ввести!" << endl;
            }
            else {
                makeTreeHuff(input);
                code.Read_Code();
                codeFlag = true;
            }
            break;
        case 3:
            if (!codeFlag) {
                cout << "Для того, чтобы вывести таблицу, нужно закодировать строку!" << endl;
            }
            else {
                code.Codes_Chars(input);
            }
            break;
        case 4:
            code.Read_Decode();

            break;

        case 5:
            cout << "Сэкономленное место: " << code.str_decode.size() * 8 - code.str_code.size() << " бит" << endl;
            break;
        case 6:
            code.PrintFrequency(input);
            break;
        default:
            break;
        }
        cout << "1. Ввод строки\n2.Кодирование алгоритмом Хаффмана\n3.Таблица кодов символов введенной строки\n4.Декодировать строку\n? ";
        cin >> choise;
        cin.ignore();
    } while (choise != 0);

    return 0;
}
