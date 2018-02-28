#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100+5;
int n,m,k;
struct Edge{
   int x,y;
   Edge (int x=0, int y=0):x(x),y(y){}
}e[maxn*maxn];
int x,y;
int cy[maxn];
bool vis[maxn];
bool a[maxn][maxn];

int DFS(int u){
   for (int v=1; v<=m; v++) {
      if (a[u][v] && !vis[v]) {
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
    memset(cy,-1,sizeof(cy));
    int ans = 0;
    for (int i=1; i<=n; i++) {
        memset(vis,0,sizeof(vis));
        ans += DFS(i);
    }
    return ans;
}

int main(){
    int kase = 0;
    while (scanf("%d%d%d",&n,&m,&k)==3) {
        memset(a,0,sizeof(a));
        for (int i=1; i<=k; i++) {
            scanf("%d%d",&x,&y);
            e[i] = Edge(x,y);
            a[x][y] = 1;
        }

        int ans = KM();
        int important = 0;
        for (int i=1; i<=k; i++) {
            memset(a,0,sizeof(a));
            for (int j=1; j<=k; j++) if (j!=i) a[e[j].x][e[j].y] = 1;
            int tmp = KM();
            if (tmp!=ans) important++;
        }

        printf("Board %d have %d important blanks for %d chessmen.\n",++kase,important,ans);
    }
    return 0;
}
