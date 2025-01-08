#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>
using namespace std;

// --- SimpleObject2 Ŭ���� --- //
class SimpleObject2 {
public:
    static const int NO = 1;
    static const int NAME = 2;
    string sno;   // ȸ����ȣ
    string sname; // �̸�

    SimpleObject2() : sno(""), sname("") {}
    SimpleObject2(string sno, string sname) : sno(move(sno)), sname(move(sname)) {}

    string toString() const {
        return "(" + sno + ") " + sname;
    }

    void scanData(const string& guide, int sw) {
        cout << guide << "�� �����͸� �Է��ϼ���:\n";
        if (sw & NO) {
            cout << "��ȣ: ";
            cin >> sno;
        }
        if (sw & NAME) {
            cout << "�̸�: ";
            cin >> sname;
        }
    }

    static bool noOrderComparator(const SimpleObject2& d1, const SimpleObject2& d2) {
        return d1.sno < d2.sno;
    }
};

// --- OpenHash Ŭ���� --- //
class OpenHash {
private:
    enum class Status { OCCUPIED, EMPTY, DELETED };

    struct Bucket {
        SimpleObject2 data;
        Status stat;

        Bucket() : stat(Status::EMPTY) {}

        void set(const SimpleObject2& data, Status stat) {
            this->data = data;
            this->stat = stat;
        }
    };

    vector<Bucket> table;
    int size;

    int hashValue(const string& key) const {
        return stoi(key) % size;
    }

    int rehashValue(int hash) const {
        return (hash + 1) % size;
    }

    Bucket* searchNode(const SimpleObject2& key, function<bool(const SimpleObject2&, const SimpleObject2&)> comp) {

    }

public:
    OpenHash(int size) : size(size), table(size) {}

    int add(const SimpleObject2& key, function<bool(const SimpleObject2&, const SimpleObject2&)> comp) {
  
    }

    int remove(const SimpleObject2& key, function<bool(const SimpleObject2&, const SimpleObject2&)> comp) {

    }

    SimpleObject2* search(const SimpleObject2& key, function<bool(const SimpleObject2&, const SimpleObject2&)> comp) {
 
    }

    void dump() const {
        for (int i = 0; i < size; ++i) {
   
        }
    }
};

// --- �޴� ������ --- //
enum class Menu {
    ADD, REMOVE, SEARCH, DUMP, TERMINATE
};

Menu selectMenu() {
    int choice;
    do {
        cout << "(0) �߰�  (1) ����  (2) �˻�  (3) ǥ��  (4) ���� : ";
        cin >> choice;
    } while (choice < 0 || choice > 4);
    return static_cast<Menu>(choice);
}

int main() {
    OpenHash hash(13);
    Menu menu;

    do {
        menu = selectMenu();
        switch (menu) {
        case Menu::ADD: {
            SimpleObject2 temp;
            temp.scanData("�߰�", SimpleObject2::NO | SimpleObject2::NAME);
            int result = hash.add(temp, SimpleObject2::noOrderComparator);
            if (result == 1) {
                cout << "�� Ű���� �̹� ��ϵǾ� �ֽ��ϴ�.\n";
            }
            else if (result == 2) {
                cout << "�ؽ� ���̺��� ���� á���ϴ�.\n";
            }
            break;
        }
        case Menu::REMOVE: {
            SimpleObject2 temp;
            temp.scanData("����", SimpleObject2::NO);
            int result = hash.remove(temp, SimpleObject2::noOrderComparator);
            if (result == 0) {
                cout << "���� �Ϸ�\n";
            }
            else {
                cout << "���� �����Ͱ� ����\n";
            }
            break;
        }
        case Menu::SEARCH: {
            SimpleObject2 temp;
            temp.scanData("�˻�", SimpleObject2::NO);
            SimpleObject2* result = hash.search(temp, SimpleObject2::noOrderComparator);
            if (result) {
                cout << "�� Ű�� ���� �����ʹ� " << result->toString() << "�Դϴ�.\n";
            }
            else {
                cout << "�ش� �����Ͱ� �����ϴ�.\n";
            }
            break;
        }
        case Menu::DUMP:
            hash.dump();
            break;
        case Menu::TERMINATE:
            cout << "���α׷��� �����մϴ�.\n";
            break;
        }
    } while (menu != Menu::TERMINATE);

    return 0;
}
