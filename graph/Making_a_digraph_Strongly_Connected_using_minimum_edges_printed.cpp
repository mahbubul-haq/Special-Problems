#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <string>
#include <set>
#include <complex>
#include <map>
#include <unordered_map>
#include <climits>
#include <bitset>
#include <queue>
#include <chrono>
#include <random>
#include <typeinfo>
#include <stack>
#include <list>
using namespace std;

#define all(v)                      v.begin(), v.end()
#define dist2D(x1, y1, x2, y2)            ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define dist3D(x1, y1, z1, x2, y2, z2)    ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2))
#define EPS                         1e-15
#define endl                        "\n"
#define FastIO                      ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt", "r", stdin)
#define FO                          freopen("out.txt", "w", stdout)
#define ff                          first
#define INF              1000000000000000000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x, y, sizeof x)
#define mp                          make_pair
#define msi                         map<string, int>
#define mii                         map<int, int>
#define mis                         map<int, string>
#define MOD                         1000000007
#define PI                          acos(-1.0)
#define PQ                          priority_queue
#define pb                          push_back
#define pib                         pair<int, bool>
#define pii                         pair<int, int>
#define pll                         pair<ll, ll>
#define present(c, x)               ((c).find(x) != (c).end())
#define sfi(x)                      scanf("%d", &x)
#define sfii(x,y)                   scanf("%d %d", &x, &y)
#define sfiii(x,y,z)                scanf("%d %d %d", &x, &y, &z)
#define siz(x)                      (int)x.size()
#define ss                          second
#define sRand                       srand(chrono::steady_clock::now().time_since_epoch().count())
#define timeTaken                   endd = clock(); cout << (double) (endd - beginn) / CLOCKS_PER_SEC * 1000 << endl
#define timeInit                    clock_t beginn = clock(), endd
#define ull                         unsigned long long
#define umsi                        unordered_map<string, int>
#define umii                        unordered_map<int, int>
#define umis                        unordered_map<int, string>
#define vb                          vector<bool>
#define vi                          vector<int>
#define vvi                         vector<vi>
#define vii                         vector<pii>
#define vvii                        vector<vii>
#define vll                         vector<ll>
#define vvll                        vector<vll>
#define vpll                        vector<pll>
#define bug(...)                    cerr << __PRETTY_FUNCTION__ << " - " << __LINE__ << " : (" << #__VA_ARGS__ << ") = ("; _Print(__VA_ARGS__);
template<class T> void _Print(T &&x) { cerr << x << ")" << endl; }
template<class T, class ...S> void _Print(T &&x, S &&...y) { cerr << x << ", "; _Print(y...); }

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
typedef tree<int,null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

//os.order_of_key(v): returns how many elements strictly less than v
//os.find_by_order(k - 1): returns kth smallest element's iterator
*/

template<class T> class compare {
public:
    bool operator() (pair<T, T> &x, pair<T, T> &y) {
        if (x.first == y.first) {
            return x.ss > y.ss;
        }
        return x.ff > y.ff;
    }
};

template<class T> ostream &operator<<(ostream &os, const pair<T, T> &a) { return os << a.ff << " " << a.ss; }
ll power(ll a, int b) {
    ll po = 1;
    while (b) {
        if (b & 1)
            po *= a;
        a *= a;
        b >>= 1;
    }
    return po;
}

template<class T> pair<T, T> operator+(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff + b.ff, a.ss + b.ss}; }
template<class T> pair<T, T> operator-(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff - b.ff, a.ss - b.ss}; }
template<class T> pair<T, T> operator*(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff * b.ff, a.ss * b.ss}; }
template<class T> pair<T, T> operator%(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff % b.ff, a.ss % b.ss}; }
template<class T, class U> pair<T, T> operator+(const pair<T, T> &a, const U &b) { return {a.ff + b, a.ss + b}; }
template<class T, class U> pair<T, T> operator*(const pair<T, T> &a, const U &b) { return {a.ff * b, a.ss * b}; }

int Set(int N, int pos) { return N = N | (1 << pos); }
int reset(int N, int pos){ return N = N & ~ (1 << pos); }
bool check(int N, int pos){ return (bool) (N & (1 << pos)); }

///=======================================template=======================================///

/// source: Halim CP3 4.2.9 Finding Strongly Connected Components (Directed Graph)

vvi g, g1, SCC; ///g, g1 -> adjacency lists
vi dfs_num, dfs_low, topsort, Stack, inWhichSCC;
vb vis, indegree, outdegree;
int n, m, dfs_time, SCCcount;

void tarjan_SCC(int u) {
    vis[u] = true;
    dfs_num[u] = dfs_low[u] = ++dfs_time;
    Stack.pb(u);

    for (auto &v : g[u]) {
        if (dfs_num[v] == INT_MAX)
            tarjan_SCC(v);
        if (vis[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        vi temp;
        int v;
        do {
            v = Stack.back();
            Stack.pop_back(); vis[v] = false;
            temp.pb(v);
            inWhichSCC[v] = SCCcount;
        } while (v != u);
        SCCcount++;
        SCC.pb(temp);
    }
}

void dfs(int u) {
    vis[u] = true;
    for (auto &v : g1[u]) {
        if (!vis[v])
            dfs(v);
    }
    topsort.pb(u);
}

int main() {

    cin >> n >> m;
    g.assign(n, vi());

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
    }

    dfs_num.assign(n, INT_MAX), dfs_low.assign(n, INT_MAX);
    vis.assign(n, false);
    inWhichSCC.resize(n);

    for (int i = 0; i < n; i++) {
        if (dfs_num[i] == INT_MAX)
            tarjan_SCC(i);
    }


    int nn = siz(SCC);

    if (nn == 1) {
        cout << "minimum extra edges : 0" << endl;
        return 0;
    }

    g1.assign(nn, vi());
    indegree.assign(nn, false), outdegree.assign(nn, false);

    for (int u = 0; u < n; u++) {
        for (auto &v : g[u]) {
            if (inWhichSCC[v] != inWhichSCC[u]) {
                g1[inWhichSCC[u]].pb(inWhichSCC[v]);
                indegree[inWhichSCC[v]] = true;
                outdegree[inWhichSCC[u]] = true;
            }
        }
    }

    vis.assign(nn, false);
    for (int i = 0; i < nn; i++) {
        if (!vis[i])
            dfs(i);
    }

    reverse(all(topsort));
    vii ans;

    for (int i = 0; i < nn; i++) {
        int v = topsort[i];
        bool ok = false;

        if (!indegree[v]) {
            for (int j = (i - 1 + nn) % nn; j != i; j = (j - 1 + nn) % nn) {
                if (!outdegree[topsort[j]]) {
                    ans.pb({topsort[j], v});
                    ok = true;
                    indegree[v] = true;
                    outdegree[topsort[j]] = true;
                    break;
                }
            }

            if (!ok) {
                int u = topsort[(i - 1 + nn) % nn];
                ans.pb({u, v});
                indegree[v] = true;
            }
        }
    }

    for (int i = 0; i < nn; i++) {
        if (!outdegree[topsort[i]]) {
            int v = topsort[(i + 1) % nn];
            ans.pb({topsort[i], v});
        }
    }

    cout << "Minimum number of extra edges: " << siz(ans) << endl;
    cout << "Edges are:" << endl;
    for (auto &x : ans) {
        cout << SCC[x.ff][0] << " " << SCC[x.ss][0] << endl;
    }

    return 0;
}
