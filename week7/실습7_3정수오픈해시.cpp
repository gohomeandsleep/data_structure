#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
using namespace std;

// --- 버킷의 상태 --- //
enum class Status { OCCUPIED, EMPTY, DELETED }; // 데이터 저장, 비어있음, 삭제 완료

// --- 버킷 클래스 --- //
class Bucket {
private:
    int data;       // 데이터
    Status stat;    // 상태

public:
    Bucket() : data(0), stat(Status::EMPTY) {} // 기본 생성자

    void set(int data, Status stat) { // 모든 필드에 값을 설정
        this->data = data;
        this->stat = stat;
    }

    void setStat(Status stat) { // 상태 설정
        this->stat = stat;
    }

    int getValue() const { // 데이터 반환
        return data;
    }

    Status getStatus() const { // 상태 반환
        return stat;
    }
};

// --- 오픈 해시 클래스 --- //
class OpenHash2 {
private:
    int size;                // 해시 테이블 크기
    vector<Bucket> table;    // 해시 테이블

    // --- 해시값 계산 --- //
    int hashValue(int key) const {
        return (key * key) % size;
    }

    // --- 재해시값 계산 --- //
    int rehashValue(int hash) const {
        return (hash + 1) % size;
    }

    // --- 키값 key를 갖는 버킷 검색 --- //
    Bucket* searchNode(int key) {

    }

public:
    OpenHash2(int size) : size(size), table(size) {}

    // --- 키값 key를 검색 --- //
    int search(int key) {

    }

    // --- 키값 key를 추가 --- //
    int add(int data) {
 
    }

    // --- 키값 key를 삭제 --- //
    int remove(int key) {

    }

    // --- 해시 테이블 출력 --- //
    void dump() const {
        for (int i = 0; i < size; i++) {
   
        }
    }
};

// --- 메뉴 열거형 --- //
enum class Menu {
    ADD, REMOVE, SEARCH, DUMP, TERMINATE
};

// --- 메뉴 선택 --- //
Menu selectMenu() {
    int key;
    do {
        cout << "\n(0) 추가 (1) 삭제 (2) 검색 (3) 표시 (4) 종료 : ";
        cin >> key;
    } while (key < 0 || key > 4);
    return static_cast<Menu>(key);
}

// --- 메인 함수 --- //
int main() {
    OpenHash2 hash(13);
    const int count = 8;

    while (true) {
        Menu menu = selectMenu();

        switch (menu) {
        case Menu::ADD: {
            int input[count];
            cout << "랜덤 데이터 추가:";
            for (int i = 0; i < count; i++) {
                input[i] = rand() % 20;
                cout << " " << input[i];
            }
            cout << endl;

            for (int i = 0; i < count; i++) {
                int result = hash.add(input[i]);
                if (result == 1)
                    cout << "(" << input[i] << ") 이미 등록되어 있습니다." << endl;
                else if (result == 2)
                    cout << "해시 테이블이 가득 찼습니다." << endl;
            }
            break;
        }

        case Menu::REMOVE: {
            int key;
            cout << "삭제할 데이터: ";
            cin >> key;
            int result = hash.remove(key);
            if (result == 0)
                cout << "삭제 완료" << endl;
            else
                cout << "삭제 실패: 데이터가 존재하지 않습니다." << endl;
            break;
        }

        case Menu::SEARCH: {
            int key;
            cout << "검색할 데이터: ";
            cin >> key;
            int result = hash.search(key);
            if (result != 0)
                cout << "검색 성공: " << result << endl;
            else
                cout << "검색 실패: 데이터가 존재하지 않습니다." << endl;
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
