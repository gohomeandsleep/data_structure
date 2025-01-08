#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>
using namespace std;

// --- SimpleObject2 클래스 --- //
class SimpleObject2 {
public:
    static const int NO = 1;
    static const int NAME = 2;
    string sno;   // 회원번호
    string sname; // 이름

    SimpleObject2() : sno(""), sname("") {}
    SimpleObject2(string sno, string sname) : sno(move(sno)), sname(move(sname)) {}

    string toString() const {
        return "(" + sno + ") " + sname;
    }

    void scanData(const string& guide, int sw) {
        cout << guide << "할 데이터를 입력하세요:\n";
        if (sw & NO) {
            cout << "번호: ";
            cin >> sno;
        }
        if (sw & NAME) {
            cout << "이름: ";
            cin >> sname;
        }
    }

    static bool noOrderComparator(const SimpleObject2& d1, const SimpleObject2& d2) {
        return d1.sno < d2.sno;
    }
};

// --- OpenHash 클래스 --- //
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

// --- 메뉴 열거형 --- //
enum class Menu {
    ADD, REMOVE, SEARCH, DUMP, TERMINATE
};

Menu selectMenu() {
    int choice;
    do {
        cout << "(0) 추가  (1) 삭제  (2) 검색  (3) 표시  (4) 종료 : ";
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
            temp.scanData("추가", SimpleObject2::NO | SimpleObject2::NAME);
            int result = hash.add(temp, SimpleObject2::noOrderComparator);
            if (result == 1) {
                cout << "그 키값은 이미 등록되어 있습니다.\n";
            }
            else if (result == 2) {
                cout << "해시 테이블이 가득 찼습니다.\n";
            }
            break;
        }
        case Menu::REMOVE: {
            SimpleObject2 temp;
            temp.scanData("삭제", SimpleObject2::NO);
            int result = hash.remove(temp, SimpleObject2::noOrderComparator);
            if (result == 0) {
                cout << "삭제 완료\n";
            }
            else {
                cout << "삭제 데이터가 없음\n";
            }
            break;
        }
        case Menu::SEARCH: {
            SimpleObject2 temp;
            temp.scanData("검색", SimpleObject2::NO);
            SimpleObject2* result = hash.search(temp, SimpleObject2::noOrderComparator);
            if (result) {
                cout << "그 키를 갖는 데이터는 " << result->toString() << "입니다.\n";
            }
            else {
                cout << "해당 데이터가 없습니다.\n";
            }
            break;
        }
        case Menu::DUMP:
            hash.dump();
            break;
        case Menu::TERMINATE:
            cout << "프로그램을 종료합니다.\n";
            break;
        }
    } while (menu != Menu::TERMINATE);

    return 0;
}
