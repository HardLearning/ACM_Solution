#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const double INF = 1e9;
const int maxn = 100+5;
const int maxm = 10000+10;
struct Edge{
   int from,to;
   double w;
}e[maxm];

struct Point{
   double x,y;
}p[maxn];
int n,m,root;

int pre[maxn];
int vis[maxn];
int id[maxn];
double in[maxn];

inline double Length(int i, int j) {
   return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x) + (p[i].y-p[j].y)*(p[i].y-p[j].y));
}

double solve(int root, int n, int m){
   double ans = 0;
   int u,v;
   Edge E;

   while (1){
      for (int i=1; i<=n; i++) in[i] = INF;
      for (int i=0; i<m; i++) {
          E = e[i];
          if (E.from != E.to && E.w < in[E.to]) {
             pre[E.to] = E.from;
             in[E.to] = E.w;
          }
      }

      for (int i=1; i<=n; i++)
        if (i!=root && in[i]==INF) return -1;

      int tn = 0;
      memset(id,-1,sizeof(id));
      memset(vis,-1,sizeof(vis));
      in[root] = 0;
      for (int i =1; i<=n; i++) {
          ans += in[i];
          v = i;
          while (vis[v]!=i && id[v]==-1 && v!=root) {
             vis[v] = i;
             v = pre[v];
          }

          if (v!=root && id[v]==-1) {
             tn++;
             for (u = pre[v]; u!=v; u=pre[u]) id[u] = tn;
             id[v] = tn;
          }
      }

      if (tn == 0) break;
      for (int i=1; i<=n; i++) if (id[i]==-1) id[i] = ++tn;
      for (int i = 0; i<m; i++) {
         v = e[i].to;
         e[i].from = id[e[i].from];
         e[i].to = id[e[i].to];

         if (e[i].from != e[i].to)
            e[i].w -= in[v];
      }

      n = tn;
      root = id[root];
   }
   return ans;
}

int main(){
    while (scanf("%d%d",&n,&m)==2){
        root = 1;
        for (int i=1; i<=n; i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        int u,v;
        for (int i=0; i<m; i++) {
            scanf("%d%d",&u,&v);
            e[i].from = u;
            e[i].to = v;
            e[i].w = Length(u,v);
        }

        double ans = solve(root,n,m);
        if (ans==-1) printf("poor snoopy\n"); else printf("%.2f\n",ans);
    }
    return 0;
}
