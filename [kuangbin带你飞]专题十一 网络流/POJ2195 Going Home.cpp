#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int maxm = 400;
const int INF = 1e9;
const int maxn = 100+5;
int n,m;
char s[maxn][maxn];

struct Edge{
   int from,to,cap,flow,cost;
};

struct MCMF{
   int n,m,s,t;
   vector<Edge>edges;
   vector<int>G[maxm];
   int d[maxm];
   int inq[maxm];
   int p[maxm];
   int a[maxm];
   #define pb push_back

   void init(int N){
      edges.clear();
      s = 0;
      t = 2*N+1;
      n = t+1;
      for (int i=s; i<=t; i++) G[i].clear();
   }

   void addEdge(int from, int to, int cap, int cost){
       edges.pb((Edge){from,to,cap,0,cost});
       edges.pb((Edge){to,from,0,0,-cost});
       m = edges.size();
       G[from].pb(m-2);
       G[to].pb(m-1);
   }

   bool BellmanFord( int &flow, int &cost){
        for (int i=0; i<n; i++) d[i] = INF;
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
            for (int i=0; i<G[u].size(); i++){
                Edge &e = edges[G[u][i]];
                if (e.cap>e.flow && d[e.to]>d[u]+e.cost){
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u],e.cap-e.flow);
                    if (!inq[e.to]) {
                        que.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }

        if (d[t]==INF) return 0;
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

   int Mincost(){
      int flow = 0,cost = 0;
      while (BellmanFord(flow,cost));
      return cost;
   }
}mcmf;

struct Point{
   int x,y;
};
vector<Point>p1,p2;

int main(){
    while (scanf("%d%d",&n,&m)==2 && n+m){
        for (int i=0; i<n; i++) scanf("%s",s[i]);
        p1.clear();
        p2.clear();

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (s[i][j]=='m') p1.push_back((Point){i,j});
                else if (s[i][j]=='H') p2.push_back((Point){i,j});
            }
        }

        int sz = p1.size();
        mcmf.init(sz);
        for (int i=1; i<=sz; i++) mcmf.addEdge(mcmf.s,i,1,0),mcmf.addEdge(sz+i,mcmf.t,1,0);
        for (int i=0; i<sz; i++) {
            for (int j=0; j<sz; j++) {
                int w = abs(p1[i].x-p2[j].x) + abs(p1[i].y-p2[j].y);
                mcmf.addEdge(i+1,sz+j+1,1,w);
            }
        }
        printf("%d\n",mcmf.Mincost());
    }
    return 0;
}
