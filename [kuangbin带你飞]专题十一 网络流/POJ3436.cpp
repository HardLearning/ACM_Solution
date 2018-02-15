#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
const int maxm = 100+10;
const int maxn = 55;
const int INF = 1e9;

struct Edge{
   int from,to,cap,flow;
};

inline int Min(int x, int y) { return x<y?x:y; }

struct Dinic{
    vector<Edge>edges;
    vector<int>G[maxm];
    int d[maxm];
    int cur[maxm];
    bool vis[maxm];
    int m,s,t;

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
       int flow = 0,f;
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

const int maxp = 30;
int p,n;
int q[maxn];
int in[maxn][maxp];
struct node{
    int from,to,val;
};
vector<node>a;


int main(){
    while (scanf("%d%d",&p,&n)==2){
        for (int i=1; i<=n; i++) {
            scanf("%d",&q[i]);
            for (int j=1; j<=p*2; j++) scanf("%d",&in[i][j]);
        }
        dinic.init(n*2);
        for (int i=1; i<=n; i++) dinic.add(i,i+n,q[i]);

        bool f_s,f_t;
        for (int i=1; i<=n; i++) {
            f_s = f_t = 1;
            for (int j=1; j<=p; j++) {
                if (in[i][j]==1) f_s = 0;
                if (in[i][j+p]==0) f_t = 0;
            }
            if (f_s) dinic.add(dinic.s,i,INF);
            if (f_t) dinic.add(i+n,dinic.t,INF);
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) if (i!=j) {
                bool flag = 1;
                for (int k=1; k<=p; k++)
                  if ((in[i][k+p]==1 && in[j][k]==0) || (in[i][k+p]==0 && in[j][k]==1)) {
                    flag = 0;
                    break;
                  }
                if (flag) dinic.add(i+n,j,Min(q[i],q[j]));
            }
        }

        int ans = dinic.Maxflow();
        if (ans == 0) {
            printf("0 0\n");
            continue;
        }

        a.clear();
        for (int i=0; i<dinic.edges.size(); i++) {
            Edge& e = dinic.edges[i];
            if (e.from==dinic.s || e.to == dinic.t || e.from+n==e.to) continue;
            if (e.from>n) e.from -= n;
            if (e.to>n) e.to -= n;
            if (e.cap>0 && e.flow>0) a.pb((node){e.from,e.to,e.flow});
        }

        printf("%d %d\n",ans,a.size());
        for (int i=0; i<a.size(); i++) printf("%d %d %d\n",a[i].from,a[i].to,a[i].val);

    }
    return 0;
}
