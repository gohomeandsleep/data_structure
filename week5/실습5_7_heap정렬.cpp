//소스코드 5.4: Heap
// 5.6 heap 
#include <iostream>
//MinPQ를 구현
using namespace std;

const int HeapSize = 1000;
enum Boolean { FALSE, TRUE };

template <class Type>
class Element {
public:
	Type key;
	Element() {}
	Element(Type key) :key(key) {}
};

template <class Type>
class MaxPQ {
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMax(Element<Type>&) = 0;
};

template <class Type>
class MaxHeap : public MaxPQ<Type> {
public:
	MaxHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new Element<Type>[MaxSize + 1]; // Don't want to use heap[0]
	};
	void display();
	void Insert(const Element<Type>& x);
	Element<Type>* DeleteMax(Element<Type>&);
private:
	Element<Type>* heap;
	int n; // current size of MaxHeap
	int MaxSize; // Maximum allowable size of MaxHeap
	void HeapEmpty() { cout << "Heap Empty" << "\n"; };
	void HeapFull() { cout << "Heap Full"; };
};

template <class Type>
void MaxHeap<Type>::display() //level order로 출력
{

}

template <class Type>
void MaxHeap<Type>::Insert(const Element<Type>& x)
{

}

template <class Type>
Element<Type>* MaxHeap<Type>::DeleteMax(Element<Type>& x)
{

}
void heapSort(MaxHeap<int> hp) {
	//heap를 사용하여 정렬 결과를 출력
}
int main() {
	int select = 0;
	int data = 0;

	MaxHeap<int> heap(20);
	Element<int> ele;

	Element<int>* deletedEle = nullptr;

	do {
		cout << endl << "Max Tree. Select: 1 insert, 2 display, 3 delete,  4 sort, 5 exit" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "input value: ";
			//난수를 생성하여 20개 입력하는 코드로 수정
			heap.Insert(Element<int>(data));
			heap.display();
			break;
		case 2:
			heap.display();
			break;
		case 3:
			deletedEle = heap.DeleteMax(ele);
			if (deletedEle != nullptr) {
				cout << "deleted element: " << deletedEle->key << endl;
			}
			cout << "current max heap: " << endl;
			heap.display();
			break;
		case 4:
			//heap를 사용한 정렬
			heapSort(heap);
		case 5:
			exit(1);
			break;

		}
	} while (select < 5);

	return 0;
}
