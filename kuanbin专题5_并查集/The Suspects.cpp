#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define pb push_back
const int maxm = 500+5;
const int maxn = 30000+10;
bool vis[maxn],vis_g[maxm];
vector<int>G[maxn],g[maxm];
int n,m;

void init(){
     memset(vis,0,sizeof(vis));
     memset(vis_g,0,sizeof(vis_g));
     for (int i=0; i<n; i++) G[i].clear();
     for (int i=0; i<m; i++) g[i].clear();

     int k;
     int num;
     for (int i=1; i<=m; i++) {
         scanf("%d",&k);
         for (int j=1; j<=k; j++) {
             scanf("%d",&num);
             g[i-1].pb(num);
             G[num].pb(i-1);
         }
     }
}

void DFS(int u) {
    vis[u] = 1;
    int group,v;
    for (int i=0; i<G[u].size(); i++) {
         group = G[u][i];
         if (vis_g[group]) continue;
         vis_g[group] = 1;
         for (int j=0; j<g[group].size(); j++) {
              v = g[group][j];
              if (vis[v]) continue;
              DFS(v);
         }
    }
}

int main(){
    while (scanf("%d %d",&n,&m)==2) {
        if (n == 0 && m == 0) break;
        init();
        DFS(0);
        int sz = 0;
        for (int i=0; i<n; i++) if (vis[i]) sz++;
        printf("%d\n",sz);
    }
    return 0;
}
