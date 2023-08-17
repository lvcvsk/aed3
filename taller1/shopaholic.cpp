#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Completar

int f(int i, int j, vector<int>& v) {
    if (j < 2) {return 0;}
    return v[i] + f(i-3,j-3,v);
}

int main() {
    int c; cin >> c;

    while (c--) {
        vector<int> v;
        int n, temp; cin >> n;
        for(int i = 0; i < n;i++){
            cin >> temp;
            v.push_back(temp);
        }
        std::sort(v.begin(), v.end());
        int acum = 0;
        acum = f(n-3,n-1,v);
        cout << acum << endl;
    }

    return 0;
}
