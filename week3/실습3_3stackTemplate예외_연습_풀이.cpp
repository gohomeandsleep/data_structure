#include <iostream>
#include <memory>
#include <exception>  

using namespace std;

class EmptyStackException : public std::exception {
public:
	EmptyStackException() {}

	const char* what() const noexcept override {
		return " �� Stack.";
	}
};

class OverflowStackException : public std::exception {
public:
	OverflowStackException() {}
	
	const char* what() const noexcept override {
		return "full Stack.";
	}
	
};

template <class T>
class Stack {
public:
	Stack(int stackCapacity = 5);
	bool IsFull() const;
	bool IsEmpty() const;
	T& Peek() const;
	void Dump();
	void Push(const T& item);
	T& Pop();
private:
	T* stack;
	int top;
	int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity), top(-1) {
	stack = new T[capacity];
}

template <class T>
void Stack<T>::Dump() {
	if (IsEmpty()) {
		throw EmptyStackException();
	}
	for (int i = 0; i <= top; i++) {
		cout << stack[i] << " ";
	}
	cout << endl;
}

template <class T>
bool Stack<T>::IsFull() const {
	return top == capacity - 1;
}

template <class T>
bool Stack<T>::IsEmpty() const {
	return top == -1;
}

template <class T>
T& Stack<T>::Peek() const {
	if (IsEmpty()){ 
		throw EmptyStackException();
	}
	return stack[top];
}

template <class T>
void Stack<T>::Push(const T& item) {
	if (IsFull()) {
		throw OverflowStackException();
	}
	stack[++top] = item;
}

template <class T>
T& Stack<T>::Pop() {
	if (IsEmpty()) {
		throw EmptyStackException();
	}
	return stack[top--];
}

enum Menu { push, pop, peek, dump, Exit };

Menu SelectMenu() {
	int choice;
	cout << "0: Push " << "1: Pop, " << "2: Peek, " << "3: Dump, " << "4: Exit\n";
	cout << "���ù�ȣ: ";
	cin >> choice;
	return static_cast<Menu>(choice);
}

int main() {
	Stack<int> stack(5);
	Menu menu;

	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			case push: {
				int value;
				cout << "push ��: ";
				cin >> value;
				stack.Push(value);
				break;
			}
			case pop: {
				cout << "pop �� = " << stack.Pop() << endl;
				break;
			}
			case peek: {
				cout << "Peek of stack: " << stack.Peek() << endl;
				break;
			}
			case dump: {
				stack.Dump();
				break;
			}
			case Exit: {
				cout << "Exiting program.\n";
				return 0;
			}
			default: {
				cout << "Invalid choice. Try again.\n";
				break;
			}
			}
		}
		catch (const EmptyStackException& e) {
			cout << "���� empty ���� : " << e.what() << endl;
		}
		catch (const OverflowStackException& e) {
			cout << "���� overflow ����: " << e.what() << endl;
		}
		catch (...) {
			cout << "An unknown exception occurred." << endl;
		}
	}


	return 0;
}