#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Completar

int mochila(vector<int>& beneficio, vector<int>& peso, int capacidad, int i, int n, int suma){
    if (i == n){return suma;}
    
}

int main() {
    int c; cin >> c;

    while (c--) {
        int n; cin >> n;
        vector<int> precio, peso, capacidades;
        int temp;
        for(int i = 0; i < n; i++){
            cin >> temp; precio.push_back(temp);
            cin >> temp; peso.push_back(temp);
        }
        int m; cin >> m;
        for(int i = 0; i < m; i++){
            cin >> temp; capacidades.push_back(temp);
        }
        int acum = 0;
        for (int i = 0; i < m;i++){
            acum += mochila(precio,peso,capacidades[i],0,n,0);
        }
        cout << acum << endl;
    }

    return 0;
}
