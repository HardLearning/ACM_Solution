#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
const int INF = 1e8;
int mx[maxn][maxn];
int cost[maxn][maxn];
bool used[maxn][maxn];
int pre[maxn];
bool vis[maxn];
int lowc[maxn];
int n,m;

inline int Max(int x, int y) { return x>y?x:y; }
inline int Min(int x, int y) { return x<y?x:y; }

int Prim(){
   memset(vis,0,sizeof(vis));
   memset(used,0,sizeof(used));
   memset(mx,0,sizeof(mx));
   int ans = 0;
   int u = 1;
   for (int i=1; i<=n; i++) lowc[i] = cost[u][i], pre[i] = u;
   vis[u] = 1;

   for (int i=1; i<n; i++) {
       int minc = INF;
       for (int j=1; j<=n; j++) if (!vis[j] && minc>lowc[j]) {
           minc = lowc[j];
           u = j;
       }
       ans += minc;
       vis[u] = 1;
       used[u][pre[u]] = used[pre[u]][u] = 1;
       for (int j=1; j<=n; j++) if (j!=u) {
           if (vis[j]) mx[j][u] = mx[u][j] = Max(mx[j][pre[u]],lowc[u]);
           if (!vis[j] && lowc[j]>cost[u][j]) {
              lowc[j] = cost[u][j];
              pre[j] = u;
           }
       }
   }
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
       scanf("%d%d",&n,&m);
       for (int i=1; i<=n; i++) {
          for (int j=1; j<=n; j++) cost[i][j] = INF;
       }

       int x,y,w;
       for (int i=1; i<=m; i++) {
           scanf("%d%d%d",&x,&y,&w);
           cost[x][y] = cost[y][x] = Min(w,cost[x][y]);
       }

       int MST = Prim();
       int second_MST = INF;
       for (int i=1; i<=n; i++) {
           for (int j=i+1; j<=n; j++) {
              if (cost[i][j]<INF && !used[i][j])
                 second_MST = Min(second_MST,MST+cost[i][j]-mx[i][j]);
           }
       }
       printf("%d %d\n",MST,second_MST);
    }
    return 0;
}
