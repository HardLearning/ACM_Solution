#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 500+5;
int n,m;
int a[maxn][maxn];
bool vis[maxn];
int cy[maxn];

int DFS(int u){
   for (int v=1; v<=n; v++) {
      if (!a[u][v] || vis[v]) continue;
      vis[v] = 1;
      if (cy[v]==-1 || DFS(cy[v])) {
          cy[v] = u;
          return 1;
      }
   }
   return 0;
}

int KM(){
   int ans = 0;
   memset(cy,-1,sizeof(cy));
   for (int i=1; i<=n; i++) {
     memset(vis,0,sizeof(vis));
     ans += DFS(i);
   }
   return ans;
}

void Floyd(){
    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
           for (int j=1; j<=n; j++)
             if (a[i][k] && a[k][j]) a[i][j] = 1;
}

int main(){
    while (scanf("%d%d",&n,&m)==2 && n){
        memset(a,0,sizeof(a));
        int x,y;
        while (m--) {
           scanf("%d%d",&x,&y);
           a[x][y] = 1;
        }
        Floyd();

        int ans = KM();
        printf("%d\n",n-ans);
    }
    return 0;
}
