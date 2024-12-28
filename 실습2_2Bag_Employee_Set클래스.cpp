#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

class EmptyBagException : public std::exception {
public:
	EmptyBagException() {};

	const char* what() const noexcept override {
		return "Empty Bag";
	}
};

class OverflowBagException : public std::exception {
public:
	OverflowBagException() {};

	const char* what() const noexcept override {
		return "Full Bag";
	}
};

class Employee {
	string eno;
	string ename;
	int age;
public:
	Employee() : eno(""), ename(""), age(0) {};
	Employee(string eno, string ename, int age) : eno(eno), ename(ename), age(age) {};
	string getEno() const { return eno; }
	string getEname() const { return ename; }
	int getAge() const { return age; }

	friend ostream& operator<<(ostream& os, const Employee& emp) {
		os << "Employee[ID: " << emp.eno << ", Name: " << emp.ename << ", Age: " << emp.age << "]";
		return os;
	}

	bool operator==(const Employee& emp) const {
		return eno == emp.eno;
	}
};

template <class T>
class Bag {
private:
	T* array;
	int capacity;
	int top;
public:
	Bag(int bagCapacity = 10) : capacity(bagCapacity), top(-1) {
		array = new T[capacity];
	}
	bool IsFull();
	bool IsEmpty() const;
	int Size() const;
	virtual T& Pop();
	virtual void Push(const T&);
	friend ostream& operator << (ostream& os, Bag<T>& b) {
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
protected:
	int getTop() const { return top; }
	T* getArray() const { return array; }
	void setTop(int t) { top = t; }
};

template <class T>
bool Bag<T>::IsFull() {
	return top == (capacity - 1);
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return top == -1;
}

template <class T>
int Bag<T>::Size() const {
	return top + 1;
}

template <class T>
void Bag<T>::Push(const T& d) {
	if (IsFull()) throw OverflowBagException();
	array[++top] = d;
}

template <class T>
T& Bag<T>::Pop() {
	if (IsEmpty()) throw EmptyBagException();
	return array[top--];
}

template <class T>
class Set : public Bag<T> {
public:
	Set(int setCapacity = 10) : Bag<T>(setCapacity) {};
	~Set() {};
	void Push(const T& d);
};

template <class T>
void Set<T>::Push(const T& d) {
	for (int i = 0; i <= this->getTop(); ++i) {
		if (this->getArray()[i] == d) {
			return;
		}
	}

	if (this->IsFull()) throw OverflowBagException();
	this->getArray()[this->getTop() + 1] = d;
	this->setTop(this->getTop() + 1);
}


int main() {
	Set<Employee> b(5);
	Employee emp[5] = { Employee("E001", "John", 30),
						Employee("E002", "Jane", 25),
						Employee("E003", "Mike", 28),
						Employee("E004", "Anna", 35),
						Employee("E005", "Tom", 40)
	};
	try {
		b.Push(emp[0]);
		b.Push(emp[1]);
		b.Push(emp[2]);
		b.Push(emp[3]);
		b.Push(emp[4]);
		if (b.IsFull()) {
			cout << "full" << endl;
		}
		else {
			cout << "not full" << endl;
		}
		cout << endl << b << endl;;
		while (!b.IsEmpty()) {
			Employee emp = b.Pop();
			cout << "b.Pop() = " << emp << endl;
		}
	}
	catch (string s) {
		cout << "예외발생" << s;
	}
	system("pause");
	return 0;
}
