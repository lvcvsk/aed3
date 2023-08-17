#include <vector>
#include <tuple>
#include <iostream>
#include <chrono>

using namespace std;


int getMax(vector<tuple<int,int,int>>& v){
    int maxVal = get<1>(v[0]);
    int n = v.size();
    for (int i = 0; i < n; i++){
        if (get<1>(v[i]) > maxVal){
            maxVal = get<1>(v[i]);
        }
    }
    return maxVal;
}

void countSort(vector<tuple<int,int,int>>& arr){

    int n = arr.size();
    if (n <= 1){  // no hay nada que ordenar
        return;
    }

    int maxValor = getMax(arr);

    // inicializar el vector para contar y el ordenado
    vector<int> count(maxValor + 1, 0);
    vector<tuple<int,int,int>> res(n);


    //Conteo
    for (int i = 0; i < n; i++){
        count[get<1>(arr[i])]++;
    }

    // Arreglar el indice
    for (int i = 1; i <= maxValor; i++){
        count[i] += count[i - 1];
    }


    // Construir el vector output de forma ordenada
    for (int i = n - 1; i >= 0; i--){
        res[count[get<1>(arr[i])] - 1] = arr[i];
        count[get<1>(arr[i])]--;
    }

    // copiar al vector original
    for (int i = 0; i < n; i++){
        arr[i] = res[i];
    }
}

vector<int> greedy(vector<tuple<int,int,int>>& act, int k) {
    vector<int> actividades;
    if(act.size() > 0){
        actividades.push_back(get<2>(act[k]));
    }
    for (int j = 1; j < act.size(); ++j) {
        if (get<0>(act[j]) >= get<1>(act[k])) {
            actividades.push_back(get<2>(act[j]));
            k = j;
        }
    }
    return (actividades);
}

int main() {
    // Inicializamos vector con actividades
    int n;
    cin >> n;
    vector<tuple<int, int>> actividades(n);
    for (int i = 0; i < actividades.size(); ++i) {
        int start, finish;
        cin >> start >> finish;
        get<0>(actividades[i]) = start;
        get<1>(actividades[i]) = finish;
    }
    vector<tuple<int, int, int>> actTripla;

    //Guardar posicion en el vector original
    for (int i = 0; i < actividades.size(); ++i) {
        tuple<int,int> actStartFinish = actividades[i];
        int firstComponent = get<0>(actStartFinish);
        int secondComponent = get<1>(actStartFinish);
        actTripla.emplace_back(firstComponent, secondComponent, (i + 1));
    }
    
    //auto start = chrono::high_resolution_clock::now();
    countSort(actTripla);
    vector<int> res = greedy(actTripla,0);
    //auto diff = chrono::high_resolution_clock::now() - start;
	//auto t1 = chrono::duration_cast<chrono::microseconds>(diff);
	//cout << "Tomo para una instancia n: " << n << ". " << t1.count() << " ms" << endl;

    cout << res.size();
    cout << "\n";
        for (int i = 0; i < res.size(); i++) {
            cout << res[i] << " ";
        }
    
    return 0;
}
    
