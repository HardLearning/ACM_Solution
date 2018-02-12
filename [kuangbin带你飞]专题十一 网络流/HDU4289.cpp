#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
const int maxn = 200*2+10;
const int INF = 1e9;

inline int Min(int x, int y){return x<y?x:y; }

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

    void init(int n, int s, int t){
       this->s = s; this->t = t+n;
       edges.clear();
       for (int i=0; i<=2*n+1; i++) G[i].clear();
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
       d[s] = 0;
       vis[s] = 1;

       int u;
       while (!que.empty()){
          u = que.front();
          que.pop();
          for (int i=0; i<G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (!vis[e.to] && e.cap > e.flow){
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
        for (int& i=cur[x]; i<G[x].size(); i++) {
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
}dinic;

int n,m;
int s,t;

int main(){
    while (scanf("%d%d",&n,&m)==2){
        scanf("%d%d",&s,&t);
        dinic.init(n,s,t);

        int x;
        for (int i=1; i<=n; i++) {
           scanf("%d",&x);
           dinic.addEdge(i,i+n,x);
        }

        int u,v;
        while (m--){
            scanf("%d%d",&u,&v);
            dinic.addEdge(u+n,v,INF);
            dinic.addEdge(v+n,u,INF);
        }

        printf("%d\n",dinic.Maxflow());
    }
    return 0;
}
