#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

class EmptyQueueException : public std::exception {
public:
	EmptyQueueException() {};

	const char* what() const noexcept override {
		return "Queue is empty";
	}
};

class OverflowQueueException : public std::exception {
public:
	OverflowQueueException() {};

	const char* what() const noexcept override {
		return "Queue is full";
	}
};

template <class T>
class Queue
{
public:
	Queue(int queueCapacity = 10);
	T& Front();
	T& Peek() const;
	//T& Rear();
	void Push(T const& x);
	T& Pop();
	bool IsFull() const;
	bool IsEmpty() const;
	void Dump();
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};

template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity), front(-1), rear(-1) {
	queue = new T[capacity];
}

template <class T>
bool Queue<T>::IsEmpty() const {
	return rear == front;
}

template <class T>
bool Queue<T>::IsFull() const {
	return rear == capacity - 1;
}

template <class T>
void Queue<T>::Push(T const& item) {
	if (IsFull()) {
		throw OverflowQueueException();
	}

	queue[rear++] = item;
}

template <class T>
T& Queue<T>::Pop() {
	if (IsEmpty()) {
		throw EmptyQueueException();
	}

	return queue[front++];
}

template <class T>
T& Queue<T>::Front() {
	if (IsEmpty()) {
		throw EmptyQueueException();
	}

	return queue[front];
}

template <class T>
T& Queue<T>::Peek() const {
	if (IsEmpty()) {
		throw EmptyQueueException();
	}

	return queue[rear - 1];
}

template <class T>
void Queue<T>::Dump() {
	if (IsEmpty()) {
		throw EmptyQueueException();
	}

	for (int i = front; i < rear; i++) {
		cout << queue[i] << " ";
	}
	cout << endl;
}

// Menu 열거형 정의
enum Menu { push, pop, front, peek, dump, Exit };

// 메뉴를 선택하는 함수
Menu SelectMenu() {
	int choice;
	cin >> choice;
	return static_cast<Menu>(choice);
}

int main() {
	Queue<int> queue(5);  // 용량이 5인 정수 Queue 생성
	Menu menu;

	while (true) {
		try {
			cout << "0: Push, 1: Pop, 2: Front, 3: Peek, 4: Dump, 5: Exit\nchoice : ";
			menu = SelectMenu();
			switch (menu) {
			case (push): {
				int value;
				cout << "push 값: ";
				cin >> value;
				queue.Push(value);
				break;
			}
			case (pop): {
				cout << "pop 값 = " << queue.Pop() << endl;
				break;
			}
			case (front): {
				cout << "front 값 = " << queue.Front() << endl;
				break;
			}
			case (peek): {
				cout << "peek 값 = " << queue.Peek() << endl;
				break;
			}
			case (dump): {
				queue.Dump();
				break;
			}
			case (Exit): {
				cout << "Terminate...";
				return 0;
			}
			default: {
				cout << "Invalid Choice";
				break;
			}

			}

		}
		catch (const EmptyQueueException& e) {
			cout << "Queue empty 예외 : " << e.what() << endl;
		}
		catch (const OverflowQueueException& e) {
			cout << "Queue overflow 예외: " << e.what() << endl;
		}
		catch (...) {
			cout << "An unknown exception occurred." << endl;
		}
	}


	return 0;
}