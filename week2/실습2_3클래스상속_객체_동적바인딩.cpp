#include <iostream>
#include <string>
using namespace std;

template <class E>
class Collection {
public:
    Collection(int capacity) {
        data = new E[capacity];  // 동적 배열 할당
        top = 0;                 // top을 0으로 초기화
    }

    virtual bool Add(E& e) {
        data[top++] = e;         // 객체 추가 후 top 증가
        return true;
    }

    virtual E& Search(string str) {
        for (int i = 0; i < top; i++) {
            if (data[i].getEname() == str) {  // 이름을 기준으로 검색
                return data[i];
            }
        }
        throw runtime_error("해당 이름의 직원이 없습니다.");
    }

    E& Delete(int index) {
        if (index < 0 || index >= top) {
            throw out_of_range("잘못된 인덱스입니다.");
        }
        E& itemToDelete = data[index];  // 삭제할 객체를 저장
        for (int i = index; i < top - 1; i++) {
            data[i] = data[i + 1];      // 배열을 한 칸씩 당김
        }
        top--;                          // top 감소
        return itemToDelete;
    }

protected:
    E* data;
    int top;
};

template <class E>
class OrderedCollection : public Collection<E> {
public:
    OrderedCollection(int capacity) : Collection<E>(capacity) {}

    bool Add(E& e) override {
        int i;
        for (i = this->top - 1; i >= 0; i--) {
            if (this->data[i].getEname() > e.getEname()) {
                this->data[i + 1] = this->data[i];  // 배열을 오른쪽으로 이동
            }
            else {
                break;
            }
        }
        this->data[i + 1] = e;  // 적절한 위치에 추가
        this->top++;
        return true;
    }

    E& Search(string str) override {
        for (int i = 0; i < this->top; i++) {
            if (this->data[i].getEname() == str) {
                return this->data[i];
            }
        }
        throw runtime_error("해당 이름의 직원이 없습니다.");
    }
};

class Employee {
private:
    string eno;
    string ename;
    int age;
public:
    Employee() : eno(""), ename(""), age(0) {}
    Employee(string eno, string ename, int age) : eno(eno), ename(ename), age(age) {}

    string getEno() const { return eno; }
    string getEname() const { return ename; }
    int getAge() const { return age; }
};

int main() {
    // Employee 객체를 담는 Collection 초기화
    Collection<Employee>* collectSet = new Collection<Employee>(5);
    Employee e1("E001", "John", 30);
    Employee e2("E002", "Jane", 25);
    Employee e3("E003", "Mike", 28);
    Employee e4("E004", "Anna", 35);
    Employee e5("E005", "Tom", 40);

    collectSet->Add(e1);
    collectSet->Add(e2);
    collectSet->Add(e3);
    collectSet->Add(e4);
    collectSet->Add(e5);

    // OrderedCollection 객체 초기화
    OrderedCollection<Employee>* listSet = new OrderedCollection<Employee>(5);
    listSet->Add(e1);
    listSet->Add(e2);
    listSet->Add(e3);
    listSet->Add(e4);
    listSet->Add(e5);

    // Search 예시
    try {
        Employee& foundEmployee = collectSet->Search("John");
        cout << "Collection에서 찾은 직원: " << foundEmployee.getEname() << ", 나이: " << foundEmployee.getAge() << endl;
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    try {
        Employee& foundOrderedEmployee = listSet->Search("Jane");
        cout << "OrderedCollection에서 찾은 직원: " << foundOrderedEmployee.getEname() << ", 나이: " << foundOrderedEmployee.getAge() << endl;
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
