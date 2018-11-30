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

int ans[]={1,1,2,6,4,2,2,4,2,8};

///source geeksforgeeks(theorem)

int lastnon0digit(int n){
    if(n<10) return ans[n];


    if(((n/10)%10)&1){
        int val=(4*lastnon0digit(n/5)*ans[(n%10)])%10;
        return val;
    }
    else {
        int val=(6*lastnon0digit(n/5)*ans[(n%10)])%10;
        return val;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;

    cout<<lastnon0digit(n)<<endl;

    return 0;
}
