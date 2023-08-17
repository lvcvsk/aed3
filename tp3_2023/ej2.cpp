#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int INF = 100000000;
int n, m;

vector<vector<int>> capacity;
vector<vector<int>> adj;

void printAdj(vector<vector<int>> adjList){
    for (int i = 0; i <= n + 1; i++) {
        cout << "Adjacency list of vertex " << i << ": ";
        for (int j : adjList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << "\t";
        }
       cout << endl;
    }
}


int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
       int cur = q.front().first;
       int flow = q.front().second;

       q.pop();

       for (int next : adj[cur])
       {
            if (parent[next] == -1 && capacity[cur][next])
            {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t){
                    return new_flow;}
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main(){
    while(true){
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
        {
            break;
        }

        adj.clear();
        adj.assign(n + 2, vector<int>());
        capacity.clear();
        capacity.assign(n + 2, vector<int>(n+2, 0));

        for (int i = 1; i <= n; i++)
        {
            int tmp;
            scanf("%d", &tmp);
            if (tmp){
                adj[0].push_back(i);
                capacity[0][i] = 1;
            }
            else{
                adj[i].push_back(n + 1);
                capacity[i][n + 1] = 1;
            }
        }

        for (int i = 0; i < m; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            capacity[u][v] = 1;
            adj[v].push_back(u);
            capacity[v][u] = 1;
        }

        //printAdj(adj);
        //printMatrix(capacity);

        printf("%i\n", maxflow(0, n + 1));

    }
}