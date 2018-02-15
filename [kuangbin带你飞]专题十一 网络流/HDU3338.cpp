#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 100+5;
const int maxm = 20000+10;
const int INF = 1e9;
#define pb push_back

struct Edge{
   int from,to,cap,flow;
};

struct Dinic{
    vector<Edge> edges;
    vector<int> G[maxm];
    int d[maxm];
    int cur[maxm];
    bool vis[maxm];
    int m,s,t;

    void init(int n){
       s=0; t=n+1;
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
        memset(vis,0,sizeof(vis));
        queue<int>que;
        que.push(s);
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

    inline int Min(int x, int y) { return x<y?x:y; }

    int DFS(int x, int a){
       if (x==t || a==0) return a;
       int flow = 0, f;
       for (int&i = cur[x]; i<G[x].size(); i++) {
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

    void Maxflow(){
       int flow = 0;
       while (BFS()){
           memset(cur,0,sizeof(cur));
           flow += DFS(s,INF);
       }
    }

}dinic;

int n,m;
bool mark[maxn][maxn];
char ans[maxn][maxn];
char s[maxn][maxn][10];

int main(){
    while (scanf("%d%d",&n,&m)!=EOF){
        memset(mark,0,sizeof(mark));
        dinic.init(2*n*m);
        for (int i=1; i<=n; i++)
          for (int j=1; j<=m; j++) {
             scanf("%s",s[i][j]+1);
             if (s[i][j][1]=='.') {
                mark[i][j] = 1;
                dinic.add((i-1)*m+j,(i-1)*m+j+n*m,8);
             }
             else ans[i][j]='_';
          }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (!mark[i][j]) {
                    if (s[i][j][1]!='X'){
                        int num = (s[i][j][1]-'0')*100+(s[i][j][2]-'0')*10+(s[i][j][3]-'0');
                        int idx = (i-1)*m+j;
                        for (int k=i+1; k<=n && mark[k][j]; k++) {
                            num--;
                            dinic.add(idx,(k-1)*m+j,INF);
                        }
                        dinic.add(dinic.s,idx,num);
                    }

                    if (s[i][j][5]!='X'){
                        int num = (s[i][j][5]-'0')*100+(s[i][j][6]-'0')*10+(s[i][j][7]-'0');
                        int idx = (i-1)*m+j+n*m;
                        for (int k=j+1; k<=m && mark[i][k]; k++) {
                            num--;
                            dinic.add((i-1)*m+k+n*m,idx,INF);
                        }
                        dinic.add(idx,dinic.t,num);
                    }
                }
            }
        }

        dinic.Maxflow();

        for (int i=0; i<dinic.edges.size(); i++) {
            Edge& e = dinic.edges[i];
            if (e.from<=n*m && e.to>n*m){
                int x = e.from/m+1;
                int y = e.from%m;
                if (y==0) {
                    x--;
                    y=m;
                }
                ans[x][y] = e.flow+'1';
            }
        }

        int i,j;
        for (i=1; i<=n; i++) {
            for (j=1; j<m; j++) printf("%c ",ans[i][j]);
            printf("%c\n",ans[i][j]);
        }
    }
    return 0;
}
