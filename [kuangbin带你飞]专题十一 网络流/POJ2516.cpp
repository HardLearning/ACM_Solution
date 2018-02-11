#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
const int INF = 1e9;
struct Edge{
   int from,to,cap,flow,cost;
};

const int maxn = 100+10;
bool flag;

const int maxm = 55;
int N,M,K;
int shop[maxm][maxm];
int supply[maxm][maxm];
int a[maxm][maxm];

struct MCMF{
    int m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    int inq[maxn];
    int d[maxn];
    int p[maxn];
    int a[maxn];

    void init(int n){
       s = 0; t = n+1;
       edges.clear();
       for (int i=s; i<=t; i++) G[i].clear();
    }

    void addEdge(int from, int to, int cap, int cost){
       edges.pb((Edge){from,to,cap,0,cost});
       edges.pb((Edge){to,from,0,0,-cost});
       m = edges.size();
       G[from].pb(m-2);
       G[to].pb(m-1);
    }

    bool BellmanFord(int &flow, int &cost){
       for (int i=s; i<=t; i++) d[i] = INF;
       memset(inq,0,sizeof(inq));
       d[s] = 0;
       inq[s] = 1;
       p[s] = 0;
       a[s] = INF;

       queue<int>que;
       que.push(s);
       int u;
       while (!que.empty()){
          u = que.front();
          que.pop();
          inq[u] = 0;
          for (int i=0; i<G[u].size(); i++) {
             Edge& e = edges[G[u][i]];
             if (e.cap>e.flow && d[e.to]>d[u]+e.cost){
                d[e.to] = d[u] + e.cost;
                p[e.to] = G[u][i];
                a[e.to] = min(a[u],e.cap-e.flow);
                if (!inq[e.to]) {que.push(e.to); inq[e.to] = 1;}
             }
          }
       }

       if (d[t] == INF) return 0;
       flow += a[t];
       cost += d[t]*a[t];
       u = t;
       while (u!=s){
         edges[p[u]].flow += a[t];
         edges[p[u]^1].flow -= a[t];
         u = edges[p[u]].from;
       }
       return 1;
    }

    int Mincost(int kth){
       int flow = 0, cost = 0;
       while (BellmanFord(flow,cost));
       int sum = 0;
       for (int i=1; i<=N; i++) sum += shop[i][kth];
       if (flow<sum) flag = 0;
       return cost;
    }

}mcmf;

int main(){
    while (scanf("%d%d%d",&N,&M,&K)==3){
       if (N==0 && M==0 && K==0) break;
       flag = 1;

       for (int i=1; i<=N; i++)
         for (int j=1; j<=K; j++)
            scanf("%d",&shop[i][j]);

       for (int i=1; i<=M; i++)
         for (int j=1; j<=K; j++)
            scanf("%d",&supply[i][j]);

        int ans = 0;
       for (int kase=1; kase<=K; kase++){
           for (int i=1; i<=N; i++)
             for (int j=1; j<=M; j++)
                scanf("%d",&a[i][j]);
           if (!flag)  continue;

           mcmf.init(N+M);
           for (int i=1; i<=M; i++) mcmf.addEdge(mcmf.s,i,supply[i][kase],0);
           for (int i=1; i<=N; i++) mcmf.addEdge(M+i,mcmf.t,shop[i][kase],0);
           for (int j=1; j<=M; j++) {
              for (int i=1; i<=N; i++) mcmf.addEdge(j,M+i,supply[j][kase],a[i][j]);
           }

           ans += mcmf.Mincost(kase);
       }
          if (!flag) printf("-1\n"); else printf("%d\n",ans);
    }
    return 0;
}
