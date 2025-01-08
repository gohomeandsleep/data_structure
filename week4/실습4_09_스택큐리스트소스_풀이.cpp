/*
* 9단계: Linked List를 사용한 스택과 큐의 구현
* template 버전으로 구현 
*/

//Stack node & Queue Node
#include <stdio.h>
#include <iostream>
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
ostream& operator<<(ostream& os, Employee& emp) {
	os << "Eno : " << emp.eno << " Ename : " << emp.ename;
	return os;
}
bool Employee::operator==(Employee& emp) {
	return this->eno == emp.eno;
}
bool Employee::operator<(Employee& emp) {
	return this->eno < emp.eno;
}
template <class T> class Stack; //forward declaration
template <class T> class Queue;

template <class T>
class StackNode {
	friend class Stack<T>;
private:
	T* data;
	StackNode<T>* link;
public:
	StackNode<T>(T* d = 0) : data(d) { link = 0; }//constructor
	StackNode(T* t, StackNode* top) : data(t), link(top) {};
	friend ostream& operator<<(ostream& os, StackNode& s);
};

template <class T>
ostream& operator<<(ostream& os, const StackNode<T>& s) {
	if (s.data) {
		os << *(s.data);
	}
	else {
		os << "null";
	}
	return os;
}

template <class T>
class Stack {
public:
	Stack<T>() { top = 0; }//constructor
	void Add(T*);
	T* Delete();
	void Show();
private:
	StackNode<T>* top;
	void StackEmpty();
};

template <class T>
void Stack<T>::Add(T* y) {
	StackNode<T>* newNode = new StackNode<T>(y, top);
	top = newNode;
}

template <class T>
void Stack<T>::StackEmpty() {
	if (Stack::top == 0) {
		cout << "Stack is Empty." << endl;
	}
	else {
		cout << "Stack is not Empty." << endl;
	}
}
template <class T>
void Stack<T>::Show() {
	if (!top) {
		cout << "Stack is empty." << endl;
		return;
	}
	StackNode<T>* current = top;
	while (current) {
		cout << *(current->data) << endl;
		current = current->link;
	}
}

template <class T>
T* Stack<T>::Delete()
//delete the top node from stack and return a pointer to its data
{
	if (!top) {
		cout << "Stack is empty." << endl;
		return nullptr;
	}
	StackNode<T>* tmp = top;
	T* data = tmp->data;
	top = top->link;
	delete tmp;
	return data;
}

template <class T>
class QueueNode {
	friend class Queue<T>;
private:
	T* data;
	QueueNode<T>* link;
public:
	QueueNode<T>(T* d = 0) : data(d) { link = 0; }//constructor
	friend ostream& operator<<(ostream& os, QueueNode& node);
};

template <class T>
ostream& operator<<(ostream& os, QueueNode<T>& node) {
	if (node.data) {
		os << *(node.data);
	}
	else {
		os << "null";
	}
	return os;
}

template <class T>
class Queue {
public:
	Queue<T>() { front = rear = nullptr; }//constructor
	void Add(T*);
	T* Delete();
	void ShowQueue();
private:
	QueueNode<T>* front;
	QueueNode<T>* rear;
	void QueueEmpty();
};


template <class T>
void Queue<T>::Add(T* y) {
	QueueNode<T>* newNode = new QueueNode<T>(y);
	if (!rear) {
		front = rear = newNode;
	}
	else {
		rear->link = newNode;
		rear = newNode;
	}
}

template <class T>
T* Queue<T>::Delete()
//delete the first node in queue and return a pointer to its data
{
	if (!front) {
		cout << "Queue is empty." << endl;
		return nullptr;
	}
	QueueNode<T>* tmp = front;
	T* data = tmp->data;
	front = front->link;

	if (!front) rear = nullptr;
	delete tmp;
	return data;
}

template <class T>
void Queue<T>::QueueEmpty() {
	if (front == 0)
		cout << "Queue is empty" << endl;
	else
		cout << "Queue is non empty" << endl;
}
template <class T>
void Queue<T>::ShowQueue() {
	if (!front) {
		cout << "Queue is empty." << endl;
		return;
	}
	QueueNode<T>* current = front;
	while (current) {
		cout << *(current->data) << endl;
		current = current->link;
	}
	cout << endl;
}

enum Enum {
	PushStack, PopStack, ShowStack, AddQueue, DeleteQueue, ShowQueue, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	Stack<Employee> st;
	Queue<Employee> qu;
	Employee* data;
	do {
		cout << "0.PushSTack, 1.PopStack, 2.ShowStack, 3.AddQueue, 4.DeleteQueue, 5.ShowQueue, 6.Exit:: ";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case PushStack:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			st.Add(data);
			break;
		case PopStack:
			data = st.Delete();
			if (data) cout << *data << endl;
			break;
		case ShowStack:
			st.Show();
			break;
		case AddQueue:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			qu.Add(data);
			break;
		case DeleteQueue:
			data = qu.Delete();
			if (data) cout << *data << endl;
			break;
		case ShowQueue:
			qu.ShowQueue();
			break;

		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);

	return 0;
}

