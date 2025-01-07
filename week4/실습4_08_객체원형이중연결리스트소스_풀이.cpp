/*
* doubly linked list
* 8단계- 원형 객체 이중 연결 리스트의 available list, getNode, retNode
* head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
* CircularDoublyList를 대상으로 한 iterator를 구현한다.
* template 버전으로 구현
*/
#include <iostream>
#include <time.h>
using namespace std;
template<class T> class DoublyListNode;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
class Employee {
	template<class T> friend class DoublyListNode;
	template<class T> friend class CircularDoublyList;
	template<class T> friend class CircularDoublyListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator>(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "Eno : " << emp.eno << " | Ename : " << emp.ename << " | Salary : " << emp.salary;
	return os;
}
bool Employee::operator==(Employee& emp) {
	return this->eno == emp.eno;
}
bool Employee::operator<(Employee& emp) {
	return this->eno < emp.eno;
}
bool Employee::operator>(Employee& emp) {
	return this->eno > emp.eno;
}
char Employee::compare(const Employee* emp) const {
	if (this->eno == emp->eno) return 0;
	else if (this->eno > emp->eno) return 1;
	else return -1;
}

template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
template<class T>
class DoublyListNode {
	friend class CircularDoublyList<T>;
	friend class CircularDoublyListIterator<T>;
public:
	DoublyListNode(T* p) { data = *p; llink = rlink = this; }
	DoublyListNode() { llink = rlink = this; }
private:
	T data;
	DoublyListNode<T>* llink, * rlink;
};

template<class T>
class CircularDoublyList {
	friend class CircularDoublyListIterator<T>;
public:
	CircularDoublyList() { last = new DoublyListNode<T>; }
	template<class T>
	friend ostream& operator<<(ostream&, CircularDoublyList<T>&);
	bool Delete(string);
	void Show();
	void Add(T*);//sno로 정렬되도록 구현
	bool Search(string);
	DoublyListNode<T>* GetNode();
	void RetNode(DoublyListNode<T>*);
	void Erase();
	CircularDoublyList<T>& operator+(CircularDoublyList<T>&);
private:
	DoublyListNode<T>* last;
	static DoublyListNode<T>* av;
};

template<class T>
DoublyListNode<T>* CircularDoublyList<T>::GetNode() {
	if (av != nullptr) {
		DoublyListNode<T>* node = av;
		av = av->rlink;
		return node;
	}
	return new DoublyListNode<T>;
}

template<class T>
void CircularDoublyList<T>::RetNode(DoublyListNode<T>* x) {
	x->rlink = av;
	av = x;
}

template<class T>
void CircularDoublyList<T>::Show() {
	if (this->last == nullptr) return;
	DoublyListNode<T>* current = last->rlink;
	do {
		cout << current->data << endl;
		current = current->rlink;
	} while (current != last);
}

template<class T>
void CircularDoublyList<T>::Add(T* element)
{
	DoublyListNode<T>* newNode = GetNode();
	newNode->data = *element;

	if (last->rlink == last) {
		newNode->rlink = last;
		last->llink = newNode;
		newNode->llink = last;
		last->rlink = newNode;
		return;
	}
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first;

	do {
		if (newNode->data < p->data) {
			newNode->rlink = p;
			newNode->llink = p->llink;
			p->llink->rlink = newNode;
			p->llink = newNode;

			if (p == first) {
				last->rlink = newNode;
			}
			return;
		}
		p = p->rlink;
	} while (p != last->rlink);

	last->llink->rlink = newNode;
	newNode->llink = last->llink;
	newNode->rlink = last;
	last->llink = newNode;
}

template<class T>
bool CircularDoublyList<T>::Search(string eno) {
	DoublyListNode<T>* first = last;
	DoublyListNode<T>* p = first->rlink;

	while (p != first) {
		if (p->data.eno == eno) {
			return true;
		}
		p = p->rlink;
	}
	return false;

}

template<class T>
bool CircularDoublyList<T>::Delete(string eno)
{
	DoublyListNode<T>* first = last;
	DoublyListNode<T>* p = first->rlink;

	if (last == nullptr) return false;

	while (p != last) {
		if (p->data.eno == eno) {
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;

			if (p == last) {
				last = p->llink;
			}

			if (p == first) {
				last->rlink = p->rlink;
			}

			RetNode(p);
			return true;
		}
		p = p->rlink;
	}
	return false;
}

template<class T>
void CircularDoublyList<T>::Erase() {
	if (last == nullptr) return;

	DoublyListNode<T>* current = last->rlink;
	DoublyListNode<T>* temp;

	do {
		temp = current;
		current = current->rlink;
		RetNode(temp);
	} while (current != last);

	last->rlink = last;
	last->llink = last;
}

//template<class T>
//ostream& operator<<(ostream& os, CircularDoublyList<T>& l)
//{
//
//}

template<class T>
class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l) {
		current = list.last->rlink;
	}
	~CircularDoublyListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T* GetCurrent();
private:
	const CircularDoublyList<T>& list;
	DoublyListNode<T>* current;
};

template<class T>
bool CircularDoublyListIterator<T>::NotNull() {
	return current != nullptr;
}
template<class T>
bool CircularDoublyListIterator<T>::NextNotNull() {
	return (current != nullptr && current->rlink != nullptr);
}
template<class T>
T* CircularDoublyListIterator<T>::First() {
	return&list.last->rlink->data;
}
template<class T>
T* CircularDoublyListIterator<T>::Next() {
	current = current->rlink;
	T* e = &current->data;
	return e;
}
template<class T>
T* CircularDoublyListIterator<T>::GetCurrent() {
	return &current->data;
}
template<class T>
CircularDoublyListIterator<T>::~CircularDoublyListIterator() {}

template<class T>
CircularDoublyList<T>& CircularDoublyList<T>::operator+(CircularDoublyList<T>& lb) {
	T* p, * q;
	CircularDoublyListIterator<T> Aiter(*this);
	CircularDoublyListIterator<T> Biter(lb);
	CircularDoublyList<T>* lc = new CircularDoublyList<T>();
	p = Aiter.First();
	q = Biter.First();

	while ((p != &this->last->data) && (q != &lb.last->data)) {
		if (*p < *q) {
			lc->Add(p);
			p = Aiter.Next();
		}
		else {
			lc->Add(q);
			q = Biter.Next();
		}
	}
	while (p != &this->last->data) {
		lc->Add(p);
		p = Aiter.Next();
	}

	while (q != &lb.last->data) {
		lc->Add(q);
		q = Biter.Next();
	}
	return *lc;
}

//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습

template<class T>
int sum(const CircularDoublyList<T>& l) {
	int result = 0;

	CircularDoublyListIterator<T> li(l);
	T* p = li.First();

	do {
		result += p->getSalary();
		p = li.Next();
	} while (p != li.First());

	return result;
}
template<class T>
double avg(const CircularDoublyList<T>& l) {
	double sum = 0;
	double count = 0;

	CircularDoublyListIterator<T> li(l);
	T* p = li.First();

	do {
		if (p->getSalary() != 0) {
			sum += p->getSalary();
			count += 1;
		}
		p = li.Next();
	} while (p != li.First());

	return sum / count;
}
template<class T>
int min(const CircularDoublyList<T>& l) {
	CircularDoublyListIterator<T> li(l);
	T* p = li.First();

	int min = numeric_limits<int>::max();

	do {
		if (min > p->getSalary() && p->getSalary() != 0) {
			min = p->getSalary();
		}
		p = li.Next();
	} while (p != li.First());
	return min;
}
template<class T>
int max(const CircularDoublyList<T>& l) {
	CircularDoublyListIterator<T> li(l);
	T* p = li.First();

	int max = numeric_limits<int>::min();

	do {
		if (max < p->getSalary() && p->getSalary() != 0) {
			max = p->getSalary();
		}
		p = li.Next();
	} while (p != li.First());
	return max;
}

template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularDoublyList<Employee> la, lb, lc;
	Employee* s;
	do {
		cout << "\n0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
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
			cout << *data;
			la.Add(data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			cout << *data;
			lb.Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "eno = " << eno << " 삭제 완료.";
			break;
		case Show:
			cout << "리스트 la = \n";
			la.Show();
			cout << "리스트 lb = \n";
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
			cout << "리스트 lc = \n";
			lc.Show();
			cout << "리스트 la를 삭제" << endl;
			la.Erase();
			cout << "리스트 lb를 삭제" << endl;
			lb.Erase();
			cout << "리스트 la = ";
			la.Show();
			cout << endl << "리스트 lb = ";
			lb.Show();
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
