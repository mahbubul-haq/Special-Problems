#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second
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
#define EPS 1e-12
#define mem(x,y) memset(x,y,sizeof x)
#define INF 100000000
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())
#define FASTIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define PI acos(-1.0)
#define FI freopen("in.txt","r",stdin)
#define FO freopen("out.txt","w",stdout)
#define debug(x) cout<<"WTH: "<<x<<endl

template<class T>
class compare{
public:
    bool operator()(pair<T,T> x,pair<T,T> y){
        if(x.first==y.first){
            return x.ss>y.ss;
        }
        return x.ff>y.ff;
    }
};

template<class T>
ostream& operator<<(ostream &os,const pair<T,T> &a){
    os<<a.ff<<" "<<a.ss;
}
template<class T>
void print(vector<T> vec){
    for(int i=0;i<vec.size();i++) cout<<vec[i]<<" "; cout<<endl;
}

template<class T> pair<T,T> operator+(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff+b.ff,a.ss+b.ss}; }
template<class T> pair<T,T> operator-(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff-b.ff,a.ss-b.ss}; }
template<class T> pair<T,T> operator*(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff*b.ff,a.ss*b.ss}; }
template<class T> pair<T,T> operator%(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff%b.ff,a.ss%b.ss}; }
template<class T,class U> pair<T,T> operator+(const pair<T,T> &a,const U &b){ return { a.ff+b,a.ss+b}; }
template<class T,class U> pair<T,T> operator*(const pair<T,T> &a,const U &b){ return { a.ff*b,a.ss*b}; }

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================///

int max_zero_mat(vvi matrix){
    int ans=0;
    int n=matrix.size();
    int m=matrix[0].size();

    vi d(m,-1),d1(m),d2(m);
    stack<int> stk;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]>0){
                d[j]=i;
            }
        }

        for(int j=0;j<m;j++){
            while(!stk.empty()&&d[stk.top()]<=d[j]){
                stk.pop();
            }

            d1[j]=stk.empty()? -1: stk.top();
            stk.push(j);
        }

        while(!stk.empty()) stk.pop();

        for(int j=m-1;j>=0;j--){
            while(!stk.empty()&&d[stk.top()]<=d[j]){
                stk.pop();
            }

            d2[j]=stk.empty()? m: stk.top();
            stk.push(j);
        }

        while(!stk.empty()) stk.pop();

        for(int j=0;j<m;j++){
            ans=max(ans,(i-d[j])*(d2[j]-d1[j]-1));
        }
    }

    return ans;
}

int main()
{
    //FI;FO;
    FASTIO;

    int n,m;

    cin>>n>>m;

    vvi matrix(n);

    for(int i=0;i<n;i++){
        matrix[i].resize(m);
        for(int j=0;j<m;j++){
            cin>>matrix[i][j];
        }
    }

    cout<<max_zero_mat(matrix)<<endl;

    return 0;
}
