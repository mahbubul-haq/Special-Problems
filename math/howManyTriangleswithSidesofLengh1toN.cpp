#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<long,long>
#define vi vector<int>
#define vii vector<pii>
#define vll vector<ll>
#define MOD 1000000007
#define EPS 1e-7
#define mem(x,y) memset(x,y,sizeof x)
#define INF 1e9
#define ff(i,a,b) for(int i=(a);i<=(b);i++)
#define fb(i,a,b) for(int i=(a);i>=(b);i--)
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())
#define debugx(x) cout<<"WTH! "<<x<<endl
#define debug(x,y) cout<<x<<" "<<y<<endl

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ///SOURCE and concept: http://ojsolver.blogspot.com/2016/07/uva-11401-triangle-counting-tutorial.html

    int n;

    ///the sides are of 1 to n length.
    ///how many triangle with them can be made..

    ///precalculation:

    ll ans[100007], add[100007];

    ans[3]=add[3]=0;
    int var=0;

    for(int i=4;i<=100000;i++){///this loop calculates for all input n. and saves
            ///them to ans

        if(i&1){
            add[i]=add[i-1]+var;
            ans[i]=ans[i-1]+add[i];
        }
        else{
            var++;
            add[i]=add[i-1]+var;
            ans[i]=ans[i-1]+add[i];
        }

    }

    while(cin>>n&&n>=3){///input and get ans!

        cout<<ans[n]<<endl;

    }

    return 0;
}
