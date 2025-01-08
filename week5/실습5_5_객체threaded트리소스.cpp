//�ҽ��ڵ� 5.3: Threaded Tree


//Tree 5.13 Threaded binary tree
/*
1. template version���� Employee ��ü�� ��忡 ����
2. tree iterator�� ����Ͽ� sum�� ���Ѵ�
3. main���� Insert, Remove, Inorder, IteratorInorder, Search, PrintTree�� Employee�� ���Ͽ� �����Ѵ�
4. Employee ��ü�� ȭ�鿡�� �Է����� �ʰ� 10���� ��ü�� �迭�� �ʱ�ȭ for������ �Է��Ѵ�.
5. main���� InsertStudent, InorderStudent�� Student�� ���Ͽ� �����Ѵ�.
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


bool ThreadedTree::Insert(char d)//leaf node���� insert, �߰� ��忡 insert �ƴ�
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
			//��ü �迭 �ʱ�ȭ�Ͽ� �Է�
			te.insert(*data);
			break;
		case Remove:
			cout << "���� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			/*
			data = new Employee(eno, nullptr);//������ ���� ������ nullptr�� ������ Ÿ���ε� string���� ��ȯ�� ���� ���� ������
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
			cout << "�˻� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			if (te.search(*data))//�Էµ� x�� ���� tree ��带 ã�� �����Ѵ�.
				cout << eno << " ���� �����Ѵ�" << endl;
			else
				cout << "���� ����" << endl;

			break;
		case PrintTree:
			cout << "PrintTree " << endl;
			te.PrintTree();
			break;
		case Sum:
			//iterator�� ����� ���� : ��� ����� salary�� ���Ѵ�
			break;
		case InsertStudent:
			//��ü �迭 �ʱ�ȭ�Ͽ� �Է�
			t.insert(*data);
			break;
		case InorderStudent:
			//���
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