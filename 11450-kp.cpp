#include <iostream>
#include <cstring>

using namespace std;

int price[25][25];
int m;
int c;
int shopping[210][25];

int shop(int money, int n) {
    if (money < 0)
        return -100000000;
    if (n == c)
        return m - money;
    if (shopping[money][n] != -1)
        return shopping[money][n];
    int ans = -100000000;
    for (int i = 1; i <= price[n][0]; i++)
        ans = max(ans, shop(money - price[n][i], n + 1));
    shopping[money][n] = ans;
    return ans;
}

int main(int argc, char const *argv[]) {
    int t = 0;
    cin >> t;
    while (t--) {
        cin >> m >> c;
        for (int i = 0; i < c; ++i) {
            cin >> price[i][0];
            for (int j = 1; j <= price[i][0]; ++j)
                cin >> price[i][j];
        }

        memset(shopping, -1, sizeof(shopping));
        int score = shop(m, 0);
        if (score < 0)
            cout << "no solution" << endl;
        else
            cout << score << endl;
    }
    return 0;
}