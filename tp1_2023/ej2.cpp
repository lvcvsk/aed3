#include <iostream>
#include <vector>

using namespace std;

long long mod(long long n, long long m){
    if (n>=0){
        return n%m;
    } else {
        return (n%m)+m;
    }
}

long long modPot(long long a, long long b, long long m)
{
    if (b == 0)
        return 1;
    long long res = modPot(a, b / 2, m);
    if (b % 2==0) {
        return ((res * res) % m);
    }
    else {
        long long res1 = ((((res * res) % m) * a) % m);
        return res1;
    }
}


bool hayOperacion(long long r, long long m, vector<long long>& numeros, long long resultado, long long i, vector<vector<long long>>& memo) {
    if (i == numeros.size()) {
        return (resultado == r);
        //return memo[resultado][i];
    } else {
        if (memo[i][resultado] == -1) {
            bool res = (hayOperacion(r, m, numeros, mod(resultado + numeros[i],m), i + 1, memo) ||
                        hayOperacion(r, m, numeros, mod(resultado - numeros[i], m), i + 1, memo) ||
                        hayOperacion(r, m, numeros, mod(resultado * numeros[i],m), i + 1, memo) ||
                        hayOperacion(r, m, numeros, modPot(resultado, numeros[i], m), i + 1, memo));
            memo[i][resultado] = res;
            return res;
        } else {
            return memo[i][resultado];
        }
    }
}


int main(){
    long long c,m,r,n;
    cin>> c;
    vector<long long> resultado(c);
    for (long long i = 0; i < c; ++i) {
        cin>> n >> r >> m;
        vector<long long> numeros(n);
        for (long long j = 0; j < n; ++j) {
            cin>>numeros[j];
        }
        vector<vector<long long>> memo(n, vector<long long>(m, -1));
        resultado[i] = hayOperacion(r, m, numeros, numeros[0], 1, memo);
        numeros.clear();
    }
    for (long long i = 0; i < c; ++i) {
        if(resultado[i]==1){
            cout << "Si" <<endl;
        } else {
            cout<< "No" << endl;
        }
    }
    return 0;
}