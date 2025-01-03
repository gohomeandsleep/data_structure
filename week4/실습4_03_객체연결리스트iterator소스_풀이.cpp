#include <iostream>
#include <time.h>
#include <algorithm>
#include <limits>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
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
	char compare(const Employee*) const;
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

class Node {
	friend class ListIterator;
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
	friend class ListIterator;
	Node* first;
public:
	LinkedList() {first = nullptr;}
	bool Delete(string);
	void Show();
	void Add(Employee);
	bool Search(string);
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
		if (p->data.eno == s) return true;
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
				first->link = first;
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

class ListIterator {
public:
	ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {};
	~ListIterator() {};
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee* GetCurrent();
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++();
	ListIterator operator++(int);

private:
	Node* current; //pointer to nodes
	const LinkedList& list;//existing list
};

bool ListIterator::NotNull() {
	return current != nullptr;
}

bool ListIterator::NextNotNull() {
	return (current != nullptr && current->link != nullptr);
}

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

bool ListIterator::operator==(const ListIterator other) const {
	return this->current == other.current;
}

bool ListIterator::operator!=(const ListIterator other) const {
	return this->current != other.current;
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->() const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

LinkedList& LinkedList::operator+(LinkedList& other) {
	ListIterator Aiter(*this); 
	ListIterator Biter(other);
	LinkedList* lc = new LinkedList();
	Employee * p = Aiter.First();
	Employee * q = Biter.First();
	
	while (Aiter.NotNull() && Biter.NotNull()) {
		if (p < q) {
			lc->Add(*p);
			p = Aiter.Next();
		}
		else {
			lc->Add(*q);
			q = Biter.Next();
		}
	}

	while (Aiter.NotNull()) {
		lc->Add(*p);
		p = Aiter.Next();
	}

	while (Biter.NotNull()) {
		lc->Add(*q);
		q = Biter.Next();
	}
	return *lc;
}

int sum(LinkedList lst) {
	int result = 0;

	ListIterator li(lst);
	Employee* p = li.First();

	while (li.NotNull()) {
		result += p->getSalary();
		p = li.Next();
	}

	return result;
}

double avg(LinkedList lst) {
	double sum = 0;
	double divisor = 0;

	ListIterator li(lst);
	Employee* p = li.First();

	while (li.NotNull()) {
		sum += p->getSalary();
		divisor += 1;
		p = li.Next();
	}
	return sum / divisor;
}

int min(LinkedList lst) {
	int result = numeric_limits<int>::max();
	ListIterator li(lst);
	Employee* p = li.First();

	while (li.NotNull()) {
		if (result > p->getSalary()) {
			result = p->getSalary();
		}
		p = li.Next();
	}
	return result;
}

int max(LinkedList lst) {
	int result = numeric_limits<int>::min();
	ListIterator li(lst);
	Employee* p = li.First();

	while (li.NotNull()) {
		if (result < p->getSalary()) {
			result = p->getSalary();
		}
		p = li.Next();
	}
	return result;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu;
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	LinkedList la, lb, lc;
	do {
		cout <<"0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(*data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(*data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "삭제 완료";
			break;
		case Show:
			cout << "리스트 la " << endl;
			la.Show();
			cout << "리스트 lb " << endl;
			lb.Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다.";
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = " << endl;
			lc.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	return 0;
}

