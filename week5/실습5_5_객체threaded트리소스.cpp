//소스코드 5.3: Threaded Tree


//Tree 5.13 Threaded binary tree
/*
1. template version으로 Employee 객체를 노드에 저장
2. tree iterator를 사용하여 sum을 구한다
3. main에서 Insert, Remove, Inorder, IteratorInorder, Search, PrintTree는 Employee에 대하여 구현한다
4. Employee 객체는 화면에서 입력하지 않고 10개의 객체를 배열로 초기화 for문으로 입력한다.
5. main에서 InsertStudent, InorderStudent는 Student에 대하여 구현한다.
*/
#include <iostream>
#include <cstdlib>
#define MAX_VALUE 65536
using namespace std;


class ThreadedTree;
class Employee {
	string eno;
	string ename;
	int salary;
public:

};
class Student {
	string snum;
	string sname;
	int age;
public:
	Student() {}
};
template <class T>
class ThreadedNode {
	friend class ThreadedTree;
	friend class ThreadedInorderIterator;
private:
	bool LeftThread;
	ThreadedNode* LeftChild;
	T data;
	ThreadedNode* RightChild;
	bool RightThread;
public:
	ThreadedNode() { LeftChild = RightChild = 0; };
	ThreadedNode(char ch) { data = ch; };
	ThreadedNode(char ch, ThreadedNode* lefty, ThreadedNode* righty,
		bool lthread, bool rthread)
	{
		data = ch; LeftChild = lefty; RightChild = righty;
		LeftThread = lthread;  RightThread = rthread;
	};
};
template <class T>
class ThreadedTree {
	friend class ThreadedInorderIterator;
private:
	ThreadedNode* root;
	void Inorder(ThreadedNode*, bool);
public:
	/* Constructor */
	ThreadedTree() {
		root = new ThreadedNode;
		root->RightChild = root->LeftChild = root;
		root->data = 'z';
		root->LeftThread = true; root->RightThread = false;
	};
	void InsertRight(ThreadedNode*, char);
	bool Insert(char data);
	void Delete(char data);
	void Inorder();
	void PrintTree();
	bool Search(char data);
	ThreadedNode* InorderSucc(ThreadedNode*);
};


ThreadedNode* ThreadedTree::InorderSucc(ThreadedNode* current)
{
	ThreadedNode* temp = current->RightChild;
	if (!current->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	return temp;
}


void ThreadedTree::InsertRight(ThreadedNode* s, char ch)
// Create node r; store ch in r; insert r as the right child of s
{

}

/* Function to delete an element */
void ThreadedTree::Delete(char data)
{
	
	}
}void ThreadedTree::Inorder()
{
	Inorder(root, root->LeftThread);
}

void ThreadedTree::Inorder(ThreadedNode* CurrentNode, bool b)
{
	if (!b) {
		Inorder(CurrentNode->LeftChild, CurrentNode->LeftThread);
		cout << " " << CurrentNode->data;
		cout << "Inorder:" << "rightthread=" << CurrentNode->RightThread;
		if (CurrentNode->RightChild != root) Inorder(CurrentNode->RightChild, CurrentNode->RightThread);
	}
}


bool ThreadedTree::Insert(char d)//leaf node에만 insert, 중간 노드에 insert 아님
{
	
}


/* Function to print tree */
void ThreadedTree::PrintTree()
{
	
	cout << endl;
}
template <class T>
class ThreadedInorderIterator {
public:
	void Inorder();
	T* Next();
	ThreadedInorderIterator(ThreadedTree tree) : t(tree) {
		CurrentNode = t.root;
	};
private:
	ThreadedTree t;
	ThreadedNode* CurrentNode;
};

T* ThreadedInorderIterator::Next()
// Find the inorder successor of CurrentNode in a threaded binary tree
{
	
}

void ThreadedInorderIterator::Inorder()
{
	


enum Enum { Insert, Remove, Inorder, IteratorInorder, Search, PrintTree, Sum, InsertStudent, InorderStudent, Quit };
int main() {
	ThreadedTree<Employee> te;
	ThreadedTree<Student> ts;
	ThreadedInorderIterator ti(te);
	cout << "ThreadedTree Test\n";
	char ch;
	int select;

	Employee* data;
	cout << "\nThreadedTree Operations\n";

	while (select != 7)
	{
		cout << "1. Insert list, 2. Remove, 3.Inorder, 4.IteratorInorder, 5.Search, 6.PrintTree, 7.Sum, 8. InsertStudent, 9.InorderStudent, 10.Quit" << endl;
		// postorder traversal
		// preorder traversal
		cout << "Enter Your Choice: ";
		cin >> select;
		int rnd = 0;
		cin >> select;
		string eno, ename;
		switch (static_cast<Enum>(select))
		{
		case Insert:
			//객체 배열 초기화하여 입력
			te.insert(*data);
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
			cout << te.Delete(*data);
			cout << endl;
			break;

		case Inorder:
			cout << "Recursive Inorder" << endl;
			te.Inorder();
			break;
		case IteratorInorder:
			cout << "IteratorInorder" << endl;
			ti.Inorder();
			break;
		case Search:
			cout << "검색 사원번호 입력:: ";
			cin >> eno;
			cout << "삽입 사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			if (te.search(*data))//입력된 x에 대한 tree 노드를 찾아 삭제한다.
				cout << eno << " 값이 존재한다" << endl;
			else
				cout << "값이 없다" << endl;

			break;
		case PrintTree:
			cout << "PrintTree " << endl;
			te.PrintTree();
			break;
		case Sum:
			//iterator를 사용한 구현 : 모든 노드의 salary를 합한다
			break;
		case InsertStudent:
			//객체 배열 초기화하여 입력
			t.insert(*data);
			break;
		case InorderStudent:
			//출력
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;

}