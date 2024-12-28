#include <iostream>
#include <string>
using namespace std;

template <class E>
class Collection {
public:
    Collection(int capacity) {
        data = new E[capacity];  // ���� �迭 �Ҵ�
        top = 0;                 // top�� 0���� �ʱ�ȭ
    }

    virtual bool Add(E& e) {
        data[top++] = e;         // ��ü �߰� �� top ����
        return true;
    }

    virtual E& Search(string str) {
        for (int i = 0; i < top; i++) {
            if (data[i].getEname() == str) {  // �̸��� �������� �˻�
                return data[i];
            }
        }
        throw runtime_error("�ش� �̸��� ������ �����ϴ�.");
    }

    E& Delete(int index) {
        if (index < 0 || index >= top) {
            throw out_of_range("�߸��� �ε����Դϴ�.");
        }
        E& itemToDelete = data[index];  // ������ ��ü�� ����
        for (int i = index; i < top - 1; i++) {
            data[i] = data[i + 1];      // �迭�� �� ĭ�� ���
        }
        top--;                          // top ����
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
                this->data[i + 1] = this->data[i];  // �迭�� ���������� �̵�
            }
            else {
                break;
            }
        }
        this->data[i + 1] = e;  // ������ ��ġ�� �߰�
        this->top++;
        return true;
    }

    E& Search(string str) override {
        for (int i = 0; i < this->top; i++) {
            if (this->data[i].getEname() == str) {
                return this->data[i];
            }
        }
        throw runtime_error("�ش� �̸��� ������ �����ϴ�.");
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
    // Employee ��ü�� ��� Collection �ʱ�ȭ
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

    // OrderedCollection ��ü �ʱ�ȭ
    OrderedCollection<Employee>* listSet = new OrderedCollection<Employee>(5);
    listSet->Add(e1);
    listSet->Add(e2);
    listSet->Add(e3);
    listSet->Add(e4);
    listSet->Add(e5);

    // Search ����
    try {
        Employee& foundEmployee = collectSet->Search("John");
        cout << "Collection���� ã�� ����: " << foundEmployee.getEname() << ", ����: " << foundEmployee.getAge() << endl;
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    try {
        Employee& foundOrderedEmployee = listSet->Search("Jane");
        cout << "OrderedCollection���� ã�� ����: " << foundOrderedEmployee.getEname() << ", ����: " << foundOrderedEmployee.getAge() << endl;
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
