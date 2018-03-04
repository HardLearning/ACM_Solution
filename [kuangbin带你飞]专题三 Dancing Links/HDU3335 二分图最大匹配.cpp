#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1000+5;
typedef long long LL;
LL a[maxn];
bool mark[maxn][maxn];
int n;

int left[maxn];
bool vis[maxn];

int DFS(int u){
    for (int v=1; v<=n; v++) if (mark[u][v] && !vis[v]) {
         vis[v] = 1;
         if (left[v]==-1 || DFS(left[v])) {
            left[v] = u;
            return 1;
         }
    }
    return 0;
}

int KM(){
    int ans = 0;
    memset(left,-1,sizeof(left));
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
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%I64d",&a[i]);
        sort(a+1,a+n+1);
        memset(mark,0,sizeof(mark));
        for (int i=1; i<=n; i++)
            for (int j=i+1; j<=n; j++) if (a[j]%a[i]==0) mark[i][j] = 1;

        int ans = KM();
        printf("%d\n",n-ans);
    }
    return 0;
}
