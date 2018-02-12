#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int INF = 1e9;
const int maxn = 800+10;
inline int Min(int x, int y) { return x<y?x:y; }

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
       for (int& i = cur[x]; i<G[x].size(); i++){
         Edge& e = edges[G[x][i]];
         if (d[e.to]==d[x]+1 && (f=(DFS(e.to,Min(a,e.cap-e.flow))))>0 ){
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

const int maxm = 25;
char s[maxm][maxm];
char b[maxm][maxm];
int a[maxm][maxm];
int n,m,d,tot,cnt;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

void add(int x, int y){
   int num = b[x][y]-'0';
   if (num==0) return;
   int tx,ty;

   dinic.addEdge(a[x][y],a[x][y]+tot,num);
   for (int i=0; i<4; i++){
       tx = x+dx[i]*d;
       ty = y+dy[i]*d;
       if (tx<1 || ty<1 || tx>n || ty>m) dinic.addEdge(a[x][y]+tot,dinic.t,INF);
   }

   for (int i=1; i<=n; i++)
     for (int j=1; j<=m; j++) {
          if (i==x && j==y && b[i][j]=='0') continue;
          if (abs(x-i)+abs(y-j)<=d) dinic.addEdge(a[x][y]+tot,a[i][j],INF);
     }
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
       scanf("%d%d",&n,&d);
       for (int i=1; i<=n; i++) scanf("%s",b[i]+1);
       for (int i=1; i<=n; i++) scanf("%s",s[i]+1);
       m = strlen(s[1]+1);

       tot = 0;
       for (int i=1; i<=n; i++)
         for (int j=1; j<=m; j++) a[i][j] = ++tot;

       dinic.init(tot*2);

       for (int i=1; i<=n; i++) {
         for (int j=1; j<=m; j++) add(i,j);
       }

       cnt = 0;
       for (int i=1; i<=n; i++) {
          for (int j=1; j<=m; j++) {
             if (s[i][j]=='L') {
                dinic.addEdge(dinic.s,a[i][j],1);
                cnt++;
             }
          }
       }

       int ans = cnt - dinic.Maxflow();
       printf("Case #%d: ",++kase);
       if (ans<=0) printf("no lizard was left behind.\n");
       else if (ans == 1) printf("1 lizard was left behind.\n");
       else printf("%d lizards were left behind.\n",ans);

    }
    return 0;
}
