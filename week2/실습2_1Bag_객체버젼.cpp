#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

//예외 처리
class EmptyException : public std::exception {
public:
	EmptyException() {};

	const char* what() const noexcept override {
		return "Empty Bag";
	}
};

class OverflowException : public std::exception {
public:
	OverflowException() {};

	const char* what() const noexcept override {
		return "Overflow Bag";
	}
};

//Bag 클래스 정의
template <class T>
class Bag {
private:
    T* array;
    int capacity;
    int top;
public:
	Bag(int bagCapacity = 10);
	~Bag();
	bool IsFull();
	int Size() const; 
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
	friend ostream& operator<< <T>(ostream&, Bag<T>&);
};

template <class T> 
ostream& operator<<(ostream& os, Bag<T>& b) {
	os << "Bag contains: \n";
	for (int i = 0; i <= b.top; ++i) {
		os << b.array[i]; 
		if (i != b.top) {
			os << "\n";
		}
	}
	os << endl;
	return os;
}

template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity), top(-1) {
	array = new T[capacity];
}

template <class T>
Bag<T>::~Bag() {
	delete[] array;
}

template <class T>
bool Bag<T>::IsFull() {
	return (top == capacity - 1);
}

template <class T>
int Bag<T>::Size() const {
	return top;
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return top == -1;
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";
	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	memcpy(temp, a, sizeof(T) * number);
	delete[] a;
	a = temp;

}

template <class T>
void Bag<T>::Push(const T& x)
{
	if (IsFull()) throw OverflowException();
	array[++top] = x;
}

template <class T>
T& Bag<T>::Pop() {
	if (IsEmpty()) throw EmptyException();
	return array[top--];
}


class Employee {
	string eno;
	string ename;
	int age;
public:
	Employee() : eno(""), ename(""), age(0) {}
	Employee(string eno, string ename, int age) : eno(eno), ename(ename), age(age) {}
	friend ostream& operator<<(ostream& os, const Employee& emp) {
		os << "Employee[ID: " << emp.eno << ", Name: " << emp.ename << ", Age: " << emp.age << "]";
		return os;
	}
};

int main() {
	Bag<Employee> b(5);
	int n;
	Employee emp[5] = { Employee("E001", "John", 30),
			    Employee("E002", "Hong", 32),
			    Employee("E003", "Jung", 22),
			    Employee("E004", "Seok", 99),
			    Employee("E005", "Wang", 123)
	};
	try {
		b.Push(emp[0]);
		b.Push(emp[1]);
		b.Push(emp[2]);
		b.Push(emp[3]);
		b.Push(emp[4]);

		if (b.IsFull()) {
			cout << "Bag is full" << endl;
		}
		else {
			cout << "Bag is not full" << endl;
		}
		cout << endl << b << endl;
		while (!b.IsEmpty()) {
			Employee emp = b.Pop();
			cout << "b.Pop() = " << emp << endl;
		}
	}
	catch (string s) {
		cout << "예외발생" << s;
	}
	return 0;
}
