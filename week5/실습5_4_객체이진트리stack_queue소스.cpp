﻿/*
* 4단계: 5장 객체 이진트리 non-recursive 버젼
*/

/*
1. preorder, postorder, copy, == (equal)를 test한다.
2. 두개의 binary tree를 만들어 equal 테스트한다.
3. NonrecInorder()를 구현한다
4. class InorderIterator를 구현한다.
5. class Queue를 사용하여 LevelOrder()를 구현한다.

expression = A + B * C –D를 TREE로 만드는 코딩

*/
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int DefaultSize = 20;
enum Boolean { FALSE, TRUE };
class Employee {
	friend class TreeNode;
	friend class Tree;
	string eno;
	string ename;
public:

};



template <class KeyType>
class Stack
{
public:
	Stack(int MaxStackSize = DefaultSize);

	Boolean IsFull();

	void Add(KeyType& item);

	Boolean IsEmpty();

	KeyType* Delete(KeyType&);

	void StackEmpty() { cout << "empty" << endl; };
	void StackFull() { cout << "full" << endl; };
	void Output();
private:
	int top;
	KeyType* stack;
	int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsFull()
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsEmpty()
{
	if (top == -1) return TRUE;
	else return FALSE;
}

template <class KeyType>
void Stack<KeyType>::Add(KeyType& x)
{
	if (IsFull()) StackFull();
	else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete(KeyType& x)
{
	if (IsEmpty()) { StackEmpty(); return 0; }
	x = stack[top--];
	return &x;
}

template <class KeyType>
void Stack<KeyType>::Output()
{
	cout << "top = " << top << endl;
	for (int i = 0; i < top; i++)
		cout << i << ":" << stack[i] << endl;
}


template <class KeyType>
class Queue
{
	// \fBobjects\fR: A finite ordered list with zero or more elements.
public:
	Queue(int MaxQueueSize = 15);
	// Create an empty queue whose maximum size is \fIMaxQueueSize\fR

	bool IsFull();
	// if number of elements in the queue is equal to the maximum size of
	//   the queue, return TRUE (1); otherwise, return FALSE (0)

	void Add(const KeyType& item);
	// if IsFull(), then QueueFull(); else insert item into the top of the queue.

	bool IsEmpty();
	// if number of elements in the queue is equal to 0, return TRUE (1) else return FALSE (0).

	KeyType* Delete(KeyType&);
	// if IsEmpty(), then QueueEmpty(); else remove and return the topmost element of the Queue

	void QueueEmpty() { cout << "empty" << endl; };
	void QueueFull() { cout << "full" << endl; };
	void Output();
private:
	int front;
	int rear;
	KeyType* queue;
	int MaxSize;
};

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize)
{
	queue = new KeyType[MaxSize];
	front = rear = -1;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsFull()
{
	if (rear == MaxSize - 1) return true;
	else return false;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsEmpty()
{
	if (front == rear) return true;
	else return false;
}

template <class KeyType>
void Queue<KeyType>::Add(const KeyType& x)
// add x to the queue
{
	if (IsFull()) QueueFull();
	else queue[++rear] = x;
}

template <class KeyType>
KeyType* Queue<KeyType>::Delete(KeyType& x)
// remove and return front element from queue
{
	Output();
	if (IsEmpty()) { QueueEmpty(); return 0; }
	x = queue[++front];
	return &x;
}

template <class KeyType>
void Queue<KeyType>::Output()
{
	cout << "front = " << front << "rear = " << rear << endl;
	for (int i = front + 1; i <= rear; i++)
		cout << i << ":" << queue[i] << endl;
}

//make a binary tree 
/*
1. preorder, postorder, copy, == (equal)를 test한다.
2. 두개의 binary tree를 만들어 equal 테스트한다.
3. NonrecInorder()를 구현한다
4. class InorderIterator를 구현한다.
5. class Queue를 사용하여 LevelOrder()를 구현한다.

   expression = A + B * C –D를 TREE로 만드는 코딩
6. template version으로 만드는 것
7. inorder iterator 처럼 level order로 binary tree를 traverse하는 LevelIterator를 구현
8. PostorderIterator 구현
9. count # of of leaf nodes
10. SwapTree(): swap left and right child of every node
*/

//inorder(), postorder(), preorder() -> NonrecInorder() -> class InorderIterator -> Next() -> LevelOrder() -> NoStackInorder() -> Copy() -> equal()

class Tree;

class TreeNode {
	friend class Tree;
	friend class InorderIterator;
	template <class KeyType> friend class Stack;
	template <class KeyType> friend class Queue;
	friend int equal(TreeNode*, TreeNode*);
private:
	TreeNode* LeftChild;
	Employee data;
	TreeNode* RightChild;
public:

};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
private:
	TreeNode* root;
	void inorder(TreeNode*);
	void preorder(TreeNode*);
	void postorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() { root = 0; };
	bool insert(Employee ex);
	bool remove(Employee ex);
	bool search(Employee ex);
	void inorder();
	void preorder();
	void postorder();
	void NoStackInorder();
	void NonrecInorder();
	void LevelOrder();
	bool isLeafNode(TreeNode* current);
	Tree* Copy(); //void Copy(Tree&);
	TreeNode* InorderSucc(TreeNode*);
};
TreeNode* Tree::InorderSucc(TreeNode* current)
{
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}

class InorderIterator {
public:
	Employee* Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root;
	};

private:
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};


Employee* InorderIterator::Next()
{
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		Employee temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild;
		return &temp;
	}
	else return 0;
}

void Tree::inorder()
{
	inorder(root);
}

void Tree::preorder()
{
	preorder(root);
}

void Tree::postorder()
{
	postorder(root);
}

void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}

Tree::Tree(const Tree& s)//copy constructor
{
	root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode* orignode)
{

}
// Driver
int operator==(const Tree& s, const Tree& t)
{
	return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode* a, TreeNode* b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{

}
bool Tree::isLeafNode(TreeNode* current) {

}
bool Tree::insert(Employee ex) {// binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을
							// 설계하여 구현

}

void Tree::NonrecInorder()//void Tree::inorder(TreeNode *CurrentNode)와 비교
{
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;

	while (1) {
		cout << "while::" << CurrentNode->data << endl;
		while (CurrentNode) {
			cout << "s.Add()하기전::" << CurrentNode->data << endl;
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!s.IsEmpty()) {
			//s.Output();
			CurrentNode = *s.Delete(CurrentNode);
			cout << "delete 한후::" << CurrentNode->data << endl;
			CurrentNode = CurrentNode->RightChild;
		}
		else break;
	}
}
void Tree::LevelOrder()
{

}
void Tree::NoStackInorder() //inorder()와 비교
{
	if (!root) return;
	TreeNode* top = 0, * LastRight = 0, * p, * q, * r, * r1;//local variable이 key point
	p = q = root;
	while (1) {
		while (1) {
			if ((!p->LeftChild) && (!p->RightChild)) {
				cout << p->data; break;
			}
			if (!p->LeftChild) {
				cout << p->data;
				r = p->RightChild; p->RightChild = q;
				q = p; p = r;
			}
			else {
				r = p->LeftChild; p->LeftChild = q;
				q = p; p = r;
			}
		}
		TreeNode* av = p;
		while (1) {
			if (p == root) return;
			if (!q->LeftChild) {
				r = q->RightChild; q->RightChild = p;
				p = q; q = r;
			}
			else if (!q->RightChild) {
				r = q->LeftChild; q->LeftChild = p;
				p = q; q = r; cout << p->data;
			}
			else
				if (q == LastRight) {
					r = top; LastRight = r->LeftChild;
					top = r->RightChild;
					r->LeftChild = r->RightChild = 0;
					r = q->RightChild; q->RightChild = p;
					p = q; q = r;
				}
				else {
					cout << q->data;
					av->LeftChild = LastRight; av->RightChild = top;
					top = av; LastRight = q;
					r = q->LeftChild; q->LeftChild = p;
					r1 = q->RightChild; q->RightChild = r;
					p = r1;
					break;
				}
		}
	}
}
bool Tree::remove(Employee ex) {


}

bool Tree::search(Employee ex) {

}
enum Enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, LevelOrder, NonrecInorder, NoStackInorder, Quit };
int main() {
	Tree t;
	bool eq = -1;
	int select = 0;
	Employee* data;

	while (select != 7)
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select 0.Insert, 1. Remove, 2.Inorder, 3.Preorder, 4.Postorder, 5.Search, 6.Copy,7.LevelOrder, 8.NonrecInorder, 9.NoStackInorder, 10.Quit =>";
		cin >> select;
		string eno, ename;
		switch (static_cast<Enum>(select))
		{
		case Insert:
			cout << "삽입 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			t.insert(*data);
			break;
		case Remove:
			cout << "삭제 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			/*
			data = new Employee(eno, nullptr);//오류가 나는 이유는 nullptr은 포인터 타입인데 string으로 변환할 수가 없기 때문임
			*/
			cout << t.remove(*data);
			cout << endl;
			break;
		case Inorder:
			cout << "inorder print:: ";
			t.inorder();
			cout << endl;
			break;
		case Preorder:
			cout << "preorder print:: ";
			t.preorder();
			cout << endl;
			break;
		case Postorder:
			cout << "postorder print:: ";
			t.postorder();
			cout << endl;
			break;
		case Search:
			cout << "검색 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			if (t.search(*data))//입력된 x에 대한 tree 노드를 찾아 삭제한다.
				cout << eno << " 값이 존재한다" << endl;
			else
				cout << "값이 없다" << endl;
			break;
		case Copy:
			eq = (t == Tree(t));//copy constructor를 호출
			if (eq) {
				cout << "compare result: true" << endl;
			}
			else
				cout << "compare result: false" << endl;
			break;
		case LevelOrder:
			cout << "Level Order:: ";
			t.LevelOrder();
			break;
		case NonrecInorder:
			cout << "NonRecursive Order:: ";
			t.NonrecInorder();
			break;
		case NoStackInorder:
			cout << "No Stack Order:: ";
			t.NoStackInorder();
			break;
		case Quit:
			cout << "Quit" << endl;
			return 1;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;

}
