#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef vector<int> vi;

#define MAX_V 40
#define INF 1000000000

int res[MAX_V][MAX_V], mf, f, s, t;                           // global variables
// mf for max flow, s for source, t for sink, f for current flow
vi p;

void augment(int v, int minEdge) {     // traverse BFS spanning tree from s to t
    if (v == s) {
        f = minEdge;    // record minEdge in a global variable f
        return;
    } else if (p[v] != -1) {
        augment(p[v], min(minEdge, res[p[v]][v])); // recursive
        res[p[v]][v] -= f; res[v][p[v]] += f;
    }

    // think about when v != s but p[v] == -1
}

int main() {
    int V, k, vertex, weight;

    scanf("%d %d %d", &V, &s, &t);

    memset(res, 0, sizeof res);
    for (int i = 0; i < V; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d %d", &vertex, &weight);
            res[i][vertex] = weight;
        }
    }

    mf = 0;                                              // mf stands for max_flow
    while (1) {              // O(VE^2) (actually O(V^3E) Edmonds Karp's algorithm
        f = 0;
        // run BFS, compare with the original BFS shown in Section 4.2.2
        vi dist(MAX_V, INF); dist[s] = 0; queue<int> q; q.push(s);

        /*
            ##########################
            dist is the distance to source. Initially, all elements in dist are INF
            ##########################
        */

        p.assign(MAX_V, -1);           // record the BFS spanning tree, from s to t!
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;      // immediately stop BFS if we already reach sink t
            for (int v = 0; v < MAX_V; v++)                 // note: this part is slow
                if (res[u][v] > 0 && dist[v] == INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
        }
        /*
        print out bfs spanning tree information
        cout << ".........." << endl;
                for (int i = 0; i < V; ++i) {
                    cout << dist[i] << " ";
                }
                cout << endl;

                for (int i = 0; i < V; ++i) {
                    cout << p[i] << " ";
                }
                cout << endl;
        cout << ".........." << endl;
        */
        augment(t, INF);     // find the min edge weight `f' along this path, if any

        if (f == 0) break;      // we cannot send any more flow (`f' = 0), terminate
        mf += f;                 // we can still send a flow, increase the max flow!
    }

    printf("%d\n", mf);                              // this is the max flow value

    return 0;
}
