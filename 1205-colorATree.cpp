#include <cstring>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

class Prioritize {
public:
    int operator() ( const pair<int, unsigned int> &p1,
                     const pair<int, unsigned int> &p2 ) {
        return p1.second < p2.second;
    }
};


int tree[1000][1000];
int cost[1000];

int main() {

    int n, r;

    while (cin >> n && cin >> r && n && r) {
        memset(tree, 0, sizeof(tree));
        memset(cost, 0, sizeof(cost));

        r--;
        for (int i = 0; i < n; ++i) {
            cin >> cost[i];
        }
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            cin >> x >> y;
            tree[--x][--y] = 1;
        }

        priority_queue < pair< int, unsigned int >, vector <pair< int, unsigned int > >, Prioritize > pq;
        pq.push(make_pair(r, cost[r]));
        
        int total = 0;
        int time = 0;
        while (!pq.empty()) {
            time++;
            pair<int, unsigned int> p = pq.top();
            pq.pop();
            int at = p.first;
            cout << at << endl;
            int c = p.second;
            total += time * c;
            for (int i = 0; i < n; ++i) {
                if (tree[at][i])
                    pq.push(make_pair(i, cost[i]));
            }
        }

        cout << total << endl;
    }


    return 0;
}