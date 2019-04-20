// example

#include <iostream>
using namespace std;

void fillTwos(const int rows, const int cols, bool swap) {
    int count = 0;
    int col = 1;
    int row = 1;
    bool doubleAdd = false;

    while (count < rows * cols) {
        if (row > rows) {
            row = 1;
        }
        if (col > cols) {
            // wrap cols around to beginning
            col = col-cols;

            // if cols wrap to same col every time, remember to increment after wrapping cols
            if (col == 1 && count < cols / 2+1) doubleAdd = true;

            // add another col to prevent overlap after wrap
            if (doubleAdd) col++;

            // final square does not fit in patter, located in top left corner
            if (doubleAdd && count == rows*cols-1) {
                    row = 2;
                    col = 1;
                }
        }

        // swap rows and cols if required
        if (!swap) cout << row << " " << col << endl;
        else cout << col << " " << row << endl;

        // move two to the right, and up 1 every time
        // fix wrapping off edges at beginning of loop
        col += 2;
        row ++;

        count ++;
    }
}


void fill(const int rows, const int cols, bool swap) {
    // use different patter for 2xN grids
    if (rows == 2) {
        fillTwos(rows, cols, swap);
        return;
    }

    int count = 0;
    int col = 1;
    int row = 1;
    int startCol = 1;
    bool remReset = false;

    while (count < rows * cols) {
        // for even square grids that aren't 4x4, switch (rows,1) and (rows,2) squares
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

        // wrap around top of grid when greater than 4 rows
        if (row > rows) {
            row = 1;

            // special case for 4x4 grid to prevent same col error when using other square grid pattern
            if (rows == 4 && cols == 4 && startCol == 1) startCol = 3;
            else if (rows == 4 && cols == 4 && startCol == 4) startCol = 2;
            else if (rows == 4 && cols == 4 && startCol == 3) startCol = 1;

            col = startCol+1;
            startCol = col;
        }

        // fill in zig-zag pattern while rising up rows
        // 1,1 then 2,3 then 3,1 then 4,3
        if (row % 2 == 0) {
            col = startCol + 2;
            if (col > cols) {
                col = col - cols;
            }
        }
        else col = startCol;

        // print coords. switch order if required
        if (!swap) cout << row << " " << col << endl;
        else cout << col << " " << row << endl;

        // even square grids > 4x4, reset the swapped values
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
        cin >> r >> c;  // rows and cols

        // swap rows and cols if required so only one fill function required
        bool swap = false;
        if (r > c) {
            swap = true;
            int tmpr = r;
            r = c;
            c = tmpr;
        }

        // check if solvable,
        // min dim of 1 impossible
        // min dim of 2, other dim must be >= 5
        // min dim of 3, other dim must be >= 4
        if (r == 1 ||
            c < 4  ||
            (r == 2 && c < 5)) {
            cout<<"Case #"<<i<<": IMPOSSIBLE" << endl;
            continue;
        }

        // all other cases solvable
        cout<<"Case #"<<i<<": POSSIBLE" << endl;
        fill(r, c, swap);

    }
  return 0;
}
