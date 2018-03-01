#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int INF = 1e9;
const int maxn = 250;
vector<int>G[maxn];
vector<int>link[maxn];
int dis[maxn][maxn];
int left[maxn];
bool vis[maxn];
int n,m,cap;

inline int Min(int x, int y) {return x<y?x:y;}
inline int Max(int x, int y) {return x>y?x:y;}

void Floyd(){
    for (int k=1; k<=n+m; k++)
        for (int i=1; i<=n+m; i++)
           for (int j=1; j<=n+m; j++)
              dis[i][j] = Min(dis[i][j],dis[i][k]+dis[k][j]);
}

int DFS(int u){
    int v;
    for (int i=0; i<G[u].size(); i++) {
        v = G[u][i];
        if (vis[v]) continue;
        vis[v] = 1;
        if (link[v].size()<cap) {
            link[v].push_back(u);
            return 1;
        }

        for (int k=0; k<cap; k++) if (DFS(link[v][k])) {
            link[v][k] = u;
            return 1;
        }
    }
    return 0;
}

bool judge(int mid){
    for (int i=1; i<=m; i++) G[i].clear();
    for (int i=1; i<=n; i++) link[i].clear();
    for (int j=1; j<=n; j++)
        for (int i=n+1; i<=n+m; i++) if (dis[j][i]<=mid) G[i-n].push_back(j);

    for (int i=1; i<=m; i++) {
        memset(vis,0,sizeof(vis));
        if (DFS(i)==0) return 0;
    }
    return 1;
}

int main(){
    while (scanf("%d%d%d",&n,&m,&cap)==3){
        int w;
        for (int i=1; i<=n+m; i++)
          for (int j=1; j<=n+m; j++) {
              scanf("%d",&dis[i][j]);
              if (dis[i][j]==0) dis[i][j] = INF;
          }
        Floyd();

        int ans,mid;
        int left = 1, right = 1000000;
        while (left<=right){
            mid = (left+right)>>1;
            if (judge(mid)) {
                ans = mid;
                right = mid-1;
            }
            else left = mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
