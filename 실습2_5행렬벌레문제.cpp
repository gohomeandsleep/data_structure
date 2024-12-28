#include <iostream>
using namespace std;
#include <stdlib.h>
#include "time.h"
struct Offsets {
	int a, b;
} moves[8] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} 
};

class Matrix {
private:
	bool CheckNonZero();
public:
	Matrix(int r, int col) : rows(r), cols(col) {
		Term = new int[rows * cols];
	}
	int GetData();
	void MoveRandom();
	int Display();

private:
	int rows, cols;
	int* Term;
};

bool Matrix::CheckNonZero() {
	for (int i = 0; i < rows * cols; i++) {
		if (Term[i] == 0) {
			return false;
		}
	}
	return true;
}

int Matrix::GetData() {
	for (int i = 0; i < rows * cols; i++) {
		Term[i] = 0;
	}
	return 0;
}

int Matrix::Display() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << Term[i * cols + j] << " ";
		}
		cout << endl;
	}
	return 0;
}

void Matrix::MoveRandom() {
	const int N = 8;
	int go = 1;
	//ó�� ��ġ�� ����
	int loc_x = rand() % rows;
	int loc_y = rand() % cols;
	Term[loc_x * cols + loc_y] += 1;

	//��� ��ҿ� 0�� �ƴ� ���� ä������ ����
	//dx,dy ��ũ���� ������� ������ �̵��� ����
	while (!CheckNonZero()) {
		int x = rand() % N; //���� ���� 0~7 ->d���� ����
		
		if (0 <= loc_x + moves[x].a && loc_x + moves[x].a < 3 &&
			0 <= loc_y + moves[x].b && loc_y + moves[x].b < 3) { //���̺� �ȿ� ���ϴ��� Ȯ��
			//�̵��� ĭ���� �̵��ϰ� �� ĭ�� Term�� 1����
			loc_x += moves[x].a;
			loc_y += moves[x].b;
			Term[loc_x * cols + loc_y] += 1;
			go += 1;
		}
		//Term[x * cols + y] = 1;
	}

	cout << "Finished in " << go << "moves." << endl;
}

int main()
{
	srand(time(NULL));
	Matrix table(3, 3);

	table.GetData();
	cout << "Before" << endl;
	table.Display();
	table.MoveRandom();
	cout << "After" << endl;
	table.Display();

	system("pause");
	return 0;
}

