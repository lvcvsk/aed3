#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main(){};

int magicSum(int n) {
    return (n * n * (n * n + 1)) / 2 / n;
}

bool validate(unordered_map<int, int>& sumDict, int n) {
    for (auto& kv : sumDict) {
        if (kv.second > magicSum(n)) {
            return false;
        }
    }
    return true;
}

bool check(unordered_map<int, int>& sumDict, int n) {
    for (auto& kv : sumDict) {
        if (kv.second != magicSum(n)) {
            return false;
        }
    }
    return true;
}

bool isValid(vector<vector<int>>& m, int n) {
    unordered_map<int, int> rowSum, colSum, diagSum;
    bool isLeft = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] == 0) {
                isLeft = true;
            }
            rowSum[i] += m[i][j];
            colSum[j] += m[i][j];
            if (i == j) {
                diagSum[0] += m[i][j];
            }
            if (i + j == n - 1) {
                diagSum[n - 1] += m[i][j];
            }
        }
    }
    if (isLeft) {
        return validate(rowSum, n) && validate(colSum, n) && validate(diagSum, n);
    } else {
        return check(rowSum, n) && check(colSum, n) && check(diagSum, n);
    }
}

vector<vector<int>> next(int cur, vector<vector<int>>& m, int n) {
    vector<vector<int>> possible;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] == 0) {
                vector<vector<int>> nextM = m;
                nextM[i][j] = cur;
                if (isValid(nextM, n)) {
                    possible.push_back(nextM);
                }
            }
        }
    }
    return possible;
}

void printM(vector<vector<int>>& m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<vector<int>>> gen(int n) {

    vector<vector<int>> startM(n, vector<int>(n, 0)); // matriz vacia

    vector<vector<vector<int>>> magic;  //vector de matrices magic

    queue<pair<int, vector<vector<int>>>> Q;  // cola de entero, matriz q

    Q.push({1, startM});   // push matriz vacia, 1

    while (!Q.empty()) {
        auto state = Q.front();
        Q.pop();
        int cur = state.first;
        vector<vector<int>> m = state.second;
        if (cur == n * n + 1) {
            magic.push_back(m);
            printM(m);
            continue;
        }
        for (auto& w : next(cur, m, n)) {
            Q.push({cur + 1, w});
        }
    }
    return magic;
}

int main() {
    vector<vector<vector<int>>> magic = gen(3);
    return 0;
}