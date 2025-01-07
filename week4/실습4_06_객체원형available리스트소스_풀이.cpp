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
	Employee(string sno, string sname, int salary) : eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const;
};

ostream& operator<<(ostream& os, Employee& emp) {
	os << "Employee No : " << emp.eno << " | Name : " << emp.ename << " | Salary : " << emp.salary;
	return os;
}

bool Employee::operator==(Employee& emp) {
	return this->eno == emp.eno;
}

bool Employee::operator<(Employee& emp) {
	return this->eno < emp.eno;
}

char Employee::compare(const Employee* emp) const {
	if (this->eno == emp->eno) return 0;
	else if (this->eno > emp->eno) return 1;
	else return -1;
}

int Employee::getSalary() const {
	return salary;
}
 
class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() : data(), link(nullptr) {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* first;
	static Node* av;
public:
	CircularList() {
		first = new Node(); 
		first->link = first; 
	}
	bool Delete(string);
	void Show();
	void Add(Employee*);
	bool Search(string);
	Node* GetNode();
	void RetNode(Node*);
	void Erase();
	CircularList& operator+(CircularList&);
	//friend ostream& operator<<(ostream& os, CircularList& l);
};

//ostream& operator<<(ostream& os, CircularList& l) {
//
//}

Node* CircularList::GetNode() {
	if (av != nullptr) {
		Node* node = av;
		av = av->link;
		return node;
	}
	return new Node();
}

void CircularList::RetNode(Node* x) { // node 하나를 반납
	x->link = av;
	av = x;
}

void CircularList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first->link;

	while (p != first) {
		cout << p->data << endl;
		p = p->link;
	}
}

void CircularList::Add(Employee* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = GetNode();
	newNode->data = *element;
	Node* p = first->link;
	Node* q = first;

	if (first->link == first) { // 원형리스트에 아무런 값도 없을때
		first->link = newNode;
		newNode->link = first;
		return;
	}

	while (p != first) {
		if (newNode->data < p->data) { //q->newNode->p (newNode < p -> 탈출조건)
			newNode->link = p;
			q->link = newNode;

			if (p == first->link) { //원형리스트에 한 개의 값만 존재할때 first->newNode->p
				first->link = newNode;
			}
			return;
		}//p, q 한칸씩 이동
		q = p;
		p = p->link;
	}
	//마지막 노드까지 도달했을때 q->newNode->first
	q->link = newNode;
	newNode->link = first;
}

bool CircularList::Search(string eno) { // sno를 갖는 레코드를 찾기
	Node* p = first->link;

	while (p != first) {
		if (p->data.eno == eno) {
			return true;
		}
		p = p->link;
	}
	return false;
}

bool CircularList::Delete(string eno) // delete the element
{
	Node* p = first->link;
	Node* q = first;

	if (first->link == first) return false; //원형리스트 안에 아무것도 없는 상태

	while (p != first) {
		if (p->data.eno == eno) { //q-> plink
			q->link = p->link;

			if (p == first->link) { // first->p->plink 일때 first->plink
				first->link = p->link;
			}

			RetNode(p);
			return true;
		}
		//p, q 한칸씩 이동
		q = p;
		p = p->link;
	}
	return false;
}

void CircularList::Erase() {
	if (first->link == first) return;

	Node* current = first->link;
	Node* temp;

	while (current != first) {
		temp = current;
		current = current->link;
		RetNode(temp);
	}

	first->link = first;
}

class ListIterator {
public:
	ListIterator(const CircularList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++();
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current;
	const CircularList& list;
};

ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {}

bool ListIterator::NotNull() {
	return current != nullptr;
}

bool ListIterator::NextNotNull() {
	return current && current->link != nullptr;
}

Employee* ListIterator::First() {
	return &list.first->data;
}

Employee* ListIterator::Next() {
	current = current->link;
	Employee* e = &current->data;
	return e;
}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
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

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}

CircularList& CircularList::operator+(CircularList& lb) {
	ListIterator Aiter(*this), Biter(lb);
	CircularList* lc = new CircularList();

	Employee* p = Aiter.GetCurrent();
	Employee* q = Biter.GetCurrent();

	Employee* p_start = Aiter.First();
	Employee* q_start = Biter.First();

	while (p != p_start && q != q_start) {
		if (q->eno < p->eno) {
			lc->Add(q);
			q = Biter.Next();
		}
		else {
			lc->Add(p);
			p = Aiter.Next();
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

int sum(const CircularList& l)
{
	int result = 0;

	ListIterator li(l);
	Employee* p = li.GetCurrent();

	while (p != li.First()) {
		result += p->getSalary();
		p = li.Next();
	}
	return result;
}

double avg(const CircularList& l)
{
	double sum = 0;
	int divisor = 0;

	ListIterator li(l);
	Employee* p = li.GetCurrent();

	while (p != li.First()) {
		sum += p->getSalary();
		divisor += 1;
		p = li.Next();
	}
	return sum / divisor;
}

int min(const CircularList& l)
{
	ListIterator li(l);
	Employee* p = li.GetCurrent();

	int min = numeric_limits<int>::max();

	while (p != li.First()) {
		if (min > p->getSalary()) {
			min = p->getSalary();
		}
		p = li.Next();
	}
	return min;

}

int max(const CircularList& l)
{
	ListIterator li(l);
	Employee* p = li.GetCurrent();

	int max = numeric_limits<int>::min();

	while (p != li.First()) {
		if (max < p->getSalary()) {
			max = p->getSalary();
		}
		p = li.Next();
	}
	return max;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

Node* CircularList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularList la, lb, lc;
	Employee* s;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
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
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
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
			cout << "리스트 lc = ";
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
