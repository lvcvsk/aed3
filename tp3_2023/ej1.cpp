#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>

using namespace std;
const int INF = 10000000;

int n, m, k, s, t;

vector<vector<tuple<int, int>>> gs, gs_inv;
vector<tuple<int, int, int>> calles;

vector<int> dist_s;
vector<int> dist_t;

void printDist(vector<int>& v){
    cout << "v: ";
    for (int i = 1; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void dijkstra(vector<vector<tuple<int,int>>>& g, int s, vector<int>& d){
    d[s] = 0;
    vector<bool> visited(n + 1, false);
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
    pq.push({0, s});

    while(!pq.empty()){
        int u = get<1>(pq.top());
        pq.pop();

        if(visited[u]){
            continue;
        }
        visited[u] = true;

        for(auto p : g[u]){
            int v = get<0>(p);
            int c = get<1>(p);

            if(d[u] + c < d[v]){
                d[v] = d[u] + c;
                pq.push({d[v], v});
            }
        }
    }
}


int main(){
    int c;
    cin >> c;
    while(c--){
        cin >> n >> m >> k >> s >> t;

        gs.clear();
        gs_inv.clear();
        gs.resize(n + 1);
        gs_inv.resize(n + 1);

        dist_s.assign(n + 1, INF);
        dist_t.assign(n + 1, INF);

        for (int i = 0; i < m; i++){
            int u, v, c;
            cin >> u >> v >> c;
            gs[u].push_back({v, c});
            gs_inv[v].push_back({u, c});
        }

        dijkstra(gs, s, dist_s);
        dijkstra(gs_inv, t, dist_t);
        int res = dist_s[t];
        
        for(int i = 0; i < k; i++){
            int u, v, c;
            cin >> u >> v >> c;
            res = min(res, min(dist_s[u] + c + dist_t[v], dist_s[v] + c + dist_t[u]));
        }

        if(res == INF){
            cout << -1 << endl;
        }else{
            cout << res << endl;
        }
    }
}