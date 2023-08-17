#include <iostream>

using namespace std;

// Completar
int mod_bin_exp(int x, int y, int n) { 
    int res;
    if (y == 0){ 
        return 1;
        }
    if (y%2 == 0){
        res = mod_bin_exp(x,y/2,n);
        res *= res;
        res = res % n;
        return res;
        }
    if (y%2 == 1){ 
        res = mod_bin_exp(x,y/2,n);
        res *= res;
        res = res % n;
        res *= x;
        res = res % n;
        return res;
        }
}


int main() {
    int c; cin >> c;

    while (c--) {
        int x, y, n; cin >> x >> y >> n;
        cout << mod_bin_exp(x, y, n) << endl;
    }

    return 0;
}