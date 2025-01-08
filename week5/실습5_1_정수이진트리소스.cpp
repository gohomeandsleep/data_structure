/*
* 1�ܰ�: 5�� ���� simple binary tree, recursive inorder, preorder, postorder, copy, equal �Լ��� ����
*/
#include <iostream>
#define MaxCapacity 20
using namespace std;

class TreeNode {
	friend class Tree;
private:
	TreeNode* LeftChild;
	int data;
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
	bool insert(int x);
	bool remove(int num);
	bool search(int num);
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


bool Tree::insert(int x) {
	TreeNode* p = root;
	TreeNode* q = NULL;

}

bool Tree::remove(int num) {


}

bool Tree::search(int num) {
	TreeNode* p = root;

}
enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, Quit };
int main() {
	srand(time(NULL));
	Tree t;
	bool eq = -1;
	int select = 0;
	int max = 0, x = 0;
	while (select != 7)
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select 0.Insert, 1. Remove, 2.Inorder, 3.Preorder, 4.Postorder, 5.Search, 6.Copy, 7.Quit =>";
		cin >> select;
		switch (select)
		{
		case Insert:
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				rnd = rand() % 20;
				if (!t.insert(rnd)) cout << "Insert Duplicated data" << endl;
			}

			break;
		case Remove:
			int x;
			cin >> x;
			cout << t.remove(x);//�Էµ� x�� ���� tree ��带 ã�� �����Ѵ�.
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
			cin >> x;
			if (t.search(x))//�Էµ� x�� ���� tree ��带 ã�� �����Ѵ�.
				cout << x << " ���� �����Ѵ�" << endl;
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

