#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

// Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева.
// Ключом будет служить номер автомашины, значением узла — список правонарушений.
// Если квитанция добавляется в первый раз, то в дереве появляется новый узел,
// а в списке данные по правонарушению; если нет, то данные заносятся в существующий
// список Необходимо также реализовать следующие операции :
//   ■ Полная распечатка базы данных(по номерам машин и списку правонарушений,
//     числящихся за ними)
//   ■ Распечатка данных по заданному номеру
//   ■ Распечатка данных по диапазону номеров

struct Node {
    string Nomer;
    vector<string> zalet;
    Node* left;
    Node* right;

    Node(const string& nomer) : Nomer(nomer), left(nullptr), right(nullptr) {}
};

class GaiDatabase
{
    Node* root;

    Node* insertNode(Node* node, const string& nomer, const string& zalet) {
        if (node == nullptr) {
            // Создаем новый узел, если дерево пустое
            Node* newNode = new Node(nomer);
            newNode->zalet.push_back(zalet);
            return newNode;
        }
        // Сравниваем номер автомашины с ключом текущего узла
        if (nomer < node->Nomer) {
            // Переходим в левое поддерево
            node->left = insertNode(node->left, nomer, zalet);
        }
        else if (nomer > node->Nomer) {
            // Переходим в правое поддерево
            node->right = insertNode(node->right, nomer, zalet);
        }
        else {
            // Номер автомашины уже существует, добавляем правонарушение в список
            node->zalet.push_back(zalet);
        }
        return node;
    }

    void showInOrder(Node* node) {
        if (node == nullptr) {
            return;
        }

        // Распечатываем данные левого поддерева
        showInOrder(node->left);

        // Распечатываем номер автомашины
        cout << "Номер автомашины: " << node->Nomer << endl;

        // Распечатываем данные по правонарушениям
        cout << "Правонарушения: ";
        for (const auto& zalet : node->zalet) {
            cout << zalet << " ";
        }
        cout << endl;

        // Распечатываем данные правого поддерева
        showInOrder(node->right);
    }

    void showByNomer(Node* node, const string& nomer) {
        if (node == nullptr) {
            cout << "Номер автомашины не найден" << endl;
            return;
        }
        if (nomer == node->Nomer) {
            cout << "Номер автомашины: " << node->Nomer << endl;
            cout << "Правонарушения: ";
            for (const auto& zalet : node->zalet) {
                cout << zalet << " ";
            }
            cout << endl;
        }
        else if (nomer < node->Nomer) {
            showByNomer(node->left, nomer);
        }
        else {
            showByNomer(node->right, nomer);
        }
    }

    void showInRange(Node* node, const string& start, const string& end) {
        if (node == nullptr) {
            return;
        }
        if (start < node->Nomer) {
            showInRange(node->left, start, end);
        }
        if (start <= node->Nomer && node->Nomer <= end) {
            cout << "Номер автомашины: " << node->Nomer << endl;
            cout << "Правонарушения: ";
            for (const auto& zalet : node->zalet) {
                cout << zalet << " ";
            }
            cout << endl;
        }
        if (node->Nomer < end) {
            showInRange(node->right, start, end);
        }
    }

public:
    GaiDatabase() : root(nullptr) {}

    void addZalet(const string& nomer, const string& zalet) {
        root = insertNode(root, nomer, zalet);
    }

    void showDatabase() {
        showInOrder(root);
    }

    void showByNomer(const string& nomer) {
        showByNomer(root, nomer);
    }

    void showByRange(const string& start, const string& end) {
        showInRange(root, start, end);
    }
};

int main()
{
    SetConsoleOutputCP(1251);

    GaiDatabase database;
    database.addZalet("A123BC-40", "Превышение скорости");
    database.addZalet("X789YZ-97", "Неправильная парковка");
    database.addZalet("A123BC-197", "Проезд на красный свет");
    database.addZalet("A123DE-98", "Не пристёгнутый ремень");
    database.addZalet("A123DE-98", "Проезд на красный свет");
    database.addZalet("D456EF-77", "Использование телефона во время движения");

    cout << "Полная база данных ГАИ:" << endl;
    database.showDatabase();
    cout << endl;

    cout << "Данные по номеру A123BC-40:" << endl;
    database.showByNomer("A123BC-40");
    cout << endl;

    cout << "Данные по диапазону номеров от A123BC-40 до X789YZ-97:" << endl;
    database.showByRange("A123BC-40", "X789YZ-97");

    return 0;
}