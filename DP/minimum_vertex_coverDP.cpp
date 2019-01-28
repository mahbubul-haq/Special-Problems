#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pii>
#define vvii vector<vii>
#define vll vector<ll>
#define vpll vector<pll>
#define MOD 1000000007
#define EPS 1e-8
#define mem(x,y) memset(x,y,sizeof x)
#define INF 1e9
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())
#define FASTIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define PI acos(-1.0)
//#define FIFO
#define FI freopen("in.txt","r",stdin)
#define FO freopen("out.txt","w",stdout)

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};

ostream& operator<<(ostream &os,const pll &a){
    os<<a.first<<" "<<a.second;
}

pll operator+(const pll &a, const ll &b){ return { a.first+b,a.second+b };}
pll operator*(const pll &a,const ll &b){ return {a.first*b,a.second*b};}
pll operator+(const pll &a,const pll &b){ return {a.first+b.first,a.second+b.second};}
pll operator-(const pll &a,const pll &b){ return { a.first-b.first,a.second-b.second};}
pll operator*(const pll &a,const pll &b){ return {a.first*b.first,a.second*b.second};}
pll operator%(const pll &a,const pll &b){ return {a.first%b.first,a.second%b.second};}

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================///

vvi adjLst;
int dp[100005][2];
int parent[100005];

int ret(int u,int isGuard){
    if(adjLst[u].size()==0) return 1;

    if(dp[u][isGuard]!=-1) return dp[u][isGuard];

    int sum=0;

    for(int i=0;i<adjLst[u].size();i++){
        int v=adjLst[u][i];
        if(v!=parent[u]){
            parent[v]=u;

            if(!isGuard) sum+=ret(v,1);
            else sum+=min(ret(v,1),ret(v,0));
        }
    }

    return dp[u][isGuard]=sum+isGuard;
}

int main()
{
#ifdef FIFO
    FI;
    FO;
#endif
    FASTIO;
    
    int v,e;
    cin>>v>>e;

    adjLst.assign(v+1,vi());
    mem(dp,-1);

    for(int i=1;i<=e;i++){
        int u,v; cin>>u>>v;
        adjLst[v].pb(u);
        adjLst[u].pb(v);
    }

    parent[1]=-1;
    int ans=min(ret(1,0),ret(1,1));

    cout<<ans<<endl;

    return 0;
}
