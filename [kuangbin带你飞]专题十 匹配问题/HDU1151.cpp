#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 120;
int n,m;
vector<int>G[maxn];
bool vis[maxn];
int cy[maxn];

int DFS(int u){
   int v;
   for (int i=0; i<G[u].size(); i++) {
      v = G[u][i];
      if (!vis[v]) {
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
   for (int i=1; i<=n; i++) {
      memset(vis,0,sizeof(vis));
      ans += DFS(i);
   }
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        for (int i=1; i<=n; i++) G[i].clear();

        int x,y;
        while (m--) {
            scanf("%d%d",&x,&y);
            G[x].push_back(y);
        }

        int ans = KM();
        printf("%d\n",n-ans);
    }
    return 0;
}
