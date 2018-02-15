#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 1000+10;
const int maxm = 100000+10;

struct Edge{
    int to,cap,flow,nxt;
};

struct Dinic{
   Edge edge[maxm*2];
   int head[maxn],tot;
   int d[maxn];
   int cur[maxn];
   bool vis[maxn];
   int n,s,t;

   int que[maxm*2];
   int Head,Tail;

   void init(int s, int t, int n){
      this->s = s; this->t = t; this->n = n;
      memset(head,-1,sizeof(head));
      tot = 0;
   }

   void add(int from, int to, int cap){
      edge[tot] = (Edge){to,cap,0,head[from]};
      head[from] = tot++;
      edge[tot] = (Edge){from,0,0,head[to]};
      head[to] = tot++;
   }

   bool BFS(){
        memset(vis,0,sizeof(vis));
        Head = 0; Tail = 1;
        que[Head] = s;
        vis[s] = 1;
        d[s] = 0;

        int u,v;
        while (Head<Tail){
           u = que[Head++];
           for (int i=head[u]; i!=-1; i=edge[i].nxt){
               Edge& e = edge[i];
               if (!vis[e.to] && e.cap>e.flow){
                  vis[e.to] = 1;
                  que[Tail++] = e.to;
                  d[e.to] = d[u] + 1;
               }
           }
        }
        return vis[t];
   }

   inline int Min(int x, int y) { return x<y?x:y; }
   int DFS(int x, int a){
      if (x==t || a==0) return a;
      int flow = 0, f;
      for (int& i=cur[x]; i!=-1; i=edge[i].nxt){
         Edge& e = edge[i];
         if (d[e.to] == d[x]+1 && (f=DFS(e.to,Min(a,e.cap-e.flow)))>0 ){
            flow += f;
            a -= f;
            e.flow += f;
            edge[i^1].flow -= f;
            if (a == 0) break;
         }
      }
      return flow;
   }

   int Maxflow(){
     int flow = 0;
     while (BFS()){
        for (int i=1; i<=n; i++) cur[i] = head[i];
        flow += DFS(s,INF);
     }
     return flow;
   }
}dinic;

//SPFA
struct Node{
   int to,w,nxt;
};

struct Shortest_Path{
   int head[maxn];
   bool vis[maxn];
   int cnt[maxn];
   int que[maxn];
   int dis[maxn];
   int tot,Head,Tail;
   int n;
   Node e[maxm];

   inline void add(int u, int v, int w){
        e[tot] = (Node){v,w,head[u]};
        head[u] = tot++;
   }

   void init(int s, int N){
       tot = 0;
       Head = Tail = 0;
       n = N;
       memset(head,-1,sizeof(head));

       for (int i=1; i<=n; i++) {
           if (i == s){
              que[Tail++] = i;
              vis[i] = 1;
              cnt[i] = 1;
              dis[i] = 0;
           }
           else {
              vis[i] = 0;
              cnt[i] = 0;
              dis[i] = INF;
           }
       }
   }

   bool SPFA(){
        int u,v;
        while (Head!=Tail){
           u = que[Head++];
           vis[u] = 0;
           if (Head>=maxn) Head = 0;
           for (int i=head[u]; i!=-1; i=e[i].nxt){
               v = e[i].to;
               if (dis[v]>dis[u]+e[i].w){
                   dis[v] = dis[u] + e[i].w;
                   if (!vis[v]){
                       vis[v] = 1;
                       que[Tail++] = v;
                       if (Tail>=maxn) Tail = 0;
                       if (++cnt[v]>n) return 0;
                   }
               }
           }
        }
        return 1;
   }

}SSSP;

int n,m;
int a[maxm],b[maxm],c[maxm];
int dist1[maxn],dist2[maxn];
int A,B;

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d%d",&n,&m);
       for (int i=1; i<=m; i++) scanf("%d%d%d",&a[i],&b[i],&c[i]);
       scanf("%d%d",&A,&B);

       SSSP.init(A,n);
       for (int i=1; i<=m; i++) SSSP.add(a[i],b[i],c[i]);
       SSSP.SPFA();
       memcpy(dist1,SSSP.dis,sizeof(SSSP.dis));

       SSSP.init(B,n);
       for (int i=1; i<=m; i++) SSSP.add(b[i],a[i],c[i]);
       SSSP.SPFA();
       memcpy(dist2,SSSP.dis,sizeof(SSSP.dis));

       dinic.init(A,B,n);
       for (int i=1; i<=m; i++) {
         if (a[i]!=b[i] && dist1[a[i]]+dist2[b[i]] + c[i] == dist1[B])
            dinic.add(a[i],b[i],1);
       }

       printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
