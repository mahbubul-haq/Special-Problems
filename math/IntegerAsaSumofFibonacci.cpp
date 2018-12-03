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


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ll fib[93];///int long long range we can hold maximum first 93 fibonacci number

    fib[0]=0,fib[1]=1;
    for(int i=2;i<93;i++){///general process for nth fibonacci
        fib[i]=fib[i-1]+fib[i-2];
    }

    for(int i=2;i<93;i++) cout<<fib[i]<<" ";
    cout<<endl;

    double shi=(1+sqrt(5))/2;

    int n;
    while(cin>>n){
        if(n==-1) break;
        cout<<(ll)((pow(shi,n)-pow(-shi,-n))/sqrt(5))<<endl;///binet's formula for nth fibonacci number..works upto 71
    }

    ///every integer can be written as a sum of non-consecutive fibonacci number!
    ///greedy solution take the biggest fibonacci number at every step

    ll make;
    while(cin>>make){

        for(int i=92;i>0;i--){
            if(fib[i]>make) continue;
            else{
                cout<<fib[i]<<" ";
                make-=fib[i];
            }
            if(make==0) break;
        }
        cout<<endl;
    }

    return 0;
}
