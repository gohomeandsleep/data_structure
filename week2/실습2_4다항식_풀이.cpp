//소스 코드2.5: Polynomial 클래스
/*
* +, -, *, << , >> operator를 사용한 버젼으로 구현한다.
* template 버젼으로 구현: T coef;
* sub와 Mult(), Eval()를 구현한다
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
class Polynomial;

class Term
{
	friend class Polynomial;
private:
	double coef;
	int exp;
public:
	double getCoef() const { return coef; }
	int getExp() const { return exp; }
	Term(double c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
	Polynomial() {
		start = finish = terms = 0;
	}
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
	friend ostream& operator <<(ostream&, Polynomial&);
	
	//construct the polynomial p(x) = 0;
	//Polynomial& Add(Polynomial& b);
	Polynomial& operator + (Polynomial&);
	Polynomial& operator - (Polynomial&);
	Polynomial& operator * (Polynomial&);
	double Eval(int);

	//return the sum of the polynomials *this and b
	//Polynomial Mult(Polynomial b);
	//return the product of the polynomials *this and b
	//float Eval(float f);
	//evaluate the polynomial *this at f and return the result

private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};

int Polynomial::GetData() {
	int degree;
	cout << "다항식의 degree 입력 : ";
	cin >> degree;

	capacity = degree + 1;

	// 객체 멤버 초기화
	start = free;

	int currentExp = degree;

	while (currentExp > 0 && free < capacity) {
		int exp = (rand() % currentExp) + 1; // 현재 지수보다 낮은 수들
		int coef = (rand() % 9) + 1; // 1~9까지 수

		termArray[free].coef = coef;
		termArray[free].exp = exp;
		++free;

		//cout << start << "|" << finish << "|" << free << endl;

		currentExp = exp - 1;
	}
	finish = free - 1;
	terms = (free - start);
	//cout << start << "|" << finish << "|" << free << "|" << terms << endl;

	return 0;
}

ostream& operator<<(ostream& stream, Polynomial& p) {
	bool first = true; //첫 번째 항의 경우 + 생략함
	for (int i = p.start; i <= p.finish; ++i) {
		int coef = p.termArray[i].getCoef();
		int exp = p.termArray[i].getExp();

		if (coef == 0) continue;

		if (coef > 0) stream << "+";
		else stream << "-";

		stream << abs(coef);
		stream << "x^" << exp;
	}

	return stream;
}

int Polynomial::Display() {//coef가 0이 아닌 term 만 있다고 가정한다 
	//cout << start << "|" << finish << "|" << free << "|" << terms << endl;
	bool first = true; //첫 번째 항의 경우 + 생략함
	for (int i = start; i <= finish; ++i) {
		int coef = termArray[i].getCoef();
		int exp = termArray[i].getExp();

		if (coef == 0) continue;

		if (coef > 0) cout << "+";
		else cout << "-";

		cout << abs(coef) << "x";
		cout << "^" << exp;
	}
	cout << endl;

	return 0;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp){
	if (terms == capacity)
	{
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;

}

Polynomial& Polynomial::operator+(Polynomial& b) {
	Polynomial* result = new Polynomial();

	int aPos = this->start;
	int bPos = b.start;

	result->start = free;

	while (aPos <= this->finish && bPos <= b.finish) {
		if (termArray[aPos].exp == termArray[bPos].exp) {
			double newCoef = termArray[aPos].coef + b.termArray[bPos].coef;
			if (newCoef != 0) {
				result->NewTerm(newCoef, termArray[aPos].exp);
			}
			aPos++;
			bPos++;
		}
		else if (termArray[aPos].exp > b.termArray[bPos].exp) {
			result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
		else {
			result->NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
	}

	while (aPos <= this->finish) {
		result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		aPos++;
	}

	while (bPos <= b.finish) {
		result->NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
		bPos++;
	}

	result->finish = free - 1;
	result->terms = free - result->start;

	return *result;
}

Polynomial& Polynomial::operator-(Polynomial& b) {
	Polynomial* result = new Polynomial();

	int aPos = this->start;
	int bPos = b.start;

	result->start = free;

	while (aPos <= this->finish && bPos <= b.finish) {
		if (termArray[aPos].exp == termArray[bPos].exp) {
			double newCoef = termArray[aPos].coef - b.termArray[bPos].coef;
			if (newCoef != 0) {
				result->NewTerm(newCoef, termArray[aPos].exp);
			}
			aPos++;
			bPos++;
		}
		else if (termArray[aPos].exp > b.termArray[bPos].exp) {
			result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
		else {
			result->NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
	}

	while (aPos <= this->finish) {
		result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		aPos++;
	}

	while (bPos <= b.finish) {
		result->NewTerm(-b.termArray[bPos].coef, b.termArray[bPos].exp);
		bPos++;
	}

	result->finish = free - 1;
	result->terms = free - result->start;

	return *result;
}

Polynomial& Polynomial::operator*(Polynomial& b) {
	Polynomial* result = new Polynomial();

	result->start = free;

	// this의 항들과 b의 항들을 각각 곱함
	for (int i = this->start; i <= this->finish; i++) {
		for (int j = b.start; j <= b.finish; j++) {
			double newCoef = termArray[i].coef * b.termArray[j].coef;
			int newExp = termArray[i].exp + b.termArray[j].exp;

			// 이미 있는 같은 지수의 항을 찾음
			bool found = false;
			for (int k = result->start; k < free; k++) {
				if (result->termArray[k].exp == newExp) {
					result->termArray[k].coef += newCoef; // 같은 지수라면 계수를 더함
					found = true;
					break;
				}
			}

			if (!found) {
				result->NewTerm(newCoef, newExp); // 같은 지수가 없으면 새로운 항 추가
			}
		}
	}

	result->finish = free - 1;
	result->terms = free - result->start;

	return *result;
}

double Polynomial::Eval(int x) {
	double result = 0.0;

	// 다항식의 각 항을 순차적으로 계산
	for (int i = start; i <= finish; i++) {
		result += termArray[i].coef * pow(x, termArray[i].exp); // coef * x^exp
	}

	return result; // 최종 계산된 결과 반환
}
// enum 선언
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT };
int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main(void) {
	srand(time(NULL));
	int choice;
	Polynomial P1, P2, P3;
	cout << "입력 예제: P(x)=5x^3+3x^1" << endl;
	cout << "입력 다항식 P1: " << endl;
	P1.GetData();
	P1.Display();
	cout << "입력 다항식 P2: " << endl;
	P2.GetData();
	P2.Display();
	
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n5: Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		// switch 문에서 enum 사용
		switch (static_cast<MenuChoice>(choice)) {
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "\nPolynomial2: ";
			cout << P2;
			P3 = P1 + P2;
			cout << "\n덧셈 결과: ";
			cout << P3;
			cout << "\n----------------------------------------\n";
			break;

		case SUBTRACTION:
			cout << "\n------------- Subtraction -------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1 - P2;
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case MULTIPLICATION:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1 * P2;
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case EVALUATION:
			cout << "\n------------- Evaluation -------------\n";
			int evalValue;
			cout << "Enter the value to evaluate Polynomial2: ";
			cin >> evalValue;
			cout << "Resultant Number : " << P2.Eval(evalValue);
			cout << "\n----------------------------------------" << endl;
			break;

		case EXIT:
			cout << "Good Bye...!!!" << endl;
			exit(0);

		default:
			cout << "Invalid choice! Please select again." << endl;
		}
	}
	
	system("pause");
	return 0;
}
