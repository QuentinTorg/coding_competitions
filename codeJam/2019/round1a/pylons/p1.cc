// example

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

void fillTwosMod(const int, const int, bool);

void fillTwos(const int rows, const int cols, bool swap) {
    if ((cols-2)%4 == 0) {
        fillTwosMod(rows, cols, swap);
        return;
    }
    vector<pair<int, int>> visitedVec;
    int count = 0;
    int col = 1;
    int row = 1;
    int prevCol = 100;
    int prevRow = 3;
    bool shift = false;

    while (count < rows * cols) {
        if (row > rows) {
            row = 1;
        }
        if (col > cols) {
            col = col-cols;
            if (cols % 4 == 0) {
                col++;
                if (count == rows*cols-1) {
                    col = 1;
                    row = 2;
                }
            }
        }

        if (!swap) cout << row << " " << col << endl;
        else cout << col << " " << row << endl;

        pair<int, int> lastVisit(row, col);
        // check if valid
        if (prevCol == col ||
                prevRow == row ||
                row - col == prevRow - prevCol ||
                row + col == prevRow + prevCol ||
                std::find(visitedVec.begin(), visitedVec.end(), lastVisit) != visitedVec.end()) {
            cout << "using twos" << endl;
            cout << "ERROR for " << rows << "x" << cols << endl;
            cout << "prevRow=" << prevRow << " prevCol=" << prevCol << endl;
            cout << "row=" << row << " col=" << col << endl;
            throw runtime_error("invalid!");
        }

        visitedVec.push_back(lastVisit);

        prevRow = row;
        prevCol = col;

        col += 2;
        row ++;

        count ++;
    }
}


void fillTwosMod(const int rows, const int cols, bool swap) {
    vector<pair<int, int>> visitedVec;
    int count = 0;
    int colOff = 0;
    int row = 1;
    int col = 1;
    int prevCol = 101;
    int prevRow = 3;
    int startCol = 1;
    int sign = 1;

    while (count < rows * cols) {
        if (row > rows) {
            row = 1;
        }

        col = startCol+colOff;
        if (col > cols) {
            if (startCol == 3) sign = -1;
            startCol += sign;
            colOff = 0;
            col = startCol+colOff;
        }


        if (!swap) cout << row << " " << col << endl;
        else cout << col << " " << row << endl;

        pair<int, int> lastVisit(row, col);
        // check if valid
        if (prevCol == col ||
                prevRow == row ||
                row - col == prevRow - prevCol ||
                row + col == prevRow + prevCol ||
                std::find(visitedVec.begin(), visitedVec.end(), lastVisit) != visitedVec.end()) {
            cout << "using twosMod" << endl;
            cout << "ERROR for " << rows << "x" << cols << endl;
            cout << "prevRow=" << prevRow << " prevCol=" << prevCol << endl;
            cout << "row=" << row << " col=" << col << endl;
            throw runtime_error("invalid!");
        }

        visitedVec.push_back(lastVisit);

        prevRow = row;
        prevCol = col;

        colOff += 2;
        row ++;

        count ++;
    }
}

void fill(const int rows, const int cols, bool swap) {

    vector<pair<int, int>> visited;

    if (rows == 2) {
        fillTwos(rows, cols, swap);
        return;
    }
    int count = 0;
    int col = 1;
    int row = 1;
    int startCol = 1;
    int prevCol = 2;
    int prevRow = 3;
    bool remReset = false;

    while (count < rows * cols) {
        if (rows == cols &&
                rows % 2 == 0 &&
                rows != 4) {
            if (count == rows * cols - 1) {
                startCol = cols-1;
            }
            else if (row == rows && col == cols - 1) {
                remReset = true;
                startCol ++;
            }
        }

        if (row > rows) {
            row = 1;
            if (rows == 4 && cols == 4 && startCol == 1) startCol = 3;
            else if (rows == 4 && cols == 4 && startCol == 4) startCol = 2;
            else if (rows == 4 && cols == 4 && startCol == 3) startCol = 1;
            col = startCol+1;
            startCol = col;
        }

        if (row % 2 == 0) {
            col = startCol + 2;
            if (col > cols) {
                col = col - cols;
            }
        }
        else col = startCol;


        if (!swap) cout << row << " " << col << endl;
        else cout << col << " " << row << endl;

        pair<int, int> lastVisit(row, col);
        // check if valid
        if (prevCol == col ||
                prevRow == row ||
                row - col == prevRow - prevCol ||
                row + col == prevRow + prevCol ||
                std::find(visited.begin(), visited.end(), lastVisit) != visited.end()) {
            cout << "ERROR for " << rows << "x" << cols << endl;
            cout << "prevRow=" << prevRow << " prevCol=" << prevCol << endl;
            cout << "row=" << row << " col=" << col << endl;
            throw runtime_error("invalid!");
        }

        visited.push_back(lastVisit);

        prevRow = row;
        prevCol = col;

        if (remReset) {
            remReset = false;
            startCol --;
        }
        row ++;
        count ++;

    }

}




int main() {
    int t, r, c;
    cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

    for (int i = 1; i <= t; ++i) {
        cin >> r >> c;  // read n and then m.

        bool swap = false;
        if (r > c) {
            swap = true;
            int tmpr = r;
            r = c;
            c = tmpr;
        }

        // check if solvable, get num of 3s and 2s
        if (r == 1 ||
            c < 4  ||
            (r == 2 && c < 5)) {
            cout<<"Case #"<<i<<": IMPOSSIBLE" << endl;
            continue;
        }

        cout<<"Case #"<<i<<": POSSIBLE" << endl;
        fill(r, c, swap);

    }
  return 0;
}
