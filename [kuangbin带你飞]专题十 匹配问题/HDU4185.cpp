#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 1100;
const int maxm = 600+5;
char str[maxm][maxm];
int idx[maxm][maxm];
int g[maxn][maxn];
int n,tot;

int cy[maxn];
bool vis[maxn];

int DFS(int u){
   for (int v=1; v<=tot; v++) {
     if (g[u][v] && !vis[v]) {
        vis[v] = 1;
        if (cy[v]==-1 || DFS(cy[v])) {
            cy[v] = u;
            return 1;
        }
     }
   }
   return 0;
}

int KM(){
   int ans = 0;
   memset(cy,-1,sizeof(cy));
   for (int i=1; i<=tot; i++) {
      memset(vis,0,sizeof(vis));
      ans += DFS(i);
   }
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%s",str[i]+1);

        tot = 0;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) if (str[i][j]=='#') {
                idx[i][j] = ++tot;
            }
        }

        memset(g,0,sizeof(g));
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (str[i][j]!='#') continue;
                if (i-1>=1 && str[i-1][j]=='#') g[idx[i][j]][idx[i-1][j]] = 1;
                if (i+1<=n && str[i+1][j]=='#') g[idx[i][j]][idx[i+1][j]] = 1;
                if (j-1>=1 && str[i][j-1]=='#') g[idx[i][j]][idx[i][j-1]] = 1;
                if (j+1<=n && str[i][j+1]=='#') g[idx[i][j]][idx[i][j+1]] = 1;
            }
        }

        int ans = KM();
        printf("Case %d: %d\n",++kase,ans/2);
    }
    return 0;
}
