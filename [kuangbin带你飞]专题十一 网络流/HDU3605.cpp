#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
const int maxn = 1024+10+5;

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
    int m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn];
    bool vis[maxn];
    int cur[maxn];
    int d[maxn];
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

    int DFS(int x, int a){
       if (x==t || a==0) return a;
       int flow = 0, f;
       for (int& i=cur[x]; i<G[x].size(); i++){
          Edge& e = edges[G[x][i]];
          if (d[x]+1==d[e.to] && (f=(DFS(e.to,min(a,e.cap-e.flow))))>0 ){
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
int cnt[maxn],a[maxn];

int main(){
    while (scanf("%d %d",&n,&m)==2){
        memset(cnt,0,sizeof(cnt));

        int x,digit;
        for (int i=1; i<=n; i++) {
            x = 0;
            for (int j=1; j<=m; j++) {
                scanf("%d",&digit);
                x<<=1;
                x|=digit;
            }
            cnt[x]++;
        }
        for (int i=1; i<=m; i++) scanf("%d",&a[i]);

        dinic.init((1<<m)+m);
        for (int i=0; i<(1<<m); i++) {
            dinic.addEdge(dinic.s,i+1,cnt[i]);
            for (int j=0; j<m; j++) if (i&(1<<j)) dinic.addEdge(i+1,j+(1<<m)+1,cnt[i]);
        }
        for (int i=1; i<=m; i++) dinic.addEdge((1<<m)+i,dinic.t,a[i]);

        bool flag = (n <= dinic.Maxflow());
        if (flag) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
