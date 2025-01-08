//�ҽ��ڵ� 5.8: Set ǥ��
/* sets - graph�� �ִܰ�ο��� ���
*/
#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

const int HeapSize = 100;

class Sets {
public:
	Sets(int);
	void display();//���պ��� {1,2,3} ���·� ���
	void SimpleUnion(int i, int j);//������ ����� ��°���� i�� ǥ��
	int SimpleFind(int);
	void WeightedUnion(int i, int j);//������ ����� ��°���� ������ ���� i �Ǵ� j�� ǥ��
	void Delete(int n);//n�� ���Ե� ���տ��� n�� ����, n�� �߰� ���, ��Ʈ�� �� ���� 
	void Difference(int i, int j);//������ ����� ��°���� i�� ǥ��
	void Intersection(int i, int j);//���� ���� ����� ��´� i�� ǥ��
private:
	int* parent;
	int n;
};
void Sets::Delete(int n) {
	//���տ��� n�� ���� >> n�� root�� ���, �߰� ����� ��� ���� �ʿ�


	//������ element�� root�� ã�´�

	// root�� n�̸� ���� �ڵ尡 �ʿ� 
	// ���� ������ ��� elements�� parent�� n�̸� root�� ����Ű�� �Ѵ� > n�� root�̸� alternate�� root�� �ؾ� �Ѵ�.


	// ���� ó���� -1�� ǥ���Ͽ� ���� ó��

}
Sets::Sets(int sz = HeapSize)
{
	n = sz;
	parent = new int[sz + 1]; // Don't want to use parent[0]
	for (int i = 1; i <= n; i++) parent[i] = -1;  // 0 for Simple versions
}

void Sets::SimpleUnion(int i, int j)
// Replace the disjoint sets with roots i and j, i != j with their union
{
	// i,j�� ���� ���

}

int Sets::SimpleFind(int i)
// Find the root of the tree containing element i
{

}

void Sets::WeightedUnion(int i, int j)
// Union sets with roots i and j, i != j, using the weighting rule.
// parent[i]=-count[i] and parent[i]=-count[i].
{
	
}



void Sets::display()
{
	//{1,2,3} , {4,5,6} ������ ǥ��

}


int main(void)
{
	Sets m(20);
	m.SimpleUnion(7, 1); m.SimpleUnion(2, 3); m.SimpleUnion(4, 5); m.SimpleUnion(6, 7);
	m.SimpleUnion(4, 2); m.SimpleUnion(5, 7); m.SimpleUnion(8, 10); m.SimpleUnion(13, 11);
	m.SimpleUnion(12, 9); m.SimpleUnion(14, 20); m.SimpleUnion(16, 19);
	m.SimpleUnion(17, 18); m.SimpleUnion(12, 19); m.SimpleUnion(13, 15);
	cout << "SimpleUnion() ���� ���::" << endl;
	m.display();
	m.WeightedUnion(1, 2); 	m.WeightedUnion(1, 4); m.WeightedUnion(23, 29); m.WeightedUnion(29, 15);
	m.WeightedUnion(29, 4); m.WeightedUnion(2, 29);
	cout << "WeightedUnion() ���� ���::" << endl;
	m.display();

	if (m.SimpleFind(2) == m.SimpleFind(18))
		cout << "2, 18�� ���� �����̴�";
	else
		cout << "2, 18�� �ٸ� �����̴�";
	m.display();
	cout << "***2�� ���տ��� �����Ѵ�***";
	m.Delete(2);
	if (m.SimpleFind(2) == m.SimpleFind(18))
		cout << "2, 18�� ���� �����̴�";
	else
		cout << "2, 18�� �ٸ� �����̴�";

	m.display();
	m.Difference(19, 29);
	m.display();
	m.Intersection(19, 29);
	m.display();
	system("pause");
	return 0;
}
