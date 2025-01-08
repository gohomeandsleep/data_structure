#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class SimpleObject5 {
public:
    static const int NO = 1;
    static const int NAME = 2;

    string no;
    string name;

    SimpleObject5(string sno = "", string sname = "") : no(sno), name(sname) {}

    friend ostream& operator<<(ostream& os, const SimpleObject5& obj) {
        return os << "(" << obj.no << ") " << obj.name;
    }

    // Comparator for ordering by number
    struct NoOrderComparator {
        bool operator()(const SimpleObject5& a, const SimpleObject5& b) const {
            return a.no < b.no;
        }
    };

    // Comparator for ordering by name
    struct NameOrderComparator {
        bool operator()(const SimpleObject5& a, const SimpleObject5& b) const {
            return a.name < b.name;
        }
    };

    void scanData(const string& guide, int sw) {
        cout << guide << "할 데이터를 입력하세요: " << endl;
        if (sw & NO) {
            cout << "번호: ";
            cin >> no;
        }
        if (sw & NAME) {
            cout << "이름: ";
            cin >> name;
        }
    }
};

class ChainHash5 {
private:
    struct Node {
        SimpleObject5 data;
        Node* next;

        Node(const SimpleObject5& s, Node* p = nullptr) : data(s), next(p) {}
    };

    int size;
    vector<Node*> table;

public:
    ChainHash5(int capacity) : size(capacity), table(capacity, nullptr) {}

    int hashValue(const string& key) const {
        int hash = stoi(key) % size;
        return hash;
    }

    bool search(const SimpleObject5& st, const function<bool(const SimpleObject5&, const SimpleObject5&)>& cmp) {

    }

    bool add(const SimpleObject5& st, const function<bool(const SimpleObject5&, const SimpleObject5&)>& cmp) {
  
    }

    bool remove(const SimpleObject5& st, const function<bool(const SimpleObject5&, const SimpleObject5&)>& cmp) {
    
    }

    void dump() const {
        for (int i = 0; i < size; ++i) {
 
        }
    }

    ~ChainHash5() {
        for (int i = 0; i < size; ++i) {

        }
    }
};

enum class Menu {
    Add, Delete, Search, Show, Exit
};

Menu selectMenu() {
    int choice;
    do {
        cout << "(0) 삽입 (1) 삭제 (2) 검색 (3) 출력 (4) 종료 : ";
        cin >> choice;
    } while (choice < static_cast<int>(Menu::Add) || choice > static_cast<int>(Menu::Exit));
    return static_cast<Menu>(choice);
}

int main() {
    ChainHash5 hash(13);
    SimpleObject5 data;
    Menu menu;

    do {
        menu = selectMenu();
        switch (menu) {
        case Menu::Add:
            data.scanData("삽입", SimpleObject5::NO | SimpleObject5::NAME);
            if (!hash.add(data, SimpleObject5::NoOrderComparator()))
                cout << " 중복 데이터가 존재합니다." << endl;
            else
                cout << " 입력 처리됨." << endl;
            break;
        case Menu::Delete:
            data.scanData("삭제", SimpleObject5::NO);
            if (hash.remove(data, SimpleObject5::NoOrderComparator()))
                cout << " 삭제 처리됨." << endl;
            else
                cout << " 삭제할 데이터가 없습니다." << endl;
            break;
        case Menu::Search:
            data.scanData("검색", SimpleObject5::NO);
            if (hash.search(data, SimpleObject5::NoOrderComparator()))
                cout << " 검색 데이터가 존재합니다." << endl;
            else
                cout << " 검색 데이터가 없습니다." << endl;
            break;
        case Menu::Show:
            hash.dump();
            break;
        case Menu::Exit:
            break;
        }
    } while (menu != Menu::Exit);

    return 0;
}
