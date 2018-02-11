#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int maxn = 100+10;

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
   int m,s,t;
   vector<Edge>edges;
   vector<int>G[maxn];
   bool vis[maxn];
   int d[maxn];
   int cur[maxn];
   #define pb push_back

   void init(int n){
      s = 0; t = n+1;
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

      int u;
      while (!que.empty()){
          u = que.front();
          que.pop();
          for (int i=0; i<G[u].size(); i++) {
             Edge& e = edges[G[u][i]];
             if (!vis[e.to] && e.cap>e.flow){
                vis[e.to] = 1;
                d[e.to] = d[u] + 1;
                que.push(e.to);
             }
          }
      }
      return vis[t];
   }

   int DFS(int x, int a){
     if (x==t || a==0) return a;
     int flow = 0, f;
     for (int& i=cur[x]; i<G[x].size(); i++){
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

int n,np,nc,m;

int main(){
    while (scanf("%d%d%d%d",&n,&np,&nc,&m)==4){
        dinic.init(n);

        int u,v,z;
        char c;
        while (m--){
            c = '!';
            while (c!='(') c = getchar();
            scanf("%d,%d)%d",&u,&v,&z);
            u++;
            v++;
            dinic.addEdge(u,v,z);
        }

        while (np--){
            c = '!';
            while (c!='(') c = getchar();
            scanf("%d)%d",&u,&z);
            u++;
            dinic.addEdge(dinic.s,u,z);
        }

        while (nc--){
            c = '!';
            while (c!='(') c = getchar();
            scanf("%d)%d",&u,&z);
            u++;
            dinic.addEdge(u,dinic.t,z);
        }

        printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
