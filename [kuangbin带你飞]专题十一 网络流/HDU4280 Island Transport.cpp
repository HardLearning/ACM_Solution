#include <cstdio>
using namespace std;

const int maxn = 100000+5;
const int INF = 1e9;

inline int Max(int x, int y) { return x>y?x:y; }
inline int Min(int x, int y) { return x<y?x:y; }

struct Edge{
   int from,to,cap,nxt;
};

struct Dinic{
   int n,m,s,t,tot;
   Edge edges[maxn*2];
   int head[maxn];
   int d[maxn];
   int cur[maxn];
   int que[maxn*2];
   bool vis[maxn];

   void init(int s, int t, int N){
      this->s = s;
      this->t = t;
      n = N;
      tot = 0;
      for (int i=0; i<=n; i++) head[i] = -1;
   }

   void addEdge(int from, int to, int cap){
       edges[tot++] = ((Edge){from,to,cap,head[from]});
       edges[tot++] = ((Edge){to,from,cap,head[to]});
       head[from] = tot-2;
       head[to] = tot-1;
   }

   bool BFS(){
       int p=0,q=1;

       que[p] = s;
       for (int i=1; i<=n; i++) vis[i] = 0;
       d[s] = 0;
       vis[s] = 1;

       int x;
       while (p<q){
          x = que[p];
          p++;
          for (int i=head[x]; i!=-1; i=edges[i].nxt) {
             Edge& e = edges[i];
             if (!vis[e.to] && e.cap){
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                que[q] = e.to;
                q++;
             }
          }
       }
       return vis[t];
   }

   int DFS(int x, int a){
      if (x==t || a==0) return a;
      int flow = 0,f;
      for (int& i=cur[x]; i!=-1; i=edges[i].nxt) {
         Edge& e = edges[i];
         if (d[e.to]==d[x]+1 && (f=(DFS(e.to,Min(a,e.cap))))>0 ) {
            flow += f;
            a -= f;
            e.cap -= f;
            edges[i^1].cap += f;
            if (a==0) break;
         }
      }
      return flow;
   }

   int Maxflow(){
      int flow = 0;
      while (BFS()){
        for (int i=0; i<=n; i++) cur[i] = head[i];
        flow += DFS(s,INF);
      }
      return flow;
   }
}dinic;

int n,m;

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d %d",&n,&m);
        int x,y,z;
        int mx=0,mn=INF;
        int s,e;
        for (int i=1; i<=n; i++) {
            scanf("%d %d",&x,&y);
            if (x>mx) { e = i; mx = x;}
            if (x<mn) { s = i; mn = x;}
        }

        dinic.init(s,e,n);
        while (m--){
           scanf("%d %d %d",&x,&y,&z);
           dinic.addEdge(x,y,z);
        }
        printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
