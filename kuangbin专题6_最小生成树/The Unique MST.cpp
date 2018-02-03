#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 100+5;
int w[maxn][maxn]; // the weight of the edge
int n,m;

bool used[maxn][maxn];
bool vis[maxn];
int pre[maxn];
int lowc[maxn];
int mx[maxn][maxn];
int ans;

inline int Max(int x, int y) { return x>y?x:y; }

int Prim(){
    int ans = 0;
    memset(vis,0,sizeof(vis));
    memset(used,0,sizeof(used));
    memset(mx,0,sizeof(mx));
    vis[1] = 1;
    pre[1] = -1;
    lowc[1] = 0;

    for (int i=2; i<=n; i++) {
        lowc[i] = w[1][i];
        pre[i] = 1;
    }

    for (int i=1; i<n; i++) {
        int minc = INF;
        int p = -1;
        for (int j=2; j<=n; j++) {
            if (!vis[j] && minc>lowc[j]) {
                minc = lowc[j];
                p = j;
            }
        }

        if (minc == -1) return -1;
        ans += minc;
        vis[p] = 1;
        used[p][pre[p]] = used[pre[p]][p] = 1;

        for (int j=2; j<=n; j++) {
            if (vis[j]) mx[j][p] = mx[p][j] = Max(mx[j][pre[p]],lowc[p]);
            if (!vis[j] && lowc[j]>w[p][j]) {
                pre[j] = p;
                lowc[j] = w[p][j];
            }
        }
    }
    return ans;
}

inline int Min(int x, int y) { return x<y?x:y; }
int second_MST(){
     int mn = INF;
     for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            if (w[i][j]!=INF && !used[i][j]) mn = Min(mn,ans+w[i][j]-mx[i][j]);
        }
     }
     if (mn == INF) return -1;
     return mn;
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d %d",&n,&m);
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) w[i][j] = INF;
            w[i][i] = 0;
        }

        int x,y,z;
        while (m--){
            scanf("%d %d %d",&x,&y,&z);
            w[x][y] = w[y][x] = z;
        }

        ans = Prim();
        if (ans == -1) {
            printf("Not Unique!\n");
            continue;
        }

        if (ans == second_MST()) printf("Not Unique!\n");
        else printf("%d\n",ans);

    }
    return 0;
}
