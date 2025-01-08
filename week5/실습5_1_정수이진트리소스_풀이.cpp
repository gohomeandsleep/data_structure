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
	TreeNode(int val) : data(val), LeftChild(NULL), RightChild(NULL) {}
};

class Tree {
public:
	Tree() { root = NULL;}
	Tree(const Tree& s){ root = copy(s.root);}
	TreeNode* inorderSucc(TreeNode* current);
	bool isLeafNode(TreeNode* current);
	void inorder() { inorder(root); }
	void preorder() { preorder(root); }
	void postorder() { postorder(root); }
	bool insert(int x);
	bool remove(int num);
	bool search(int num);
	int operator==(const Tree& t) { return equal(this->root, t.root); }// Driver
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

TreeNode* Tree::copy(TreeNode* orignode) {
	if (!orignode) return NULL;
	TreeNode* newNode = new TreeNode(orignode->data);
	newNode->LeftChild = copy(orignode->LeftChild);
	newNode->RightChild = copy(orignode->RightChild);
	return newNode;
}

// Workhorse
int Tree::equal(TreeNode* a, TreeNode* b) {
	if (!a && !b) return 1;
	if (a && b && a->data == b->data) {
		return equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild);
	}
	return 0;
}
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */

bool Tree::insert(int x) {
	TreeNode* p = root;
	TreeNode* q = NULL;
	while (p) {
		q = p;
		if (x == p->data) return false; // Duplicate value
		p = (x < p->data) ? p->LeftChild : p->RightChild;
	}
	TreeNode* newNode = new TreeNode(x);
	if (!q) root = newNode;
	else if (x < q->data) q->LeftChild = newNode;
	else q->RightChild = newNode;
	return true;
}

bool Tree::remove(int num) {
	TreeNode* p = root, * parent = NULL;
	while (p && p->data != num) {
		parent = p;
		p = (num < p->data) ? p->LeftChild : p->RightChild;
	}
	if (!p) return false;

	// Node with two children
	if (p->LeftChild && p->RightChild) {
		TreeNode* succ = inorderSucc(p);
		int val = succ->data;
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

bool Tree::search(int num) {
	TreeNode* p = root;
	while (p) {
		if (num == p->data) return true;
		p = (num < p->data) ? p->LeftChild : p->RightChild;
	}
	return false;
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
				rnd = rand() % 100;
				if (!t.insert(rnd)) cout << "Insert Duplicated data" << endl;
			}
			break;
		case Remove:
			int x;
			cin >> x;
			cout << t.remove(x);//입력된 x에 대한 tree 노드를 찾아 삭제한다.
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
			if (t.search(x))//입력된 x에 대한 tree 노드를 찾아 삭제한다.
				cout << x << " 값이 존재한다" << endl;
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
	return 0;

}

