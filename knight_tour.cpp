#include <iostream>

using namespace std;
struct chessSquare {
    int row = 0;
    int column = 0;
    int mark = 0;
};

template<class t>
class Stack {
    t *arr;
    int top;
public:
    int size;

    Stack(int s = 100) {
        arr = new t[s];
        top = -1;
        size = 0;
    };

    bool isEmpty() {
        return top < 0;
    }

    bool isFull() {
        return top >= 99;
    }

    void push(t value) {
        if (!isFull()) {
            top++;
            arr[top] = value;
            size++;
        }
    }

    t pop() {
        if (!isEmpty()) {
            t temp = arr[top];
            size--;
            top--;
            return temp;
        }
    }

    t Top() {
        if (!isEmpty())
            return arr[top];
    }

};

class knightTour {
    chessSquare chess[9][9];
    int colMove[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int rowMove[8] = {2, -2, -2, 2, 1, -1, -1, 1};
    Stack<chessSquare> tour;
public:
    knightTour(int startRow, int startColumn) {

        chess[startRow][startColumn].row = startRow;
        chess[startRow][startColumn].column = startColumn;
        chess[startRow][startColumn].mark = 1;
        tour.push(chess[startRow][startColumn]);
    }

    int Tour() {

        // Base
        if (isFinished())
            return 1;

        if (tour.isEmpty())
            return 0;

        chessSquare current = tour.Top();

        for (int i = 0; i < 8; i++) {
            chessSquare nextMove = next(current, i);

            if (nextMove.mark != -1) {
                nextMove.mark = 1;
                tour.push(nextMove);
                int a = Tour();
                if (a == 1)
                    return 1;
            }
        }

        current.mark = 0;
        tour.pop();
        return 0;
    }

    chessSquare next(chessSquare current, int i) {
        chessSquare tempo;
        tempo.mark = -1;
        chessSquare *temp = nullptr;
        int tempRow = current.row + rowMove[i];
        int tempCol = current.column + colMove[i];

        if (tempRow >= 0 && tempRow <= 7 && tempCol >= 0 && tempCol <= 7) {
            temp = &chess[tempRow][tempCol];
            temp->row = tempRow;
            temp->column = tempCol;
            if (temp->mark != 1) {
                return *temp;
            }
        }

        return tempo;
    }

    bool isFinished() {
        return tour.size == 64;
    }

    Stack<chessSquare> getTour() {
        return tour;
    }

};

int main() {
    string p;
    int startRow, startColumn;
    cout << "input type :  ( row , col )" << endl;
    cin >> p >> startRow >> p >> startColumn >> p;
    knightTour obj(startRow, startColumn);
    obj.Tour();
    Stack<chessSquare> tmp = obj.getTour();
    Stack<chessSquare> path;
    while (!tmp.isEmpty()) {
        path.push(tmp.pop());
    }
    for (int i = 0; i < 64; ++i) {
        chessSquare temp = path.pop();
        cout << i + 1 << " - " << "( " << temp.row << " , " << temp.column << " )" << endl;
    }
    return 0;
}
