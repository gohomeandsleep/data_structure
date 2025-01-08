//소스코드 5.8: Set 표현
/* sets - graph의 최단경로에서 사용
*/
#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

const int HeapSize = 100;

class Sets {
public:
	Sets(int);
	void display();//집합별로 {1,2,3} 형태로 출력
	void SimpleUnion(int i, int j);//합집합 결과를 출력결과는 i에 표현
	int SimpleFind(int);
	void WeightedUnion(int i, int j);//차집합 결과를 출력결과는 갯수가 많은 i 또는 j에 표현
	void Delete(int n);//n이 포함된 집합에서 n을 제거, n이 중간 노드, 루트일 수 있음 
	void Difference(int i, int j);//차집합 결과를 출력결과는 i에 표현
	void Intersection(int i, int j);//교차 집합 결과를 출력는 i에 표현
private:
	int* parent;
	int n;
};
void Sets::Delete(int n) {
	//집합에서 n을 삭제 >> n이 root인 경우, 중간 노드인 경우 구현 필요


	//삭제할 element의 root를 찾는다

	// root가 n이면 수정 코드가 필요 
	// 같은 집합의 모든 elements의 parent가 n이면 root를 가리키게 한다 > n이 root이면 alternate를 root로 해야 한다.


	// 삭제 처리는 -1로 표시하여 삭제 처리

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
	// i,j는 임의 노드

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
	//{1,2,3} , {4,5,6} 등으로 표현

}


int main(void)
{
	Sets m(20);
	m.SimpleUnion(7, 1); m.SimpleUnion(2, 3); m.SimpleUnion(4, 5); m.SimpleUnion(6, 7);
	m.SimpleUnion(4, 2); m.SimpleUnion(5, 7); m.SimpleUnion(8, 10); m.SimpleUnion(13, 11);
	m.SimpleUnion(12, 9); m.SimpleUnion(14, 20); m.SimpleUnion(16, 19);
	m.SimpleUnion(17, 18); m.SimpleUnion(12, 19); m.SimpleUnion(13, 15);
	cout << "SimpleUnion() 실행 결과::" << endl;
	m.display();
	m.WeightedUnion(1, 2); 	m.WeightedUnion(1, 4); m.WeightedUnion(23, 29); m.WeightedUnion(29, 15);
	m.WeightedUnion(29, 4); m.WeightedUnion(2, 29);
	cout << "WeightedUnion() 실행 결과::" << endl;
	m.display();

	if (m.SimpleFind(2) == m.SimpleFind(18))
		cout << "2, 18은 같은 집합이다";
	else
		cout << "2, 18은 다른 집합이다";
	m.display();
	cout << "***2를 집합에서 삭제한다***";
	m.Delete(2);
	if (m.SimpleFind(2) == m.SimpleFind(18))
		cout << "2, 18은 같은 집합이다";
	else
		cout << "2, 18은 다른 집합이다";

	m.display();
	m.Difference(19, 29);
	m.display();
	m.Intersection(19, 29);
	m.display();
	system("pause");
	return 0;
}
