#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using matriz = vector<vector<int>>;
int numeroMagico;

bool esCuadradoMagico(matriz& grid, int n) {
    // Chequear si una matriz terminada es cuadrado magico
    for (int i = 0; i < n; i++) {
        int fil_sum = 0;
        int col_sum = 0;
        for (int j = 0; j < n; j++) {
            fil_sum += grid[i][j];
            col_sum += grid[j][i];
        }
        if (fil_sum != numeroMagico || col_sum != numeroMagico) {
            return false;
        }
    }
    int diagonal_sum1 = 0;
    int diagonal_sum2 = 0;
    for (int i = 0; i < n; i++) {
        diagonal_sum1 += grid[i][i];
        diagonal_sum2 += grid[i][n - 1 - i];
    }
    if (diagonal_sum1 != numeroMagico || diagonal_sum2 != numeroMagico) {
        return false;
    }
    return true;
}

void backtrack(matriz& grid, int n, int fil, int col, vector<matriz>& matrix_list, vector<int>& posibles, vector<int>& sumaAcumulada, int diag, int diagInv) {
    // Caso base: la matriz esta llena
    if (fil == n && col == 0) {
        //if (esCuadradoMagico(grid, n)) {
            matrix_list.push_back(grid);
        //}
    } else {
        // Llenar la proxima celda
        int next_fil, next_col;
        if (col == n - 1) {
            next_fil = fil + 1;
            next_col = 0;
        } else {
            next_fil = fil;
            next_col = col + 1;
        }
        // Probar todos los valores posibles
        for (int i = 1; i <= n * n; i++) {
            if (posibles[i] == 1) {
                if (fil == col) // diagonal
                {
                    if (n - 1 == fil){ // final de la diagonal
                        if (diag + i != numeroMagico){continue;}
                    }
                    else{
                        if (diag + i > numeroMagico){continue;}
                    }
                }
                if (fil == n - 1 - col) // diag Inversa
                {
                    if (n - 1 == fil){ // final de la diag inversa
                        if (diagInv + i != numeroMagico){continue;}
                    }
                    else{
                        if (diagInv + i > numeroMagico){continue;}
                    }
                }

                if (col == n - 1){
                    if (sumaAcumulada[fil] + i != numeroMagico){continue;}
                }
                else{
                    if (sumaAcumulada[fil] + i > numeroMagico){continue;}
                }
                if (fil == n - 1){
                    if (sumaAcumulada[col + n] + i != numeroMagico){continue;}
                }
                else{
                    if (sumaAcumulada[col + n] + i > numeroMagico){continue;}
                }

                // Llenar la celda, actualizar los acumuladores
                grid[fil][col] = i;
                posibles[i] = 0;
                sumaAcumulada[fil] = sumaAcumulada[fil] + i;
                sumaAcumulada[col + n] = sumaAcumulada[col + n] + i;
                if(fil == col){
                    diag = diag + i;
                }
                if(fil == n - 1 - col){
                    diagInv = diagInv + i;
                }

                backtrack(grid, n, next_fil, next_col, matrix_list, posibles, sumaAcumulada, diag, diagInv);

                // vuelvo y actualizo las estructuras
                posibles[i] = 1;
                grid[fil][col] = 0;

                sumaAcumulada[fil] = sumaAcumulada[fil] - i;
                sumaAcumulada[col + n] = sumaAcumulada[col + n] - i;
                if(fil == col) {diag = diag - i;}
                if (fil == n - 1 - col){diagInv = diagInv - i;}
            }
        }
    }
}


vector<matriz> get_magic_squares(int n) {
    // Inicializo matriz de 0s
    vector<matriz> matrix_list;
    matriz grid(n, vector<int>(n, 0));
    vector<int> posibles((n*n)+ 1, 1);
    // vector sumaAcumulada donde
    vector<int> sumaAcumulada((n*n), 0);
    backtrack(grid, n, 0, 0, matrix_list, posibles, sumaAcumulada, 0, 0);
    return matrix_list;
}

bool compare_matrices(const matriz& A, const matriz& B) {
    int fils = A.size(), cols = A[0].size();
    for (int i = 0; i < fils; i++) {
        for (int j = 0; j < cols; j++) {
            if (A[i][j] < B[i][j]) {
                return true;
            } else if (A[i][j] > B[i][j]) {
                return false;
            }
        }
    }
    return false; // A y B son iguales
}

void printMatriz(matriz& M){
    int size = M.size();
    for(int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n,k;
    cin >> n >> k;
    vector<matriz> matrix_list;
    numeroMagico =  ((n*n*n) + n)/2;
    matrix_list = get_magic_squares(n);
    if (k > matrix_list.size()) {
        cout<< -1;
    } else {
    //sort(matrix_list.begin(), matrix_list.end(), compare_matrices);
    matriz matrix_res = matrix_list[k - 1];
    printMatriz(matrix_res);
    }
    return 0;
}