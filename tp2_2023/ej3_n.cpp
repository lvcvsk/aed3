#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <chrono>
#include <cmath>

using namespace std;

int n,w,u,v;
long double r;
vector<tuple<long double, int, int>> E;
vector<tuple<long double,long double>> coordenadas;
vector<tuple<long double,long double> > resultados;

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if (u > v) padre[v] = padre[u];
        else
            padre[u] = padre[v];
    }

    vector<int> padre;
    vector<int> rank;
};

tuple<long double,long double> kruskal(){
    long double costo_utp= 0;
    long double costo_fibra= 0;
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(n);

    for(auto e : E){
        long double dist = get<0>(e);
        int x = get<1>(e);
        int y = get<2>(e);
        if(w== n-aristas)
            break;
        //si (u,v) es arista segura
        if(dsu.find(x) != dsu.find(y)){
            // agregar
            dsu.unite(x,y);
            aristas++;
            if(dist<=r){
                costo_utp += dist * static_cast<long double>(u);
            }
            else
                costo_fibra+= dist * static_cast<long double>(v);
        }
    }
    return {costo_utp,costo_fibra};
}

//Distancia entre dos puntos
long double distancia(tuple<long double,long double> p1, tuple<long double,long double> p2){
    long double deltaX = get<0>(p1) - get<0>(p2);
    long double deltaY = get<1>(p1) - get<1>(p2);
    long double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

int main(int argc, char** argv) {
    if (argc < 2){
        return 0;
    }
    char *txt = argv[1];
    ofstream outfile;
    outfile.open(txt, ios_base::app);
    outfile << "n,time\n";
    
    int c; // casos de test
    cin>> c;
    for(int i=0; i<c ;i++){ 
        cin>>n;     //cantidad de nodos
        cin>>r; 
        cin>>w;     //cantidad de modems
        cin>>u;    //costo por metro de UTP 
        cin>>v;    //costo por metro de fibra óptica
        coordenadas.clear();
        E.clear();

        //creo mi vector de aristas y sus costos

        //implemento kruskal, guardar los valores para imprimirlos al final
        //auto start = chrono::high_resolution_clock::now();

        for(int i=0; i<n ;i++){
            long double a,b; long double dist;
            cin>>a>>b;
            coordenadas.push_back({a,b});
            for(int j=0; j<coordenadas.size()-1;j++){
                dist= distancia(coordenadas[coordenadas.size()-1], coordenadas[j]);
                E.push_back({dist,i,j});
            }
        }
        auto start = chrono::high_resolution_clock::now();
        resultados.push_back(kruskal());

        auto diff = chrono::high_resolution_clock::now() - start;
	    auto t1 = chrono::duration_cast<chrono::microseconds>(diff);
        outfile << n << "," << t1.count() << endl;
    }

    for(int i=0; i<resultados.size() ; i++){
        cout<<"Caso #"<<i+1<<": "<< fixed << setprecision(3)<< get<0>(resultados[i])<<" "<<get<1>(resultados[i])<<endl;
    }
    
    return 0;
}