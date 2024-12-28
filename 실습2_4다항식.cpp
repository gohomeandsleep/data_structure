//�ҽ� �ڵ�2.5: Polynomial Ŭ����
/*
* +, -, *, << , >> operator�� ����� �������� �����Ѵ�.
* template �������� ����: T coef;
* sub�� Mult(), Eval()�� �����Ѵ�
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
	cout << "���׽��� degree �Է� : ";
	cin >> degree;

	capacity = degree + 1;

	// ��ü ��� �ʱ�ȭ
	start = free;

	int currentExp = degree;

	while (currentExp > 0 && free < capacity) {
		int exp = (rand() % currentExp) + 1; // ���� �������� ���� ����
		int coef = (rand() % 9) + 1; // 1~9���� ��

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
	bool first = true; //ù ��° ���� ��� + ������
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

int Polynomial::Display() {//coef�� 0�� �ƴ� term �� �ִٰ� �����Ѵ� 
	//cout << start << "|" << finish << "|" << free << "|" << terms << endl;
	bool first = true; //ù ��° ���� ��� + ������
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

	// this�� �׵�� b�� �׵��� ���� ����
	for (int i = this->start; i <= this->finish; i++) {
		for (int j = b.start; j <= b.finish; j++) {
			double newCoef = termArray[i].coef * b.termArray[j].coef;
			int newExp = termArray[i].exp + b.termArray[j].exp;

			// �̹� �ִ� ���� ������ ���� ã��
			bool found = false;
			for (int k = result->start; k < free; k++) {
				if (result->termArray[k].exp == newExp) {
					result->termArray[k].coef += newCoef; // ���� ������� ����� ����
					found = true;
					break;
				}
			}

			if (!found) {
				result->NewTerm(newCoef, newExp); // ���� ������ ������ ���ο� �� �߰�
			}
		}
	}

	result->finish = free - 1;
	result->terms = free - result->start;

	return *result;
}

double Polynomial::Eval(int x) {
	double result = 0.0;

	// ���׽��� �� ���� ���������� ���
	for (int i = start; i <= finish; i++) {
		result += termArray[i].coef * pow(x, termArray[i].exp); // coef * x^exp
	}

	return result; // ���� ���� ��� ��ȯ
}
// enum ����
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT };
int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main(void) {
	srand(time(NULL));
	int choice;
	Polynomial P1, P2, P3;
	cout << "�Է� ����: P(x)=5x^3+3x^1" << endl;
	cout << "�Է� ���׽� P1: " << endl;
	P1.GetData();
	P1.Display();
	cout << "�Է� ���׽� P2: " << endl;
	P2.GetData();
	P2.Display();
	
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n5: Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		// switch ������ enum ���
		switch (static_cast<MenuChoice>(choice)) {
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "\nPolynomial2: ";
			cout << P2;
			P3 = P1 + P2;
			cout << "\n���� ���: ";
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
