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
	void MoveRandom(int size);
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

void Matrix::MoveRandom(int size) {
	const int N = 8;
	int go = 1;
	//처음 위치를 정함
	int loc_x = rand() % rows;
	int loc_y = rand() % cols;
	Term[loc_x * cols + loc_y] += 1;

	//모든 요소에 0이 아닌 수로 채워지면 종료
	//dx,dy 테크닉을 기반으로 벌레의 이동을 구현
	while (!CheckNonZero()) {
		int x = rand() % N; //난수 생성 0~7 ->d변수 저장
		
		if (0 <= loc_x + moves[x].a && loc_x + moves[x].a < size &&
			0 <= loc_y + moves[x].b && loc_y + moves[x].b < size) { //테이블 안에 속하는지 확인
			//이동할 칸으로 이동하고 그 칸에 Term값 1증가
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
	cout << "Matrix 크기 : ";
	cin >> size;
	Matrix table(size, size);

	table.GetData();
	cout << "Before" << endl;
	table.Display();
	table.MoveRandom(size);
	cout << "After" << endl;
	table.Display();

	system("pause");
	return 0;
}

