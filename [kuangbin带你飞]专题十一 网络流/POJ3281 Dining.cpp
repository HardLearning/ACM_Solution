#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int INF  = 1e9;
const int maxn = 500;
struct Edge{
   int from,to,cap,flow;
};

int N,F,D;

struct Dinic{
   int n,m,s,t;
   vector<Edge> edges;
   vector<int> G[maxn];
   bool vis[maxn];
   int d[maxn];
   int cur[maxn];
   #define pb push_back

   void init(){
      s = 0; t = F+2*N+D+1;
      for (int i=s; i<=t; i++) G[i].clear();
      edges.clear();
   }

   void addEdge(int from, int to, int cap){
        edges.pb((Edge){from,to,cap,0});
        edges.pb((Edge){to,from,0,0});
        m = edges.size();
        G[from].pb(m-2);
        G[to].pb(m-1);
   }

   bool BFS(){
      memset(vis,0,sizeof(vis));
      queue<int>que;
      que.push(s);
      d[s] = 0;
      vis[s] = 1;

      int x;
      while (!que.empty()){
          x = que.front();
          que.pop();
          for (int i=0; i<G[x].size(); i++) {
             Edge &e = edges[G[x][i]];
             if (!vis[e.to] && e.cap>e.flow){
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                que.push(e.to);
             }
          }
      }

      return vis[t];
   }

   int DFS(int x, int a){
      if (x == t || a == 0) return a;
      int flow = 0,f;
      for (int& i = cur[x]; i<G[x].size(); i++) {
         Edge &e = edges[G[x][i]];
         if (d[x]+1 == d[e.to] && (f=DFS(e.to,min(a,e.cap-e.flow)))>0 ) {
             flow += f;
             a -= f;
             e.flow += f;
             edges[G[x][i]^1].flow -= f;
             if (a == 0) break;
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

}dinic;


int main(){
    while (scanf("%d%d%d",&N,&F,&D)==3){
        dinic.init();

        int x,y;
        int c;
        for (int i=1; i<=N; i++) {
            scanf("%d %d",&x,&y);
            for (int j=1; j<=x; j++) {
                scanf("%d",&c);
                dinic.addEdge(c,F+i,1);
            }
            dinic.addEdge(F+i,N+F+i,1);
            for (int j=1; j<=y; j++) {
                scanf("%d",&c);
                dinic.addEdge(N+F+i,2*N+F+c,1);
            }
        }
        for (int i=1; i<=F; i++) dinic.addEdge(dinic.s,i,1);
        for (int i=1; i<=D; i++) dinic.addEdge(2*N+F+i,dinic.t,1);

        printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
