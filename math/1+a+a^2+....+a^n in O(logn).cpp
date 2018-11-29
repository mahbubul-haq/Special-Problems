/*
1+a+a2+a3+a4 + ....+an;
if n==1 return 1+a;
if n is odd: then divide like this..as example for n==5....1+a+a2+a3(1+a+a2)...then
for even;;as example...n==6...1+a(1+a+a2+a3+a4+a5)..
*/

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

long long bigsum(int a,int n){
    if(n==0) return 1L;///if the series is 1
    if(n==1) return 1L+a;
    if(n&1){///n%2==1 n&1 is faster
        return (1L+int(pow(a,n/2+1)))*bigsum(a,n/2);
    }
    else return 1L+a*(bigsum(a,n-1));
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cout<<bigsum(10,17)<<endl;

    return 0;
}
