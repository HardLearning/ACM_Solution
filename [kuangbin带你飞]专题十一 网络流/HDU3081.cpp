#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define pb push_back
const int maxn = 100+10;
const int INF = 1e9;

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
    int m,s,t;
    vector<Edge>edges;
    vector<int>G[maxn*2];
    int d[maxn*2];
    int cur[maxn*2];
    bool vis[maxn*2];

    void init(int n){
       s = 0; t = 2*n+1;
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

    inline int  Min(int x, int y) { return x<y?x:y; }

    int DFS(int x, int a){
        if (x==t || a==0) return a;
        int flow = 0, f;
        for (int& i=cur[x]; i<G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (d[e.to] == d[x]+1 && (f=DFS(e.to,Min(a,e.cap-e.flow)))>0 ){
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

const int maxm = 100*100+5;
struct node{
   int girl,boy;
}a[maxm];
int fa[maxn];
vector<int>group[maxn];
vector<int>link[maxn];
bool re[maxn];
bool map[maxn][maxn];
int n,m,f;


int Find(int x){
   if (fa[x] == x) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
   x = Find(x);
   y = Find(y);
   if (x==y) return;
   fa[x] = y;
}

bool solve(int k){
    dinic.init(n);
    for (int i=1; i<=n; i++) dinic.addEdge(dinic.s,i,k);
    for (int i=1; i<=n; i++) dinic.addEdge(i+n,dinic.t,k);
    for (int i=1; i<=n; i++) if (group[i].size()){
        for (int j=0; j<group[i].size(); j++){
            for (int p=0; p<link[i].size(); p++) dinic.addEdge(group[i][j],n+link[i][p],1);
        }
    }

    return k*n == dinic.Maxflow();

}


int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d%d",&n,&m,&f);
        for (int i=1; i<=n; i++) fa[i] = i;
        for (int i=1; i<=m; i++) scanf("%d%d",&a[i].girl,&a[i].boy);
        int u,v;
        while (f--){
            scanf("%d%d",&u,&v);
            Merge(u,v);
        }

        for (int i=1; i<=n; i++) fa[i] = Find(fa[i]);
        for (int i=1; i<=n; i++) group[i].clear();
        for (int i=1; i<=n; i++) link[i].clear();
        for (int i=1; i<=n; i++) group[fa[i]].pb(i);
        memset(map,0,sizeof(map));
        for (int i=1; i<=m; i++) if (!map[fa[a[i].girl]][a[i].boy]) link[fa[a[i].girl]].pb(a[i].boy),map[fa[a[i].girl]][a[i].boy] = 1;


        int left = 0,right = n;
        int mid,ans = 0;
        while (left<=right){
            mid = (left+right)>>1;
            if (solve(mid)){
                ans = mid;
                left = mid+1;
            }
            else right = mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
