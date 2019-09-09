#include <bits/stdc++.h>
using namespace std;

#define dist2D(x1,y1,x2,y2)         ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2)   ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define EPS                         1e-16
#define endl                        "\n"
#define FastIO                      ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt","r",stdin)
#define FO                          freopen("out.txt","w",stdout)
#define fap(x)                      cout<<"WTH: "<<x<<endl
#define ff                          first
#define fof(i,x,y)                  for(int i=x;i<(int)y;i++)
#define fob(i,x,y)                  for(int i=x;i>=(int)y;i--)
#define INF              1000000000000000000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x,y,sizeof x)
#define mp                          make_pair
#define msi                         map<string,int>
#define mii                         map<int,int>
#define mis                         map<int,string>
#define MOD                         1000000007
#define PI                          acos(-1.0)
#define PQ                          priority_queue
#define pb                          push_back
#define pib                         pair<int,bool>
#define pii                         pair<int,int>
#define pll                         pair<ll,ll>
#define sfi(x)                      scanf("%d",&x)
#define sfii(x,y)                   scanf("%d%d",&x,&y)
#define sfiii(x,y,z)                scanf("%d%d%d",&x,&y,&z)
#define siz(x)                      (int)x.size()
#define sortv(v)                    sort(v.begin(),v.end())
#define ss                          second
#define timeTaken                   endd=clock();cout<<(double)(endd-beginn)/CLOCKS_PER_SEC*1000<<endl
#define timeInit                    clock_t beginn=clock(),endd
#define ull                         unsigned long long
#define umsi                        unordered_map<string,int>
#define umii                        unordered_map<int,int>
#define umis                        unordered_map<int,string>
#define vb                          vector<bool>
#define vi                          vector<int>
#define vvi                         vector<vi>
#define vii                         vector<pii>
#define vvii                        vector<vii>
#define vll                         vector<ll>
#define vvll                        vector<vll>
#define vpll                        vector<pll>

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

//os.order_of_key(v): returns how many elements strictly less than v
//os.find_by_order(k-1): returns kth smallest element's iterator
*/

template<class T> class compare{
public:
    bool operator()(pair<T,T> &x,pair<T,T> &y){
        if(x.first==y.first){
            return x.ss>y.ss;
        }
        return x.ff>y.ff;
    }
};

//template<class T> ostream& operator<<(ostream &os,const pair<T,T> &a) { os<<a.ff<<" "<<a.ss; }
ll power(ll a,int b) {
    ll po = 1;
    while (b) {
        if (b & 1)
            po *= a;
        a *= a;
        b >>= 1;
    }
    return po;
}

template<class T> pair<T,T> operator+(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff+b.ff,a.ss+b.ss}; }
template<class T> pair<T,T> operator-(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff-b.ff,a.ss-b.ss}; }
template<class T> pair<T,T> operator*(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff*b.ff,a.ss*b.ss}; }
template<class T> pair<T,T> operator%(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff%b.ff,a.ss%b.ss}; }
template<class T,class U> pair<T,T> operator+(const pair<T,T> &a,const U &b){ return { a.ff+b,a.ss+b}; }
template<class T,class U> pair<T,T> operator*(const pair<T,T> &a,const U &b){ return { a.ff*b,a.ss*b}; }

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos); }
bool check(ll N,int pos){  return (bool) (N&(1LL<<pos)); }

///=======================================template=======================================///

/// Source : CP-Algorithms

/******* symmetry rule:
 * nCr = nC(n - r)
 *
 ******* factoring:
 * nCr = (n / r) * (n - 1)C(r - 1);
 *
 ******* sum over r:
 * nC0 + nC1 + nC2 + ... + nCn = 2 ^ n;
 *
 ******* sum over n:
 * 0Cr + 1Cr + 2Cr + ... + nCr = (n + 1)C(r + 1);
 * ==> rCr + (r + 1)Cr + ... + nCr = (n + 1)C(r + 1);/// application of nCr = (n - 1)Cr + (n - 1)C(r - 1)
 * ==> after subtracting the values of left side one by one from right side value and using this law we get 0
 *
 ******* sum over n and k:
 * nC0 + (n + 1)C1 + (n + 2)C2 + ... + (n + m)Cm = (n + m + 1)Cm
 * the same process as sum over n
 *
 ******* sum of the squares:
 * C0 ^ 2 + C1 ^ 2 + C2 ^ 2 + ... + Cn ^ 2 = (2 * n)Cn (HSC)
 *
 ******* Weighted sum:
 * 1 * nC1 + 2 * nC2 + 3 * nC3 + ... + n * nCn = n * 2 ^ (n - 1)
 *
 * connection with fibonacci numbers:
 * nC0 + (n - 1)C1 + (n - 2)C2 + ... + 0Cn = F(n+1)
 */
ll mod = 1000000007;

ll bigmod(ll a, ll b, ll m) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll nCr1(int n, int r) {
    ld res = 1; /// long double can hold > 1500!
    for(int i = 1; i <= r; i++){
        res = res * (n - r + i) / i;/// res should be integer every time
    }
    return (ll)(res + 0.05); // for precision loss
}

ll nCr2(int n, int r) { /// for small n ~ 1000 this can handle nCr % MOD where MOD can be any value
    ll nCr[n + 1][n + 1];
    nCr[0][0] = 1, nCr[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        nCr[i][0] = nCr[i][i] = 1;
        for (int j = 1; j < i; j++) {
            nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]);
        }
    }
    return nCr[n][r];
}
const int maxn = 1000006;
ll fact[maxn], factinv[maxn];

void pre() {
    fact[0] = 1;
    for(int i = 1; i < maxn; i++){
        fact[i] = i * fact[i - 1] % mod;
    }
    factinv[maxn - 1] = bigmod(fact[maxn - 1], mod - 2, mod);
    for(int i = maxn - 2; i >= 0; i--){
        factinv[i] = factinv[i + 1] * (i + 1) % mod;
    }
}

ll nCr3(int n, int r){/// complexity O(1) if pre-calculated
    pre();
    return fact[n] * factinv[n - r] % mod * factinv[r] % mod;
}
/*
/// nCr % m; where m = p ^ b and p is prime but p <= max(n - r, r) - that is a barrier to modular inverse

void pre(vector<pair<pll,ll > > &gc, ll &p, int &n, ll &m) {
    gc[0].ff.ff = 1, gc[0].ss = 0, gc[0].ff.ss = 1;

    for (int i = 1; i <= n; i++) {
        int now = i;
        gc[i].ss = gc[i - 1].ss;

        while (now % p == 0) {
            now /= p;
            gc[i].ss++;
        }

        gc[i].ff.ff = gc[i - 1].ff.ff * now;
        //gc[i].ff.ss = gc[i - 1].ff.ss * bigmod(now, m - 2, m);
    }
}

ll nCr4(int n, int r, ll p, int b) {/// Postponed.
    ll m = power(p, b);
    vector<pair<pll, ll > >gc(n + 1, {{0, 0}, 0});  /// g(x) = x! / p ^ c; p ^ c | x!
    pre(gc, p, n, m);

    for(auto v: gc){
        cout << v.ff.ff << " " << v.ff.ss << " " << v.ss << endl;
    }

    ll ans = 0, po = gc[n].ss - gc[r].ss - gc[n - r].ss;

    if (po < b) {
        ans = (gc[n].ff.ff * bigmod(gc[r].ff.ff, m - 2, m) % m * bigmod(gc[n - r].ff.ff, m - 2, m) % m * power(p, po)) % m;
    }
    return ans;
}*/

int main() {
    //FI;//FO;
    FastIO;//timeInit;

    cout << nCr1(5,3) << " " << nCr2(5,3) << " " << nCr3(5,3) << endl;
    cout << nCr1(10, 5) << " " << nCr2(10, 5) << " " << nCr3(10, 5) << endl;
    cout << nCr1(40, 27) << " " << nCr2(40, 27) << " " << nCr3(40, 27) << endl;
    cout << nCr1(5,2) << " " << nCr2(5,2) << " " << nCr3(5,2) << endl;
    cout << nCr1(8, 5) << " " << nCr2(8, 5) << " " << nCr3(8, 5) << endl;
    cout << nCr1(6, 2) << " " << nCr2(6, 2) << " " << nCr3(6, 2) << endl;

    //timeTaken;
    return 0;
}
