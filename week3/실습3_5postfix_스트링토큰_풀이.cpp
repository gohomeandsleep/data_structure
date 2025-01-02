#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <exception>
#include <time.h>

using namespace std;


class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return " 빈 Stack.";
    }
};

class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "full Stack.";
    }
};
 
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 4);
    bool IsFull() const;
    bool IsEmpty() const;
    T& Peek() const;
    void Push(const T& item);
    T Pop();
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity), top(-1) {
    stack = new T[capacity];
}

template <class T>
T& Stack<T>::Peek() const {
    if (IsEmpty()) {
        throw EmptyStackException();
    }
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& item) {
    if (IsFull()) {
        throw OverflowStackException();
    }
    stack[++top] = item;
}

template <class T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        throw EmptyStackException();
    }
    return stack[top--];
}

template <class T>
bool Stack<T>::IsEmpty() const {
    return top == -1;
}

template <class T>
bool Stack<T>::IsFull() const {
    return top == capacity - 1;
}
    
typedef vector<string> Expr;
typedef string Token;

int idx = 0;
int inputData[26] = { 0 };

string NextToken(const string& e, int idx) {
    //cout << idx;
    string token;
    //cout << e[idx] << endl;
    if (idx >= e.length()) {
        return "#";
    }

    if (idx < e.length() - 1) {

        if (e[idx] == '>' && e[idx + 1] == '=') {
            idx += 2;
            return ">=";
        }
        if (e[idx] == '<' && e[idx + 1] == '=') {
            idx += 2;
            return "<=";
        }
        if (e[idx] == '=' && e[idx + 1] == '=') {
            idx += 2;
            return "==";
        }
        if (e[idx] == '!' && e[idx + 1] == '=') {
            idx += 2;
            return "!=";
        }
        if (e[idx] == '&' && e[idx + 1] == '&') {
            idx += 2;
            return "&&";
        }
        if (e[idx] == '|' && e[idx + 1] == '|') {
            idx += 2;
            return "||";
        }
    }

    if (e[idx] == '-') {
        if (idx == 0 || !isalpha(e[idx - 1]) && e[idx - 1] != '(' && e[idx - 1] != ')') {
            return "ㅡ";
        }
    }

    if (string("+-*/><()!").find(e[idx]) != string::npos) {
        token += e[idx];
        idx++;
        return token;
    }

    if (isalpha(e[idx])) {
        token += e[idx];
        idx++;
        return token;
    }
}

bool isOperand(const string& x) {
    return (x.size() == 1 && isalpha(x[0]));
}

int isp(const string& a) {
    if (a == "#") return 8;
    if (a == "(") return 8;
    if (a == "+" || a == "-") return 3;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "!" || a == "ㅡ") return 1;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9;
}

int icp(const string& a) {
    if (a == "(") return 0;
    if (a == "+" || a == "-") return 3;
    if (a == "!" || a == "ㅡ") return 1;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9;
}

void stringAdd(Expr& ex, const string& str) {
    ex.push_back(str);
}

Expr Postfix(const string& e) {
    Stack<string> stack(30);
    Expr result;
    stack.Push("#");

    size_t idx = 0;
    string token;
    while (idx < e.size()){
        token = NextToken(e, idx);
        if (token.length() == 2 && token != "ㅡ") {
            idx += 2;
        }
        else idx++;

        if (isOperand(token)) {
            stringAdd(result, token);
        }
        else if (token == ")") {
            while (stack.Peek() != "(") {
                stringAdd(result, stack.Pop());
            }
            stack.Pop();
        }
        else {
            while (isp(stack.Peek()) <= icp(token)) {
                stringAdd(result, stack.Pop());
            }

            stack.Push(token);
        }
    }

    while (stack.Peek() != "#") {
        stringAdd(result, stack.Pop());
    }

    return result;
}

void InitializeInputData() {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 26; ++i) {
        inputData[i] = rand() % 9 + 1;
    }
}

void Eval(const Expr& e) {
    Stack<int> stack(30);
    
    for(const auto& token : e)
    {
        if (isOperand(token)) {
            int value = inputData[token[0] - 'A'];

        	stack.Push(value);
        }
        else if (token == "!") 
        {
            int operand = stack.Pop();
            stack.Push(!operand);
        }
        else if (token == "ㅡ")
        {
            int operand = -stack.Pop();
            stack.Push(operand);
        }

        else 
        {
            int operand2 = stack.Pop();
            int operand1 = stack.Pop();
            int result = 0;

            if (token == "+") {
                result = operand1 + operand2;
            }
            
            else if (token == "-") {
                result = operand1 - operand2;
            }
            else if (token == "*") {
                result = operand1 * operand2;
            }
            else if (token == "/") {
                result = operand1 / operand2;
            }
            else if (token == "%") {
                result = operand1 % operand2;
            }
            else if (token == "<") {
                result = operand1 < operand2;
            }
            else if (token == ">") {
                result = operand1 > operand2;
            }
            else if (token == "<=") {
                result = operand1 <= operand2;
            }
            else if (token == ">=") {
                result = operand1 >= operand2;
            }
            else if (token == "==") {
                result = operand1 == operand2;
            }
            else if (token == "!=") {
                result = operand1 != operand2;
            }
            else if (token == "&&") {
                result = operand1 && operand2;
            }
            else if (token == "||") {
                result = operand1 || operand2;
            }

            stack.Push(result);
        }
    }
    cout << "Evaluation Result: " << stack.Pop() << endl;
}

enum class Expressions {
    Exit, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11
};

std::string expressionToString(Expressions expression) {
    switch (expression) {
    case Expressions::E1: return "A/B-C+D*E-A*C";
    case Expressions::E2: return "(((A/B)-C)+(D*E))-(A*C)";
    case Expressions::E3: return "A*B*C";
    case Expressions::E4: return "-A+B-C+D";
    case Expressions::E5: return "A*-B+C";
    case Expressions::E6: return "(A+B)*D+E/(F+A*D)+C";
    case Expressions::E7: return "A&&B||C||!(E>F)";
    case Expressions::E8: return "!(A&&!((B<C)||(C>D)))||(E<E)";
    case Expressions::E9: return "A*B/C";
    case Expressions::E10: return "A/B-C+D*E-A*C";
    case Expressions::E11: return "A*(B+C)/D-G";
    default: return "Unknown";
    }
}

void PrintExpr(const Expr& ex) {
    for (const auto& token : ex) {
        cout << token;
    }
    cout << endl;
}

Expressions SelectExpression() {
    int choice;
    cout << "1:E1,2:E2,3:E3,4:E4,5:E5,6:E6,7:E7,8:E8,9:E9,10:E10,11:E11,0:Exit\n";
    cout << "번호: ";
    cin >> choice;
    return static_cast<Expressions>(choice);
}

void toPostfix(const string& infixString) {
    cout << endl << "infix 표기의 expression 입력: " << infixString;
    Expr result = Postfix(infixString);
    cout << "\n후위 표기식: ";
    PrintExpr(result);
    Eval(result);
}

int main() {
    InitializeInputData();
    
    Expressions menu;
    string infix;
    while (true) {
        try {
            menu = SelectExpression();
            switch (menu) {
            case Expressions::E1: {
                infix = expressionToString(Expressions::E1);
                toPostfix(infix);
                break;
            }
            case Expressions::E2: {
                infix = expressionToString(Expressions::E2);
                toPostfix(infix);
                break;
            }
            case Expressions::E3: {
                infix = expressionToString(Expressions::E3);
                toPostfix(infix);
                break;
            }
            case Expressions::E4: {
                infix = expressionToString(Expressions::E4);
                toPostfix(infix);
                break;
            }
            case Expressions::E5: {
                infix = expressionToString(Expressions::E5);
                toPostfix(infix);
                break;
            }
            case Expressions::E6: {
                infix = expressionToString(Expressions::E6);
                toPostfix(infix);
                break;
            }
            case Expressions::E7: {
                infix = expressionToString(Expressions::E7);
                toPostfix(infix);
                break;
            }
            case Expressions::E8: {
                infix = expressionToString(Expressions::E8);
                toPostfix(infix);
                break;
            }
            case Expressions::E9: {
                infix = expressionToString(Expressions::E9);
                toPostfix(infix);
                break;
            }
            case Expressions::E10: {
                infix = expressionToString(Expressions::E10);
                toPostfix(infix);
                break;
            }
            case Expressions::E11: {
                infix = expressionToString(Expressions::E11);
                toPostfix(infix);
                break;
            }
            case Expressions::Exit:
                return 0;
            }

        }
        catch (const EmptyStackException& e) {
            cout << "스택 empty 예외 : " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "스택 overflow 예외: " << e.what() << endl;
        }
        catch (...) {
            cout << "An unknown exception occurred." << endl;
        }
    }
}
