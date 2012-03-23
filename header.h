#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>

#define rep(i, a, b) for( int i = (a); i < (b); i++ )
#define foreach(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)

using namespace std;

vector<string> split(const string &str) {
    vector<string> res;
    if (str.size() == 0)
        return res;

    int i = 0;
    while (i < str.size() && !isalpha(str[i]))
        i++;
    while (i < str.size()) {
        int j = i;
        while (i < str.size() && isalpha(str[i]))
            i++;
        res.push_back(str.substr(j, i - j));
        while (i < str.size() && !isalpha(str[i]))
            i++;
    }

    return res;
}