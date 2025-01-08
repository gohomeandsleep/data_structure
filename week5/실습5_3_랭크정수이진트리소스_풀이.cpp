#include <iostream>
#include <vector>
#define MaxCapacity 20
using namespace std;

class TreeNode {
	friend class Tree;
private:
	TreeNode* LeftChild;
	int data;
	int leftSize;
	TreeNode* RightChild;
public:
	TreeNode(int value) : data(value), LeftChild(NULL), RightChild(NULL), leftSize(0) {}
	bool operator==(TreeNode& t) {
		return this->data == t.data;
	}
	bool operator<(TreeNode& t) {
		return this->data < t.data;
	}
	friend ostream& operator<<(ostream&, TreeNode&);
};

ostream& operator<<(ostream& os, TreeNode& t) {
	os << t.data << "(" << t.leftSize << ") ";
	return os;
}


class Tree {
public:
	Tree() {
		root = NULL;
	}
	Tree(const Tree& s)
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
	void rank() {
		rank(root);
	}
	int search(int rank);//nth 작은 값을 찾는다 
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
	int rank(TreeNode*);
};
int Tree::rank(TreeNode* current) {
	return current->leftSize;
}
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
		cout << *CurrentNode << " ";
		inorder(CurrentNode->RightChild);
	}
}
void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << *CurrentNode << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}
void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << *CurrentNode << " ";
	}
}
TreeNode* Tree::copy(TreeNode* orignode)
{
	if (!orignode) return NULL;
	TreeNode* newNode = new TreeNode(orignode->data);
	newNode->leftSize = orignode->leftSize;
	newNode->LeftChild = copy(orignode->LeftChild);
	newNode->RightChild = copy(orignode->RightChild);
	return newNode;
}

int Tree::equal(TreeNode* a, TreeNode* b)
// Workhorse
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if (!a && !b) return 1;
	if (a && b && *a == *b) 
		return equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild);
	return 0;
}

bool Tree::insert(int x) {
	TreeNode* newNode = new TreeNode(x);
	TreeNode* p = root;
	TreeNode* q = NULL;

	while (p) {
		if (*p == *newNode) { //같은 값은 false
			return false;
		}
		else if (*newNode < *p)		{ //왼쪽으로 이동하고 p에 rank + 1
			q = p;
			p = p->LeftChild;
		}
		else {
			q = p;
			p = p->RightChild;
		}
	}
	if (!q) root = newNode;
	else if (*newNode < *q) q->LeftChild = newNode;
	else q->RightChild = newNode;

	//다시 순회하면서 조건에 따라 rank +1
	TreeNode* rank = root;
	while (rank) {
		if (*rank == *newNode) break;
		else if (*newNode < *rank) {
			rank->leftSize += 1;
			rank = rank->LeftChild;
		}
		else {
			rank = rank->RightChild;
		}
	}

	return true;
}

bool Tree::remove(int num) {
	TreeNode* p = root, *q = NULL;

	while (p && p->data != num) {
		q = p;
		if (num < p->data) p = p->LeftChild;
		else p = p->RightChild;
	}
	//찾는 값이 없을 경우
	if (!p) return false;
	
	int val = -1;
	//노드 삭제 진행
	if (p->LeftChild && p->RightChild) {
		TreeNode* succ = inorderSucc(p);
		val = succ->data;
		cout << val << endl;
		remove(succ->data);
		p->data = val;
	}
	else {
		TreeNode* child;
		if (p->LeftChild) child = p->LeftChild;
		else child = p->RightChild;
		if (!q) root = child;
		else if (q->LeftChild == p) q->LeftChild = child;
		else q->RightChild = child;
		delete p;
	}

	//다시 순회하면서 조건에 따라 rank -1
	TreeNode* rank = root;
	if (val != -1) num = val;
	while (rank) {
		if (rank->data == num) break;
		else if (num < rank->data) {
			cout << rank->data << "감소 발생" << endl;
			rank->leftSize -= 1;
			rank = rank->LeftChild;
		}
		else {
			rank = rank->RightChild;
		}
	}

	return true;
	
}

int Tree::search(int rank) {
	TreeNode* p = root;
	if (!p) return -1; //트리가 비었으면 -1
	while (p) {
		if (rank == p->leftSize + 1) return p->data;
		else if (rank <= p->leftSize) p = p->LeftChild;
		else {
			rank -= (p->leftSize + 1);
			p = p->RightChild;
		}
	}

	return -1;
}
enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, Quit };
int main() {
	srand(time(NULL));
	Tree t;
	bool eq = false;
	int select = 0, rankNumber = 0;
	int max = 0, x = 0;
	vector<int> numList;
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
				cout << rnd << "\t";
				if (!t.insert(rnd)) cout << "NO (Duplication)" << endl;
				else cout << "OK" << endl;
			}
			break;
		case Remove:
			int x;
			cin >> x;
			if (t.remove(x)) cout << "삭제 완료" << endl;
			else cout << "값이 없음" << endl;
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
			t.rank();
			cout << "찾고자 하는 rank 순위 입력: ";
			cin >> x;
			rankNumber = t.search(x); // x번째 순위의 값을 찾는다
			if (rankNumber != -1)cout << x << " 번째 순위 값은 " << rankNumber << endl;
			else cout << "값이 존재하지 않음" << endl;
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

