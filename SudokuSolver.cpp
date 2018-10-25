// Sudoku solver <3

#include <cstdio>
#include <iostream>

using namespace std;

typedef pair<int, int> pii;

char arr[9][9];
bool isFixed[9][9];

// Checks if an arrangement of numbers is valid
bool check(int i, int j) {
    for (int k = 0; k < 9; k++) {
        if ((k != j && arr[i][k] == arr[i][j]) || (k != i && arr[k][j] == arr[i][j])) {
            return false;
        }
    }
    int i0 = i / 3 * 3, j0 = j / 3 * 3;
    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
            if ((i0 + k != i || j0 + l != j) && arr[i0 + k][j0 + l] == arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

pii getPos(int n) {
    return {n / 9, n % 9};
}

int main() {
    
    for (int i = 0; i < 9; i++) {
        scanf("%s", arr[i]);
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (arr[i][j] != '0') {
                isFixed[i][j] = true;
            }
        }
    }
    
    // Backtracking
    int pos = 0;
    while (pos < 81) {
        pii x = getPos(pos);
        if (!isFixed[x.first][x.second]) {
            arr[x.first][x.second]++;
            if (arr[x.first][x.second] > '9') {
                // If out of possibilities for this tile, go back
                arr[x.first][x.second] = '0';
                do {
                    pos--;
                    x = getPos(pos);
                } while (isFixed[x.first][x.second]);
            } else if (check(x.first, x.second)) {
                // Else, if the partial solution is valid, go forward
                pos++;
            }
        } else {
            // If this tile is already fixed, go forward
            pos++;
        }
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
