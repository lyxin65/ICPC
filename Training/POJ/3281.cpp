// written at 17:27 on 20 Jan 2017 
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <complex>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector> 
#include <utility>
#include <bitset>

#define IOS std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
// #define __DEBUG__
#ifdef __DEBUG__
    #define DEBUG(...) printf(__VA_ARGS__)
#else
    #define DEBUG(...)
#endif
#define filename ""
#define setfile() freopen(filename".in", "r", stdin); freopen(filename".ans", "w", stdout);
#define resetfile() freopen("/dev/tty", "r", stdin); freopen("/dev/tty", "w", stdout); system("more " filename".ans");
#define rep(i, j, k) for (int i = j; i < k; ++i)
#define irep(i, j, k) for (int i = j - 1; i >= k; --i)

using namespace std;

template <typename T>
inline T sqr(T a) { return a * a;};

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int > Pii;

const double pi = acos(-1.0);
const int INF = INT_MAX;
const ll LLINF = LLONG_MAX;
const int MAX_V = 1e3 + 10;

struct edge {int to, cap, rev; };
vector<edge> G[MAX_V];
int V, iter[MAX_V], level[MAX_V];
int F, D, N;

void add_edge(int from, int to, int cap) {
    G[from].push_back(edge{to, cap, (int)G[to].size()});
    G[to].push_back(edge{from, 0, (int)G[from].size() - 1});
}
void bfs(int s) {
    memset(level, -1, sizeof level);
    queue<int> que;
    level[s] = 0; que.push(s);
    while (!que.empty()) {
        int v = que.front(); que.pop();
        rep(i, 0, G[v].size()) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); ++i) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s, int t) {
    int flow = 0;
    for(;;)    {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof iter);
        int f;
        while ((f = dfs(s, t, INF)) > 0)
            flow += f;
    }
    return flow;
}

int main(int argc, char const *argv[])
{
    while (~scanf("%d%d%d", &N, &F, &D)) {
        // 0 ~ N - 1 left cow
        // N ~ 2N - 1 right cow
        // 2N ~ 2N + F - 1 food
        // 2N + F ~ 2N + F + D - 1 drink
        int s = F + D + 2 * N, t = s + 1;
        rep(v, 0, t + 1) G[v].clear();
        int n, m, a;
        rep(j, 0, F) add_edge(s, j + 2 * N, 1);
        rep(j, 0, D) add_edge(j + 2 * N + F, t, 1);
        rep(i, 0, N) {
            scanf("%d%d", &n, &m);
            rep(j, 0, n) {
                scanf("%d", &a); --a;
                add_edge(a + 2 * N, i, 1);
            }
            rep(j, 0, m) {
                scanf("%d", &a); --a;
                add_edge(i + N, a + 2 * N + F, 1);
            }
            add_edge(i, i + N, 1);
        }
        printf("%d\n", max_flow(s, t));
    }
    return 0;
}