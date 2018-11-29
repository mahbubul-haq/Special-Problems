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
#define MAX 4e18
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

vector< vi > AdjLst,SCC,AdjLst1;

vi dfs_num,dfs_low,Stack,topsort,inwhichSCC;
vector<bool> visited;
int times,SCCcount=0;

//sample graph intput
/*
 1. 4 0

 2.
 4 4
 0 3
 1 3
 2 3
 3 0

 3.
 8 7
 1 2
 3 1
 2 3
 5 1
 7 6
 0 1
 6 0

 */

void dfs(int u){
    visited[u]=true;
    int siz=AdjLst1[u].size();

    for(int i=0;i<siz;i++){
        int v=AdjLst1[u][i];
        if(!visited[v]) dfs(v);
    }

    topsort.push_back(u);
}

void tarjan_SCC(int u){
    dfs_num[u]=dfs_low[u]=++times;
    visited[u]=true;
    Stack.push_back(u);
    int siz=AdjLst[u].size();

    for(int i=0;i<siz;i++){
        int v=AdjLst[u][i];

        if(dfs_num[v]==-1) tarjan_SCC(v);
        if(visited[v]) dfs_low[u]=min(dfs_low[u],dfs_low[v]);
    }

    if(dfs_low[u]==dfs_num[u]){
        vi temp;
        while(true){
            int v=Stack.back(); Stack.pop_back(); visited[v]=false;
            temp.push_back(v);
            inwhichSCC[v]=SCCcount;
            if(u==v) break;
        }
        SCCcount++;
        SCC.push_back(temp);
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int V,E;

     cin>>V>>E;
    AdjLst.assign(V,vi());///vertices are numbered from 0

    for(int i=1;i<=E;i++){
        int u,v; cin>>u>>v;
        AdjLst[u].push_back(v);
    }

    ///find SCC(Strongly Connected Components). I used tarjan's algo

    dfs_num.assign(V,-1),dfs_low.assign(V,0),visited.assign(V,false);
    inwhichSCC.assign(V,-1); times=0;

    for(int i=0;i<V;i++) {
        if(dfs_num[i]==-1) tarjan_SCC(i);
    }

    ///now SCCs are found and we can determine in which SCC a vertex is by inwhichSCC

    int siz=SCC.size();

    if(siz==1){
        cout<<"The number of minimum edges needed: "<<0<<endl;///already SC
        return 0;
    }

    ///now make SCCs are new big vertices and determine there AdjLst using inwhichSCC

    AdjLst1.assign(siz,vi());///now vertices are 0 to siz-1;
    vector<bool> indegree1,outdegree1;///these will keep track of indegree0 and outdegree0 vertices
    indegree1.assign(siz,false),outdegree1.assign(siz,false);

    for(int i=0;i<siz;i++){
        int siz1=SCC[i].size();

        for(int j=0;j<siz1;j++){
            int u=SCC[i][j];

            int siz2=AdjLst[u].size();

            for(int k=0;k<siz2;k++){

                if(inwhichSCC[u]!=inwhichSCC[AdjLst[u][k]]){///now the new two vertices have edge from inwhichSCC[u] to inwhichSCC[AdjLst[u][k]]
                    AdjLst1[inwhichSCC[u]].push_back(inwhichSCC[AdjLst[u][k]]);
                    indegree1[inwhichSCC[AdjLst[u][k]]]=true;
                    outdegree1[inwhichSCC[u]]=true;


                }

            }

        }
    }
    int indcnt=0,outcnt=0;

    for(int i=0;i<siz;i++){
        if(!indegree1[i]){
            indcnt++;
        }if(!outdegree1[i]) outcnt++;
    }

    cout<<"Minimum edges needed to make the graph SC: "<<max(indcnt,outcnt)<<endl;

    cout<<"The added edges are: "<<endl;

    visited.assign(siz,false);
    ///first do topological sort to the new graph

    for(int i=0;i<siz;i++) if(!visited[i]) dfs(i);

    ///now new graph is topsorted from the end to the beginning of topsort

    for(int i=siz-1;i>=0;i--){
        if(!outdegree1[topsort[i]]){

            bool flag=false;

            for(int j=i-1;j>=0;j--){
                if(!indegree1[topsort[j]]){
                    cout<<SCC[topsort[i]][0]<<" "<<SCC[topsort[j]][0]<<endl;
                    indegree1[topsort[j]]=true;
                    outdegree1[topsort[i]]=true;
                    flag=true; break;
                }
            }
            if(!flag) {
                for (int j = siz - 1; j >= i + 1; j--) {
                    if (!indegree1[topsort[j]]) {
                        cout << SCC[topsort[i]][0] << " " << SCC[topsort[j]][0] << endl;
                        indegree1[topsort[j]] = true;
                        outdegree1[topsort[i]] = true;
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag){
                cout<<SCC[topsort[i]][0]<<" "<<SCC[topsort[i-1]][0]<<endl;
            }
        }
    }

    for(int i=siz-1;i>=1;i--){
        if(!indegree1[topsort[i-1]]){
            cout<<SCC[topsort[i]][0]<<" "<<SCC[topsort[i-1]][0]<<endl;
        }
    }


    return 0;
}
