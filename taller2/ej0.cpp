#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>

using namespace std;
enum {WHITE, GREY, BLACK};
int n, m;
vector<vector<int>> D;
vector<vector<int>> D_T;

void dfs_initial(int v, vector<int> &status, stack<int> &s){
    status[v] = GREY;
    for(int u : D[v]){
        if(status[u]==WHITE) dfs_initial(u, status, s);
    }
    status[v] = BLACK;
    s.push(v);
}

void dfs_transpose(int v, vector<int> & status_transpose){
    status_transpose[v] = GREY;
    for(int u : D_T[v]){
        if(status_transpose[u]==WHITE) dfs_transpose(u, status_transpose);
    }
    status_transpose[v] = BLACK;
}

int main() {
    while (true) {
        cin >> n >> m;
        if (n+m==0) break;

        map<string,int> name_to_index;
        
        string line; getline(cin, line);
        for (int i=0; i<n; i++) {getline(cin, line); name_to_index[line] = i;}
        
        D.assign(n, vector<int>(0)); D_T.assign(n, vector<int>(0));

        for (int j=0; j<m; j++) {
            string from, to;
            getline(cin, from); getline(cin, to);
            D[name_to_index[from]].push_back(name_to_index[to]);
            D_T[name_to_index[to]].push_back(name_to_index[from]);
        }
        vector<int> status(n,WHITE);
        stack<int> s;
        vector<int> status_transpose(n,WHITE);
        for(int i=0;i<n;i++){if(status[i]==WHITE)dfs_initial(i,status,s);}
        int i=0;
        while(!s.empty()){
            int x = s.top(); s.pop();
            if(status_transpose[x]==WHITE){dfs_transpose(x,status_transpose); i++;}
        }

        printf("%d\n", i);    
    }

    return 0;
}
