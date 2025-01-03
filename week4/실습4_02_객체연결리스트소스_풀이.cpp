#include <iostream>
#include <time.h>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};

ostream& operator<<(ostream& os, Employee& e) {
	os << "Eno : " << e.eno << " | Ename : " << e.ename;
	return os;
}

bool Employee::operator==(Employee& other) {
	return this->eno == other.eno;
}

bool Employee::operator<(Employee& other) {
	return this->eno < other.eno;
}

class Node {
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
	Node* first;
public:
	LinkedList() {
		first = nullptr; //headNode�� ���� ����
	}
	void Add(Employee);
	void Show();
	bool Search(string);
	bool Delete(string);
	LinkedList& operator+(LinkedList&);
};

void LinkedList::Add(Employee e) {
	Node* newNode = new Node(e);
	Node* p = first;
	Node* q = nullptr;
	if (p == nullptr) {
		first = newNode;
		return;
	}
	while (p != nullptr) {
		if (e < p->data) {
			if (q == nullptr) {
				first = newNode;
				newNode->link = p;
			}
			else {
				newNode->link = p;
				q->link = newNode;
			}
			return;
		}
		else {
			q = p;
			p = p->link;
			if (p == nullptr) {
				q->link = newNode;
				return;
			}
		}
	}
}

void LinkedList::Show() {
	Node* p = first;
	while (p != nullptr) {
		cout << p->data << endl;
		p = p->link;
	}
}

bool LinkedList::Search(string s) {
	Node* p = first;
	while (p != nullptr) {
		if (p->data.eno == s) {
			return true;
		}
		p = p->link;
	}
	return false;
}

bool LinkedList::Delete(string s) {
	if (first == nullptr) return false;
	Node* p = first;
	Node* q = nullptr;
	while (p != nullptr) {
		if (p->data.eno == s) {
			if (q == nullptr) {
				Node* temp = first;
				first = first->link;
				delete temp;
			}
			else {
				q->link = p->link;
			}
			return true;
		}
		else {
			q = p;
			p = p->link;
		}
	}
	return false;
}

LinkedList& LinkedList::operator+(LinkedList& other) {
	LinkedList* lc = new LinkedList();
	Node* p = first;
	Node* q = other.first;

	while (p != nullptr && q != nullptr) {
		if (p->data < q->data) {
			lc->Add(q->data);
			q = q->link;
		}
		else {
			lc->Add(p->data);
			p = p->link;
		}
	}

	while (p != nullptr) {
		lc->Add(p->data);
		p = p->link;
	}

	while (q != nullptr) {
		lc->Add(q->data);
		q = q->link;
	}
	return *lc;
}

enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};

int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	LinkedList la, lb, lc;
	Employee* data;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			la.Add(*data);
			break;
		case Add2:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			lb.Add(*data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "���� �Ϸ�";
			break;
		case Show:
			cout << "����Ʈ la = \n";
			la.Show();
			cout << "����Ʈ lb = \n";
			lb.Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�.\n";
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�.\n";
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = \n";
			lc.Show();
			break;

		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	
	return 0;
}

