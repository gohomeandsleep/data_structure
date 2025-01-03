#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) : data(element), link(nullptr) {}
};

class LinkedList {
	Node* first;
public:
	LinkedList() {
		first = nullptr;
	}
	bool Delete(int);
	void Show();
	void Add(int element);
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};

void LinkedList::Add(int element) {
	Node* newNode = new Node(element);
	Node* p = first;
	Node* q = nullptr;

	if (p == nullptr) {
		first = newNode;
		return;
	}

	while (p != nullptr) {
		if (element < p->data) {
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
		cout << p->data << " ";
		p = p->link;
	}
}

bool LinkedList::Search(int data) {
	Node* p = first;

	while (p != nullptr) {
		if (data == p->data) {
			return true;
		}
		p = p->link;
	}
	return false;
}

bool LinkedList::Delete(int element) {
	if (first == nullptr) return false;
	Node* p = first;
	Node* q = nullptr;
	while (p != nullptr) {
		if (element == p->data) {
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
	Node* a = first;
	Node* b = other.first;

	while (a != nullptr && b != nullptr) {
		if (a->data >= b->data) {
			lc->Add(b->data);
			b = b->link;
		}
		else {
			lc->Add(a->data);
			a = a->link;
		}
	}

	while (a != nullptr) {
		lc->Add(a->data);
		a = a->link;
	}

	while (b != nullptr) {
		lc->Add(b->data);
		b = b->link;
	}
	
	return *lc;
}

enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};

void main() {
	Enum menu; // 메뉴
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0 : ADD0 | 1 : Add1 | 2 : Delete | 3 : Show | 4 : Search | 5 : Merge | 6 : Exit \n선택 : ";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << endl;
			cout << "리스트 lb = ";
			lb.Show();
			cout << endl;
			break;
		case Search:
			int n; 
			cin >> n;
			result = la.Search(n) || lb.Search(n);
			if (!result)
				cout << "검색 값 = " << n << " 데이터가 없습니다.\n";
			else
				cout << "검색 값 = " << n << " 데이터가 존재합니다.\n";
			break;
		case Delete:
			cout << "List0에서 삭제할 값 : ";
			cin >> data;
			result = la.Delete(data);
			if (result) cout << "삭제 완료\n";
			else cout << "Value isn't exist.\n";
			break;

		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			cout << endl;
			break;

		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
}

