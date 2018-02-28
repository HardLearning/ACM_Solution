#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 300+5;
int cy[maxn];
bool vis[maxn];
int a[maxn][maxn];
int p,n;

int DFS(int u){
    for (int v=1; v<=n; v++) {
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

bool KM(){
    for (int i=1; i<=p; i++) {
        memset(vis,0,sizeof(vis));
        if (!DFS(i)) return 0;
    }
    return 1;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d%d",&p,&n);
       memset(cy,-1,sizeof(cy));
       memset(a,0,sizeof(a));

       int num,y;
       for (int i=1; i<=p; i++) {
          scanf("%d",&num);
          while (num--) {
              scanf("%d",&y);
              a[i][y] = 1;
          }
       }

       if (KM()) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
