#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 200+5;
int n,m;
int lx[maxn],ly[maxn];
bool a[maxn][maxn];
bool vis[maxn];
queue<int> que;

bool BFS(){
    int color[maxn];
    memset(color,-1,sizeof(color));
    for (int i=1; i<=n; i++) if (color[i]==-1) {
        color[i] = 0;
        while (!que.empty()) que.pop();
        que.push(i);

        int u;
        while (!que.empty()) {
             u = que.front();
             que.pop();
             for (int i=1; i<=n; i++) if (i!=u) {
                 if (a[u][i]) {
                     if (color[i]==color[u]) return 0;
                     if (color[i]==-1) {
                         color[i] = !color[u];
                         que.push(i);
                     }
                 }
             }
        }
    }
    return 1;
}

int DFS(int u){
     for (int v=1; v<=n; v++) {
        if (a[u][v] &&!vis[v]) {
            vis[v] = 1;
            if (ly[v]==-1 || DFS(ly[v])) {
                ly[v] = u;
                lx[u] = v;
                return 1;
            }
        }
     }
     return 0;
}

int main(){
    while(scanf("%d%d",&n,&m)==2){
         memset(lx,-1,sizeof(lx));
         memset(ly,-1,sizeof(ly));
         memset(a,0,sizeof(a));

         int u,v;
         for (int i=1; i<=m; i++) {
            scanf("%d%d",&u,&v);
            a[u][v] = 1;
            a[v][u] = 1;
         }

         if (!BFS()) {
            printf("No\n");
            continue;
         }

         int ans = 0;
         for (int i=1; i<=n; i++) {
            memset(vis,0,sizeof(vis));
            ans += DFS(i);
         }

         printf("%d\n",ans/2);

    }
    return 0;
}
