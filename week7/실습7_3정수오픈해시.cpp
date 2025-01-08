#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
using namespace std;

// --- ��Ŷ�� ���� --- //
enum class Status { OCCUPIED, EMPTY, DELETED }; // ������ ����, �������, ���� �Ϸ�

// --- ��Ŷ Ŭ���� --- //
class Bucket {
private:
    int data;       // ������
    Status stat;    // ����

public:
    Bucket() : data(0), stat(Status::EMPTY) {} // �⺻ ������

    void set(int data, Status stat) { // ��� �ʵ忡 ���� ����
        this->data = data;
        this->stat = stat;
    }

    void setStat(Status stat) { // ���� ����
        this->stat = stat;
    }

    int getValue() const { // ������ ��ȯ
        return data;
    }

    Status getStatus() const { // ���� ��ȯ
        return stat;
    }
};

// --- ���� �ؽ� Ŭ���� --- //
class OpenHash2 {
private:
    int size;                // �ؽ� ���̺� ũ��
    vector<Bucket> table;    // �ؽ� ���̺�

    // --- �ؽð� ��� --- //
    int hashValue(int key) const {
        return (key * key) % size;
    }

    // --- ���ؽð� ��� --- //
    int rehashValue(int hash) const {
        return (hash + 1) % size;
    }

    // --- Ű�� key�� ���� ��Ŷ �˻� --- //
    Bucket* searchNode(int key) {

    }

public:
    OpenHash2(int size) : size(size), table(size) {}

    // --- Ű�� key�� �˻� --- //
    int search(int key) {

    }

    // --- Ű�� key�� �߰� --- //
    int add(int data) {
 
    }

    // --- Ű�� key�� ���� --- //
    int remove(int key) {

    }

    // --- �ؽ� ���̺� ��� --- //
    void dump() const {
        for (int i = 0; i < size; i++) {
   
        }
    }
};

// --- �޴� ������ --- //
enum class Menu {
    ADD, REMOVE, SEARCH, DUMP, TERMINATE
};

// --- �޴� ���� --- //
Menu selectMenu() {
    int key;
    do {
        cout << "\n(0) �߰� (1) ���� (2) �˻� (3) ǥ�� (4) ���� : ";
        cin >> key;
    } while (key < 0 || key > 4);
    return static_cast<Menu>(key);
}

// --- ���� �Լ� --- //
int main() {
    OpenHash2 hash(13);
    const int count = 8;

    while (true) {
        Menu menu = selectMenu();

        switch (menu) {
        case Menu::ADD: {
            int input[count];
            cout << "���� ������ �߰�:";
            for (int i = 0; i < count; i++) {
                input[i] = rand() % 20;
                cout << " " << input[i];
            }
            cout << endl;

            for (int i = 0; i < count; i++) {
                int result = hash.add(input[i]);
                if (result == 1)
                    cout << "(" << input[i] << ") �̹� ��ϵǾ� �ֽ��ϴ�." << endl;
                else if (result == 2)
                    cout << "�ؽ� ���̺��� ���� á���ϴ�." << endl;
            }
            break;
        }

        case Menu::REMOVE: {
            int key;
            cout << "������ ������: ";
            cin >> key;
            int result = hash.remove(key);
            if (result == 0)
                cout << "���� �Ϸ�" << endl;
            else
                cout << "���� ����: �����Ͱ� �������� �ʽ��ϴ�." << endl;
            break;
        }

        case Menu::SEARCH: {
            int key;
            cout << "�˻��� ������: ";
            cin >> key;
            int result = hash.search(key);
            if (result != 0)
                cout << "�˻� ����: " << result << endl;
            else
                cout << "�˻� ����: �����Ͱ� �������� �ʽ��ϴ�." << endl;
            break;
        }

        case Menu::DUMP:
            hash.dump();
            break;

        case Menu::TERMINATE:
            return 0;
        }
    }
}
