#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
const int INF = 1e9;
const int maxn = 55;
const int maxm = 1000+10;

struct Edge{
   int from,to,cap,flow;
};

bool mark[maxn];

struct Dinic{
   vector<Edge>edges;
   vector<int>G[maxn];
   int m,s,t;
   int d[maxn];
   int cur[maxn];
   bool vis[maxn];

   void init(int n){
       s = 1; t = 2;
       for (int i=1; i<=n; i++) G[i].clear();
       edges.clear();
   }

   void add(int from, int to, int cap){
       edges.pb((Edge){from,to,cap,0});
       edges.pb((Edge){to,from,cap,0});
       m = edges.size();
       G[from].pb(m-2);
       G[to].pb(m-1);
   }

   bool BFS(){
       queue<int>que;
       que.push(s);
       memset(vis,0,sizeof(vis));
       vis[s] = 1;
       d[s] = 0;

       int u;
       while (!que.empty()){
          u = que.front();
          que.pop();
          for (int i=0; i<G[u].size(); i++) {
             Edge&e = edges[G[u][i]];
             if (!vis[e.to] && e.cap>e.flow){
                  vis[e.to] = 1;
                  d[e.to] = d[u] + 1;
                  que.push(e.to);
             }
          }
       }
       return vis[t];
   }

   inline int Min(int x, int y) {return x<y?x:y; }

   int DFS(int x, int a){
      if (x==t || a==0) return a;
      int flow = 0, f;
      for (int& i = cur[x]; i<G[x].size(); i++) {
         Edge& e = edges[G[x][i]];
         if (d[e.to]==d[x]+1 && (f=DFS(e.to,Min(a,e.cap-e.flow)))>0 ){
            flow += f;
            a -= f;
            e.flow += f;
            edges[G[x][i]^1].flow -= f;
            if (a==0) break;
         }
      }
      return flow;
   }

   int Maxflow(){
      int flow = 0;
      while (BFS()){
         memset(cur,0,sizeof(cur));
         flow += DFS(s,INF);
      }
      return flow;
   }

   void Find(){
      memset(mark,0,sizeof(mark));
      queue<int>que;
      que.push(s);
      mark[s] = 1;

      int u;
      while (!que.empty()){
         u = que.front();
         que.pop();
         for (int i=0; i<G[u].size(); i++){
            Edge& e = edges[G[u][i]];
            if (!mark[e.to] && e.cap>e.flow) {
                mark[e.to] = 1;
                que.push(e.to);
            }
         }
      }
   }

}dinic;

int n,m;
int x[maxm],y[maxm],z[maxm];


int main(){
    while (scanf("%d%d",&n,&m)==2 && n+m){
        dinic.init(n);
        for (int i=1; i<=m; i++) scanf("%d%d%d",&x[i],&y[i],&z[i]),dinic.add(x[i],y[i],z[i]);
        dinic.Maxflow();
        dinic.Find();

        for (int i=1; i<=m; i++) {
            if (!mark[x[i]]&&mark[y[i]] || mark[x[i]]&&!mark[y[i]]) printf("%d %d\n",x[i],y[i]);
        }
        printf("\n");
    }
    return 0;
}
