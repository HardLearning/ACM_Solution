#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define pb push_back
const int INF = 1e9;
const int maxn = 800+10;
int N,F,D;

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
   int m,s,t;
   vector<Edge>edges;
   vector<int>G[maxn];
   int d[maxn];
   int cur[maxn];
   bool vis[maxn];

   void init(int n){
      s = 0;
      t = n+1;
      edges.clear();
      for (int i=s; i<=t; i++) G[i].clear();
   }

   void addEdge(int from, int to, int cap){
      edges.pb((Edge){from,to,cap,0});
      edges.pb((Edge){to,from,0,0});
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

       int x;
       while (!que.empty()){
           x = que.front();
           que.pop();
           for (int i=0; i<G[x].size(); i++) {
              Edge& e = edges[G[x][i]];
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
      if (x==t || a==0) return a;
      int flow = 0, f;
      for (int& i=cur[x]; i<G[x].size(); i++) {
         Edge& e = edges[G[x][i]];
         if (d[e.to]==d[x]+1 && (f=DFS(e.to,min(a,e.cap-e.flow)))>0 ){
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

}dinic;

int main(){
    char s[maxn];
    while (scanf("%d%d%d",&N,&F,&D)!=EOF){
       dinic.init(2*N+F+D);

       int x;
       for (int i=1; i<=F; i++) {
           scanf("%d",&x);
           dinic.addEdge(dinic.s,i,x);
       }

       for (int i=1; i<=D; i++) {
           scanf("%d",&x);
           dinic.addEdge(F+2*N+i,dinic.t,x);
       }

       for (int i=1; i<=N; i++) {
          scanf("%s",s+1);
          for (int j=1; j<=F; j++)
            if (s[j]=='Y') dinic.addEdge(j,F+i,1);
       }

       for (int i=1; i<=N; i++) {
          scanf("%s",s+1);
          for (int j=1; j<=D; j++)
            if (s[j]=='Y') dinic.addEdge(N+F+i,2*N+F+j,1);
       }

       for (int i=1; i<=N; i++) dinic.addEdge(F+i,N+F+i,1);

       printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
