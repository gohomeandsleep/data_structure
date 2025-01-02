#pragma once
#include <iostream>
#include <memory>
#include <fstream>

using namespace std;
#define MaxSize 100
const int DefaultSize = 100;

//예외처리를 위한 클래스
class EmptyStackException : public std::exception {
public:
	EmptyStackException() {}
	const char* what() const noexcept override {
		return " 빈 Stack.";
	}
};

class OverflowStackException : public std::exception {
public:
	OverflowStackException() {}
	const char* what() const noexcept override {
		return "full Stack.";
	}
};

//bag 클래스
template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
	bool IsFull();
	int Size() const;
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
protected:
	T* array;
	int capacity;
	int top;
};

template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity) {
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() {
	delete[] array;
}

template <class T>
bool Bag<T>::IsFull() {
	return top == capacity - 1;
}

template <class T>
int Bag<T>::Size() const {
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return top == -1;
}

template <class T>
T& Bag<T>::Pop() {
	if (IsEmpty()) throw EmptyStackException();
	return array[top--];
}

template <class T>
void Bag<T>::Push(const T& x) {
	if (IsFull()) throw OverflowStackException();
	array[++top] = x;
}

//stack 클래스
template <class T>
class Stack : public Bag<T> {
public:
	Stack(int MaxStackSize = DefaultSize);
	T& Pop();
	void Push(const T&);
	T& Peek() const;
	void Dump();
};

template <class T>
Stack<T>::Stack(int MaxStackSize) : Bag<T>(MaxStackSize) {}

template <class T>
T& Stack<T>::Pop() {
	if (this->IsEmpty()) throw EmptyStackException();
	return this->array[this->top--];
}

template <class T>
void Stack<T>::Push(const T& x) {
	if (this->IsFull()) throw OverflowStackException();
	this->array[++this->top] = x;
}

template <class T>
T& Stack<T>::Peek() const {
	if (this->IsEmpty()) throw EmptyStackException();
	return this->array[this->top];
}

template <class T>
void Stack<T>::Dump() {
	if (this->IsEmpty()) throw EmptyStackException();
	for (int i = 0; i <= this->top; i++) {
		cout << this->array[i] << " ";
	}
	cout << endl;
}

struct items {
	int x, y, dir;
};


struct offsets {
	int a, b;
};

enum directions { N, NE, E, SE, S, SW, W, NW };
offsets moves[8];
int maze[100][100];
int mark[100][100];

// 메뉴 옵션을 위한 enum
enum MenuOption { INIT_MAZE = 1, FIND_PATH, SHOW_RESULT, EXIT };

// 미로 초기화
void initializeMaze() {
	int input[12][15] = {
		{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },
	};

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 17; j++) {
			if (i == 0 || i == 13 || j == 0 || j == 16) {
				maze[i][j] = 1;
				mark[i][j] = 1;
			}
			else {
				maze[i][j] = input[i - 1][j - 1];
				mark[i][j] = input[i - 1][j - 1];
			}
		}
	}
	cout << "Maze initialized.\n";
}

// 미로 출력
void showMatrix(int d[][100], int row, int col) {
	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < col + 2; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
}

// 미로 탐색
void findPath(int m, int p) {
	try {
		Stack<items> stack(m * p);
		items temp;
		int row, col, nextRow, nextCol, dir, found = false;
		mark[1][1] = 1;
		stack.Push({ 1, 1, E });

		while (!stack.IsEmpty() && !found) {
			//스택에서 위치 가져오기
			temp = stack.Pop();
			row = temp.x;
			col = temp.y;
			dir = temp.dir;

			while (dir < 8 && !found) {
				//다음 위치 계산
				nextRow = row + moves[dir].a;
				nextCol = col + moves[dir].b;

				if (nextRow == m && nextCol == p) {
					//검색 성공
					found = true;
					stack.Push({ row, col, dir });
					stack.Push({ nextRow, nextCol, 0 });
				}
				else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
					//다음 위치로 이동
					mark[nextRow][nextCol] = 1;
					temp.x = row;
					temp.y = col;
					temp.dir = ++dir;
					stack.Push(temp);
					row = nextRow;
					col = nextCol;
					dir = N;
				}
				else ++dir;
			}
		}

		if (found) {
			while (!stack.IsEmpty()) {
				temp = stack.Pop();
				mark[temp.x][temp.y] = 2;
			}
			cout << "The path is marked by 2\n";
		}
		else cout << "The maze does not have a path\n";
	}
	catch (const EmptyStackException& e) {
		cout << "스택 empty 예외 발생." << endl;
	}
	catch (const OverflowStackException& e) {
		cout << "스택 overflow 예외 발생." << endl;
	}
}

int main() {
	moves[N].a = -1; moves[N].b = 0;
	moves[NE].a = -1; moves[NE].b = 1;
	moves[E].a = 0; moves[E].b = 1;
	moves[SE].a = 1; moves[SE].b = 1;
	moves[S].a = 1; moves[S].b = 0;
	moves[SW].a = 1; moves[SW].b = -1;
	moves[W].a = 0; moves[W].b = -1;
	moves[NW].a = -1; moves[NW].b = -1;

	int choice;
	while (true) {
		cout << "1. Initialize Maze\n2. Find Path\n3. Show Result\n4. Exit\n";
		cout << "Choose an option: ";
		cin >> choice;

		switch (choice) {
		case INIT_MAZE:
			initializeMaze();
			showMatrix(maze, 12, 15);
			break;
		case FIND_PATH:
			findPath(12, 15);
			break;
		case SHOW_RESULT:
			showMatrix(mark, 12, 15);
			break;
		case EXIT:
			cout << "Exiting...\n";
			return 0;
		default:
			cout << "Invalid choice. Try again.\n";
		}
	}
	return 0;
}