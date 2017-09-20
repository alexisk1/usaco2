
/*
ID: alexisk2
PROG: holstein
LANG: C++11
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
 
using namespace std;
 
int main() {
    vector<int> array, sorted;
    freopen("holstein.in", "r", stdin), freopen("holstein.out", "w", stdout);
    int V, v[30], G, g[30][30], best = (1<<21) -1;
    scanf("%d", &V);
    for (int i = 0; i < V; i++)
        scanf("%d", v + i);
    scanf("%d", &G);
    for (int i = 0; i < G; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", g[i] + j);
    for (int m = 0; m < (1 << G); m++) {
        int total[30] = { 0 };
        for (int i = 0; i < G; i++)
            if (m & (1 << i))
                for (int j = 0; j < V; j++)
                    total[j] += g[i][j];
 
        int valid = 1;
        for (int i = 0; i < V; i++)
            valid &= total[i] >= v[i];
        if (valid && __builtin_popcount(m) < __builtin_popcount(best))
            best = m;
 
    }
 
    printf("%d", __builtin_popcount(best));
    for (int i = 0; i < G; i++)
        if (best & (1 << i))
            printf(" %d", i + 1);
    puts("");
 
    return 0;
}

//Belbesy solution
https://belbesy.wordpress.com/
