#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxa = 50;
const int maxn = 500;
char str[maxa][maxa];
int idx[maxa][maxa];
vector<int>G[maxn];
int cy[maxn];
bool vis[maxn];
int n,m,tot;

int DFS(int u){
    int v;
    for (int i=0; i<G[u].size(); i++) {
        v = G[u][i];
        if (!vis[v]) {
            vis[v] = 1;
            if (cy[v]==-1 || DFS(cy[v])){
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
    while (T--){
        scanf("%d%d",&n,&m);
        for (int i=1; i<=n; i++) scanf("%s",str[i]+1);

        memset(idx,0,sizeof(idx));
        tot = 0;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=m; j++) if (str[i][j]=='*') idx[i][j] = ++tot,G[tot].clear();

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (str[i][j]=='o') continue;
                if (i-1>=1 && str[i-1][j]=='*') G[idx[i][j]].push_back(idx[i-1][j]);
                if (j-1>=1 && str[i][j-1]=='*') G[idx[i][j]].push_back(idx[i][j-1]);
                if (i+1<=n && str[i+1][j]=='*') G[idx[i][j]].push_back(idx[i+1][j]);
                if (j+1<=m && str[i][j+1]=='*') G[idx[i][j]].push_back(idx[i][j+1]);
            }
        }

        int ans = KM();
        printf("%d\n",tot-ans+ans/2);
    }
    return 0;
}
