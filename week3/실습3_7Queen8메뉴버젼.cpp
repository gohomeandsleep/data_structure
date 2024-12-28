#include <iostream>
#include <stdio.h>
#define ROW 8
#define COL 8

using namespace std;

//예외처리를 위한 클래스
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


class Point {
private:
    int ix;
    int iy;
public:
    Point(int x = 0, int y = 0) : ix(x), iy(y) {}
    int getX() const { return ix; }
    int getY() const { return iy; }
};

//스택 클래스
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    T& Pop();
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
bool Stack<T>::IsEmpty() const{
    return top == -1;
}

template <class T>
T& Stack<T>::Top() const {
    return top;
}

template <class T>
void Stack<T>::Push(const T& item) {
     stack[++top] = item;
}

template <class T>
T& Stack<T>::Pop() {
    if (IsEmpty()) {
        throw EmptyStackException();
    }
    return stack[top--];
}

//퀸을 놓을 수 있는지 확인하는 함수
bool checkRow(int d[][COL], int crow) {
    for (int col = 0; col < COL; col++) {
        if (d[crow][col] == 1) return false;
    }
    return true;
}

bool checkCol(int d[][COL], int ccol) {
    for (int row = 0; row < ROW; row++) {
        if (d[row][ccol] == 1) return false;
    }
    return true;
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++
    for (int i = 1; (cx - i >= 0) && (cy - i >= 0); i++) {
        if (d[cx - i][cy - i] == 1) return false;
    }
    for (int i = 1; (cx + i < ROW) && (cy + i < COL); i++) {
        if (d[cx + i][cy + i] == 1) return false;
    }
    return true;
}

bool checkDiagSE(int d[][COL], int cx, int cy) { // x++, y++ or x--, y--
    for (int i = 1; (cx - i >= 0) && (cy + i < COL); i++) {
        if (d[cx - i][cy + i] == 1) return false;
    }
    for (int i = 1; (cx + i < ROW) && (cy - i >= 0); i++) {
        if (d[cx + i][cy - i] == 1) return false;
    }
    return true;
}

bool checkMove(int d[][COL], int y, int x) {
    bool rowCheck = checkRow(d, x);
    bool colCheck = checkCol(d, y);
    bool diagSWCheck = checkDiagSW(d, x, y);
    bool diagSECheck = checkDiagSE(d, x, y);

    return rowCheck && colCheck && diagSWCheck && diagSECheck;
}

//다음 행에 퀸을 놓을 수 있는지 확인하는 함수
int nextMove(int d[][COL], int col, int row) {
    for (int nextCol = col; nextCol < COL; nextCol++) {
        if (checkMove(d, row, nextCol)) return nextCol;
    }
    return -1;
}

void showQueens(int data[][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << (data[j][i] == 1 ? "Q" : "□");
        }
        cout << endl;
    }
    cout << endl;
}

//퀸을 놓는 함수
int solveQueen(int d[][COL], bool findAll) {
    int ix = 0, iy = 0;
    Stack<Point> st((COL + 1) * (COL + 1));
    Point p(ix, iy);
    d[ix][iy] = 1;
    st.Push(p);
    
    iy += 1;
    int solutions = 0;
    while (true) {
        try {
            int nextCol = nextMove(d, ix, iy);
            if (nextCol != -1) {
                ix = nextCol;
                if (ix < ROW) {
                    d[ix][iy] = 1;
                    st.Push(Point(ix, iy));
                    iy += 1;
                    ix = 0;
                }
            }

            else {
                Point last = st.Pop();
                ix = last.getX();
                iy = last.getY();
                d[ix][iy] = 0;
                ix += 1;

            }
            if (iy == ROW) {
                showQueens(d);
                solutions++;
                if (!findAll) break;
                Point last = st.Pop();
                ix = last.getX();
                iy = last.getY();
                d[ix][iy] = 0;
                ix += 1;
            }
        }
        catch (EmptyStackException) {
            break;
        }
    }
    return solutions;
}

enum MenuOption { FIND_ONE_SOLUTION = 1, FIND_ALL_SOLUTIONS, EXIT };

int main() {
    int board[ROW][COL] = { 0 };
    MenuOption choice;
    int input;

    while (true) {
        cout << "1. Find One Solution\n2. Find All Solutions\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> input;
        choice = static_cast<MenuOption>(input);

        switch (choice) {
        case FIND_ONE_SOLUTION: {
            memset(board, 0, sizeof(board));
            cout << "Finding one solution...\n";
            solveQueen(board, false);
            break;
        }
        case FIND_ALL_SOLUTIONS: {
            memset(board, 0, sizeof(board));
            cout << "Finding all solutions...\n";
            int totalSolutions = solveQueen(board, true);
            cout << "Total solutions: " << totalSolutions << endl;
            break;
        }
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}