/*
* 4�ܰ�- ���� ��ü ���� ����Ʈ�� iterator ����
* CircularList�� ������� �� iterator�� �����Ѵ�.
* template �������� ���� 
*/
#include <iostream>
#include <time.h>
#include <algorithm>
#include <limits>
using namespace std;

class Employee {
	friend class Node;
	friend class CircularList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:	
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};

ostream& operator<<(ostream& os, Employee& e) {
	os << "Eno : " << e.eno << " | Ename : " << e.ename << " | Salary : " << e.salary;
	return os;
}

bool Employee::operator<(Employee& other) {
	return this->eno < other.eno;
}

bool Employee::operator==(Employee& other) {
	return this->eno == other.eno;
}

char Employee::compare(const Employee* other) const {
	if (this == other) {
		return 0;
	}
	else if (this > other) {
		return 1;
	}
	else {
		return -1;
	}
}

class Node {
	friend class ListIterator;
	friend class CircularList;
	friend ostream& operator<<(ostream& os, CircularList& l);
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* first;
public:
	CircularList() {
		first = new Node(); 
		//Head Node�� �ִ� version
		first->link = first;
	}
	bool Delete(string);
	void Show(); //lb.Show(); �� ��� ��Ҹ� ���
	void Add(Employee*);
	bool Search(string);
	CircularList& operator+(CircularList&); //merge
	friend ostream& operator<<(ostream& os, CircularList& l); //cout << la << endl; �� ��� ��Ҹ� ���
};

ostream& operator<< (ostream& os, CircularList & l) {
	if (l.first->link == l.first) {
		cout << "List is Empty.";
		return os;
	}
	Node* current = l.first->link;
	while (current != l.first) {
		cout << current->data << endl;
		current = current->link;
	}
	return os;
}

void CircularList::Add(Employee* e) {
	Node* newNode = new Node(*e);
	Node* p = first->link;
	Node* q = first;

	if (first->link == first) { //linked list ���� �ƹ��� ���� ����
		first->link = newNode;
		newNode->link = first;
		return;
	}
	
	while (p != first) {
		if (newNode->data < p->data) {//Ż�� ����
			newNode->link = p;
			q->link = newNode;
			
			if (p == first->link) {
				//���� ó�� ��ġ�� ���� ����
				first->link = newNode;
			}
			return;
		}
		//���� ���� �̵�
		q = p;
		p = p->link;
	}

	//������ ��忡 ����
	q->link = newNode;
	newNode->link = first;
}

bool CircularList::Delete(string s) {
	if (first->link == first) return false; //����Ʈ �� �ƹ��� ���� ����
	Node* p = first->link;
	Node* q = nullptr;

	while (p != first) {
		if (p->data.eno == s) {
			if (q == nullptr) { //�Ǿտ��� ���� ����
				first->link = p->link;
			}
			else if (p->link == first) { //�� ���������� ���� ����
				q->link = first;
			}
			else { //������
				q->link = p->link;
			}

			delete p;
			return true;
		}
		q = p;
		p = p->link;
	}
	return false;
}

void CircularList::Show() {
	Node* p = first->link;
	while (p != first) {
		cout << p->data << endl;
		p = p->link;
	}
}

bool CircularList::Search(string s) {
	Node* p = first->link;

	while (p != first) {
		if (p->data.eno == s) {
			cout << p->data << endl;
			return true;
		}
		p = p->link;
	}
	return false;
}

class ListIterator { 
	//���� ����Ʈ�� head node�� �����̹Ƿ� ����Ʈ ������ ��忡 ���޽� ������ �ʿ��ϴ� 
public:
	ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {};
	~ListIterator() {};
	Employee* First();
	Employee* Next();
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const CircularList& list;//existing list
};

Employee* ListIterator::First() {
	return &list.first->data;
}

Employee* ListIterator::Next() {
	current = current->link;
	Employee* p = &current->data;
	return p;
}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

CircularList& CircularList::operator+(CircularList& other) {
	Employee* p, * q;
	ListIterator Aiter(*this), Biter(other);
	CircularList* lc = new CircularList();

	p = Aiter.GetCurrent();
	q = Biter.GetCurrent();

	Employee* p_start = Aiter.First();
	Employee* q_start = Biter.First();

	while (p != p_start && q != q_start) {
		if (q->eno < p->eno) {
			lc->Add(q);
			q = Biter.Next();
			if (Biter.GetCurrent() == q_start) break;
		}
		else {
			lc->Add(p);
			p = Aiter.Next();
			if (Aiter.GetCurrent() == p_start) break;
		}
	}
	while (p->eno != p_start->eno) {
		lc->Add(p);
		p = Aiter.Next();
	}

	while (q->eno != q_start->eno) {
		lc->Add(q);
		q = Biter.Next();
	}
	return *lc;
}

int sum(CircularList& l) {
	int result = 0;

	ListIterator li(l);
	Employee* p = li.GetCurrent();

	while (p != li.First()) {
		result += p->getSalary();
		p = li.Next();
	}
	return result;
}

double avg(CircularList& l) {
	double sum = 0;
	double amount = 0;

	ListIterator li(l);
	Employee* p = li.GetCurrent();
	
	while (p != li.First()) {
		sum += p->getSalary();
		amount += 1;
		p = li.Next();
	}

	return sum / amount;
}

int max(CircularList& l) {
	int result = numeric_limits<int>::min();

	ListIterator li(l);
	Employee* p = li.GetCurrent();

	while (p != li.First()) {
		if (result < p->getSalary()) result = p->getSalary();
		p = li.Next();
	}

	return result;
}

int min(CircularList& l) {
	int result = numeric_limits<int>::max();

	ListIterator li(l);
	Employee* p = li.GetCurrent();

	while (p != li.First()) {
		if (result > p->getSalary()) result = p->getSalary();
		p = li.Next();
	}

	return result;
}

//int printAll(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
//int sumProductFifthElement(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularList la, lb, lc;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(data);
			break;
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "���� �Ϸ�";
			else cout << "���� ����";
			break;
		case Show: //operator<< ������� ���
			cout << "����Ʈ la = \n";
			cout << la << endl;
			cout << "����Ʈ lb = \n";
			cout << lb << endl;
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�.";
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
			lc.Show();
			break;

		case SUM:  
			cout << "sum() = " << sum(la) << endl; 
			break;
		case AVG:  
			cout << "avg() = " << avg(la) << endl; 
			break;
		case MIN:  
			cout << "min() = " << min(la) << endl; 
			break;
		case MAX:  
			cout << "max() = " << max(la) << endl;
			break;
		case Exit: // ���� ��� ����
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	return 0;
}
