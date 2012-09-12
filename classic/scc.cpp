#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#define NUM_NODES 1000

using namespace std;

int n;                              // actual number of nodes
int dfs_counter;                    // initial value 0
int scc_counter;                    // initial value 0
int vis[NUM_NODES];                 // 0 for unvisited, 1 for visited
int graph[NUM_NODES][NUM_NODES];    // adjacent matrix of graph, 0 & 1
int dfs_num[NUM_NODES];             // initial value 0
int dfs_low[NUM_NODES];             // initial value 0
vector<int> s;                      // a stack to store scc

void initialize() {
    memset(graph, 0, sizeof(graph));
    memset(dfs_low, 0, sizeof(dfs_low));
    memset(dfs_num, 0, sizeof(dfs_num));
    memset(vis, 0, sizeof(vis));
    s.clear();
    dfs_counter = scc_counter = 0;
}

void dfs_scc(int u) {
    dfs_low[u] = dfs_num[u] = ++dfs_counter;
    s.push_back(u);
    vis[u] = 1;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!vis[v])                            // never been visited
                dfs_scc(v);
            if (dfs_num[v] != 0)                    // have been visited and not "released"
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
    }

    if (dfs_low[u] == dfs_num[u]) {                 // root of scc
        printf("SCC %d:", ++scc_counter);

        while (1) {
            int v = s.back(); s.pop_back();
            printf(" %d(%d, %d)", v, dfs_num[v], dfs_low[v]);
            dfs_num[v] = 0;                         // crucial step, "release" node v, don't consider v for updating
            if (u == v)
                break;
        }

        cout << endl;
    }
}

int main(int argc, char const *argv[]) {
    initialize();

    n = 8;
    graph[0][1] = graph[1][3] = graph[3][2] = graph[2][1] = graph[3][4] = graph[4][5] = graph[5][7] = graph[7][6] = graph[6][4] = 1;

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs_scc(i);
        }
    }

    return 0;
}