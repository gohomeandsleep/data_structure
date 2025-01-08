#include <stdio.h>
#include <stdlib.h>
/*
* 2�ܰ�: 5�� ��ü simple binary tree, recursive inorder, preorder, postorder, copy, equal �Լ��� ����
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
		return (ename < emp.eno);
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

};

class Tree {
public:
	Tree() {
		root = NULL;
	}
	Tree::Tree(const Tree& s)//copy constructor
	{
		root = copy(s.root);
	}
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
	int operator==(const Tree& t)
	{
		return equal(this->root, t.root);
	}
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

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}



TreeNode* Tree::copy(TreeNode* orignode)
{

}


// Workhorse
int Tree::equal(TreeNode* a, TreeNode* b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{

}


bool Tree::insert(Employee ex) {// binary search tree�� ����� �Է� => A + B * C�� tree�� ����� ���: �Է� �ذ��ϴ� �˰��� �ۼ� �����
							// �����Ͽ� ����

}

bool Tree::remove(Employee ex) {


}

bool Tree::search(Employee ex) {

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
			cout << "���� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			t.insert(*data);
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
			cout << "�˻� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			if (t.search(*data))//�Էµ� x�� ���� tree ��带 ã�� �����Ѵ�.
				cout << eno << " ���� �����Ѵ�" << endl;
			else
				cout << "���� ����" << endl;
			break;
		case Copy:
			eq = (t == Tree(t));//copy constructor�� ȣ��
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

