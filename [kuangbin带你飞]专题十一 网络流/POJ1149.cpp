#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
const int maxn = 100+10;
const int maxm = 1000+10;
const int INF = 1e9;

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
   vector<Edge>edges;
   vector<int>G[maxn];
   int m,s,t;
   int d[maxn];
   int cur[maxn];
   bool vis[maxn];

   void init(int n){
      s = 0; t = n+1;
      edges.clear();
      for (int i=s; i<=t; i++) G[i].clear();
   }

   void add(int from, int to, int cap){
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
         for (int i=0; i<G[u].size(); i++){
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

   inline int Min(int x, int y) { return x<y?x:y; }
   int DFS(int x, int a){
      if (x==t || a==0) return a;
      int flow = 0, f;
      for (int& i=cur[x]; i<G[x].size(); i++) {
          Edge& e = edges[G[x][i]];
          if (d[e.to]==d[x]+1 && (f=DFS(e.to,Min(a,e.cap-e.flow)))>0 ) {
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

int m,n;
int a[maxm];
int cnt[maxn];
vector<int>pig[maxm];
int x,k,B;

int main(){
    while (scanf("%d%d",&m,&n)==2){
        for (int i=1; i<=m; i++) scanf("%d",&a[i]),pig[i].clear();
        memset(cnt,0,sizeof(cnt));
        dinic.init(n);

        for (int i=1; i<=n; i++) {
            scanf("%d",&x);
            while (x--){
                scanf("%d",&k);
                pig[k].pb(i);
            }
            scanf("%d",&B);
            dinic.add(i,dinic.t,B);
        }

        for (int i=1; i<=m; i++) if (pig[i].size()) cnt[pig[i][0]] += a[i];
        for (int i=1; i<=n; i++) dinic.add(dinic.s,i,cnt[i]);
        for (int i=1; i<=m; i++) if (pig[i].size()) {
             for (int j=0; j<pig[i].size()-1; j++) dinic.add(pig[i][j],pig[i][j+1],INF);
        }

        printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
