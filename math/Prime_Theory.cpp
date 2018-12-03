///to learn theories see: Halim's CP3 mathematics Section

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

vi primes;
bitset<10000010> isPrime;
int numOfDivisors=1;///count number of divisors of n
ll sumOfDivisors=1;

void sieve(int n){
    int limit=sqrt(n)+1;
    isPrime.set();

    isPrime[0]=isPrime[1]=0;
    for(int i=4;i<=n;i+=2) isPrime[i]=0;
    primes.pb(2);

    for(int i=3;i<=n;i+=2){
        if(isPrime[i]){
            primes.pb(i);
            if(i<=limit){

                for(int j=i*i;j<=n;j+=i) isPrime[j]=0;

            }
        }
    }
}

vi primeFactors(ll n){
    vi factors;
    int primecnt=0,pf=primes[primecnt];


    while(pf*pf<=n){
        int cnt=0;
        while(n%pf==0){ n/=pf; factors.push_back(pf);cnt++;}///takes same prime factor multiple times

        sumOfDivisors*=((ll)pow((double)pf,cnt+1.0)-1)/(pf-1);

        pf=primes[++primecnt];
        numOfDivisors*=(cnt+1);

    }


    if(n!=1) {
        factors.push_back(n);
        numOfDivisors*=2;

        sumOfDivisors*=(n*n-1)/(n-1);
    }

    return factors;
}

int EulerPhi(ll n){///same as prime factors
    int primecnt=0, pf=primes[primecnt];
    int coprimecnt=n;

    while(pf*pf<=n){
        if(n%pf==0) coprimecnt-=coprimecnt/pf;
        while(n%pf==0) n/=pf;
        pf=primes[++primecnt];
    }
    if(n!=1) coprimecnt-=coprimecnt/n;
    return coprimecnt;
}


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    sieve(10000007);///generate primes

    ll n; cin>>n;

    vi primefactors=primeFactors(n);

    for(int i=0;i<primefactors.size();i++ ) cout<<primefactors[i]<<" ";
    cout<<endl;

    cout<<numOfDivisors<<endl;///total number of divisors of n
    cout<<sumOfDivisors<<endl;///sum of all distinct divisors

    int coprimen=EulerPhi(n);///euler phi counts the number of coprimes of n from 1 to n-1.
    cout<<coprimen<<endl;

    return 0;
}
