#include <stdio.h>
#include <stdlib.h>
/*
* 2단계: 5장 객체 simple binary tree, recursive inorder, preorder, postorder, copy, equal 함수를 구현
*/
#include <iostream>
#define MaxCapacity 20
using namespace std;
class Employee {
	friend class TreeNode;
	friend class Tree;
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
	os << " " << emp.eno << emp.ename;
	return os;
}

bool Employee::operator==(Employee& emp) {
	bool result = false;
	if (eno == emp.eno)
		return (ename == emp.ename);
	else
		return false;
}

bool Employee::operator<(Employee& emp) {	
	bool result = false;
	if (eno == emp.eno)
		return (ename < emp.ename);
	else
		return (eno < emp.eno);
}

class TreeNode {
	friend class Tree;
private:
	TreeNode* LeftChild;
	Employee data;
	TreeNode* RightChild;
public:
	TreeNode(Employee emp) : data(emp), LeftChild(nullptr), RightChild(nullptr) {}
};

class Tree {
public:
	Tree() { root = NULL; }
	Tree(const Tree& s) { root = copy(s.root);}
	TreeNode* inorderSucc(TreeNode* current);
	bool isLeafNode(TreeNode* current);
	void inorder() {
		inorder(root);
	}
	void preorder() {
		preorder(root);
	}
	void postorder() {
		postorder(root);
	}
	bool insert(Employee ex);
	bool remove(Employee ex);
	bool search(Employee ex);
	// Driver
	int operator==(const Tree& t) { return equal(this->root, t.root);}
private:
	TreeNode* root;
	void inorder(TreeNode* CurrentNode);
	void preorder(TreeNode* CurrentNode);
	void postorder(TreeNode* CurrentNode);
	TreeNode* copy(TreeNode* orignode);
	int equal(TreeNode* a, TreeNode* b);
};

TreeNode* Tree::inorderSucc(TreeNode* current)
{
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}
bool Tree::isLeafNode(TreeNode* current) {
	if (current->LeftChild == NULL && current->RightChild == NULL)
		return true;
	else
		return false;
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

void Tree::postorder(TreeNode* CurrentNode){
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}

TreeNode* Tree::copy(TreeNode* orignode){
	if (!orignode) return NULL;
	TreeNode* newNode = new TreeNode(orignode->data);
	newNode->LeftChild = copy(orignode->LeftChild);
	newNode->RightChild = copy(orignode->RightChild);
	return newNode;
}

// Workhorse
int Tree::equal(TreeNode* a, TreeNode* b){
	if (!a && !b) return 1;
	if (a && b && a->data == b->data) {
		return equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild);
	}
	return 0;
}
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */

bool Tree::insert(Employee ex) {
	TreeNode* p = root;
	TreeNode* q = NULL;
	while (p) {
		q = p;
		if (ex == p->data) return false; // Duplicate value
		p = (ex < p->data) ? p->LeftChild : p->RightChild;
	}
	TreeNode* newNode = new TreeNode(ex);
	if (!q) root = newNode;
	else if (ex < q->data) q->LeftChild = newNode;
	else q->RightChild = newNode;
	return true;
}
// binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을 설계하여 구현

bool Tree::remove(Employee ex) {
	TreeNode* p = root, * parent = NULL;
	while (p && p->data.eno != ex.eno) {
		parent = p;
		p = (ex < p->data) ? p->LeftChild : p->RightChild;
	}
	if (!p) return false;

	// Node with two children
	if (p->LeftChild && p->RightChild) {
		TreeNode* succ = inorderSucc(p);
		Employee val = succ->data;
		remove(succ->data);
		p->data = val;
	}
	else {
		TreeNode* child = (p->LeftChild) ? p->LeftChild : p->RightChild;
		if (!parent) root = child;
		else if (parent->LeftChild == p) parent->LeftChild = child;
		else parent->RightChild = child;
		delete p;
	}
	return true;
}

bool Tree::search(Employee ex) {
	TreeNode* p = root;
	while (p) {
		if (ex == p->data) {
			return true;
		}
		else if (ex < p->data) {
			p = p->LeftChild;
		}
		else {
			p = p->RightChild;
		}
	}
	return false;
}
enum Enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, Quit };

int main() {
	Tree t;
	bool eq = -1;
	int select = 0;
	Employee* data;

	while (select != 7)
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select 0.Insert, 1. Remove, 2.Inorder, 3.Preorder, 4.Postorder, 5.Search, 6.Copy, 7.Quit =>";
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
		case Quit:
			cout << "Quit" << endl;
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

