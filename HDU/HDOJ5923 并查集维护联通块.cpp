#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define pb push_back
const int maxn = 505;
const int maxm = 10000+5;
int n,m,q;

int fa[maxm][maxn];
vector<int>G[maxm];
struct Edge{
   int from,to;
}e[maxm];
int tot;

int Find(int t, int x) {
   if (fa[t][x]==x) return x;
   return fa[t][x] = Find(t,fa[t][x]);
}

void dfs(int u, int f){
    for (int i=1; i<=n; i++) fa[u][i] = fa[f][i];
    int fx = Find(u,e[u].from);
    int fy = Find(u,e[u].to);
    if (fx!=fy) fa[u][fx] = fy;
    for (int i=0; i<G[u].size(); i++) {
        int v = G[u][i];
        dfs(v,u);
    }
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
       scanf("%d%d",&n,&m);
       for (int i=1; i<=m; i++) G[i].clear();
       int parent;
       for (int i=2; i<=m; i++) {
          scanf("%d",&parent);
          G[parent].pb(i);
       }
       tot = 0;
       for (int i=1; i<=m; i++) {
          tot++;
          scanf("%d%d",&e[tot].from,&e[tot].to);
       }

       for (int i=1; i<=n; i++) fa[1][i] = i;
       dfs(1,1);
       printf("Case #%d:\n",++kase);

       int ki,sum,x;
       scanf("%d",&q);
       while (q--) {
           sum = n;
           scanf("%d",&ki);
           for (int i=1; i<=n; i++) fa[0][i] = i;

           for (int i=1; i<=ki; i++) {
               scanf("%d",&x);
               for (int j=1; j<=n; j++) {
                   int tx = Find(x,j);
                   if (tx==j) continue;
                   int fx = Find(0,tx);
                   int fy = Find(0,j);

                   if (fx!=fy) {
                      sum--;
                      fa[0][fx] = fy;
                   }
               }
           }
           printf("%d\n",sum);
       }
    }
    return 0;
}
