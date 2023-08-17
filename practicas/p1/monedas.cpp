#include <iostream>
#include <vector>

using namespace std;

int monedas(vector<int> B, int i, int j){
    int res;

    if(i == 0){

        return j;
    }
    res = min(monedas(B,i-1,j), monedas(B,i-1,j-B[i]));
    
    return res;
}

int main(){

    cout << "n, j, b" << endl;
    int n, j, input;
    vector<int> B;
    cin >> n >> j;

    //for(int i = 0; i++; i < n){
    //    cin >> input;
    //    B.push_back(input);
    //}
 

    monedas(B,n-1,j);
}