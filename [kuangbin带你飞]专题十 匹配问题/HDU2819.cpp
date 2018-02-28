#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
vector<int>G[maxn];
int a[maxn][maxn];
int n;

bool vis[maxn];
int match[maxn];


int DFS(int u){
   int v;
   for (int  i=0; i<G[u].size(); i++) {
       v = G[u][i];
       if (!vis[v]) {
          vis[v] = 1;
          if (match[v]==-1 || DFS(match[v])) {
              match[v] = u;
              return 1;
          }
       }
   }
   return 0;
}

int KM(){
   int ans = 0;
   memset(match,-1,sizeof(match));
   for (int i=1; i<=n; i++) {
      memset(vis,0,sizeof(vis));
      ans += DFS(i);
   }
   return ans;
}

struct Edge{
   int x,y;
};
vector<Edge>e;
int tot;

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) G[i].clear();
        for (int i=1; i<=n; i++)
          for (int j=1; j<=n; j++) {
               scanf("%d",&a[i][j]);
               if (a[i][j]) G[i].push_back(j);
          }

        int ans = KM();
        if (ans<n) { printf("-1\n"); continue; }

        tot = 0;
        e.clear();
        for (int i=1; i<=n; i++) if (match[i]!=i) {
             tot++;
             e.push_back((Edge){i,match[i]});
             for (int j=1; j<=n; j++) if (match[j]==i) { swap(match[j],match[i]); break; }
        }

        printf("%d\n",tot);
        for (int i=0; i<tot; i++) printf("R %d %d\n",e[i].x,e[i].y);
    }
    return 0;
}
