#include <iostream>
#include <cmath>

using namespace std;

constexpr int MAX_ROWS = 8;
constexpr int MAX_COLS = 8;

int ROWS, COLS;
int R1, C1, R2, C2, R3, C3;
int CHECK1, CHECK2, CHECK3;
int RES;

int MARKED[MAX_ROWS][MAX_COLS] = {0};

int SeDivideEn2(int x, int y) {
    int res = 0;
    int vecindario[8];
    vecindario[0] = x-1 < 0     || y-1 < 0        || MARKED[x-1][y-1];
    vecindario[1] = x-1 < 0     || MARKED[x-1][y];
    vecindario[2] = x-1 < 0     || y+1 >= COLS    || MARKED[x-1][y+1];
    vecindario[3] = y+1 >= COLS || MARKED[x][y+1];
    vecindario[4] = x+1 >= ROWS || y+1 >= COLS    || MARKED[x+1][y+1];
    vecindario[5] = x+1 >= ROWS || MARKED[x+1][y];
    vecindario[6] = x+1 >= ROWS || y-1 < 0        || MARKED[x+1][y-1];
    vecindario[7] = y-1 < 0     || MARKED[x][y-1];
    vecindario[8] = vecindario[0];

    for (int i = 0; i < 8; i++) { 
        if (vecindario[i] != vecindario[i+1]) { res++; } 
    } 

    return res >= 4;
}

void DFS(int i, int j, int steps) {
    /* Pase antes de lo esperado por un check point? */
    if (steps < CHECK1 && MARKED[R1][C1])  { return; }
    if (steps < CHECK2 && MARKED[R2][C2])  { return; }
    if (steps < CHECK3 && MARKED[R3][C3])  { return; }
    if (steps < ROWS*COLS && MARKED[0][1]) { return; }

    /* Podas por check in */
    if (steps == CHECK1 && (i != R1 || j != C1))  { return; }
    if (steps == CHECK2 && (i != R2 || j != C2))  { return; }
    if (steps == CHECK3 && (i != R3 || j != C3))  { return; }
    if (steps == ROWS*COLS) {
        if (i == 0 && j == 1) { RES++; }
        return;
    }

    /* Podas por distancia manhattan */
    if (steps < CHECK1 && (steps + abs(i-R1) + abs(j-C1) > CHECK1)) { return; } 
    if (steps < CHECK2 && (steps + abs(i-R2) + abs(j-C2) > CHECK2)) { return; } 
    if (steps < CHECK3 && (steps + abs(i-R3) + abs(j-C3) > CHECK3)) { return; } 
    if (steps < ROWS*COLS && (steps + abs(i-0) + abs(j-1) > ROWS*COLS)) { return; } 

    /* Poda que se fija si la matriz se me divide en 2 */
    if (SeDivideEn2(i,j)) { return; }

    /* Me preparo para DFS sobre los adyacentes a i,j */
    MARKED[i][j] = 1;

    /* Solo hago DFS sobre los adyacentes validos? */
    if (i+1 < ROWS && !MARKED[i+1][j]) { DFS(i+1,j  ,steps+1); } 
    if (i-1 >= 0   && !MARKED[i-1][j]) { DFS(i-1,j  ,steps+1); }
    if (j+1 < COLS && !MARKED[i][j+1]) { DFS(i  ,j+1,steps+1); }
    if (j-1 >= 0   && !MARKED[i][j-1]) { DFS(i  ,j-1,steps+1); }

    MARKED[i][j] = 0;
}


int main() {
    int n_case = 0;
    while (1) {
        cin >> ROWS >> COLS;
        if (ROWS == 0 && COLS == 0) { break; }
        n_case++;
        cin >> R1 >> C1;
        cin >> R2 >> C2;
        cin >> R3 >> C3;
        CHECK1 = (ROWS*COLS)/4; 
        CHECK2 = (ROWS*COLS)/2;
        CHECK3 = (3*ROWS*COLS)/4;
        RES = 0;
        DFS(0,0,1);
        cout << "Case " << n_case << ": " << RES << endl;
    }

    return 0;
}
