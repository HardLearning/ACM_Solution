#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1000+2;
const int maxm = 22;
int n,m;
int s,e;
int r[maxn][maxm];
int cap[maxm];
vector<int>link[maxm];
bool vis[maxm];

int DFS(int u){
    for (int v=1; v<=m; v++) {
         if (!vis[v] && s<=r[u][v] && r[u][v]<=e) {
            vis[v] = 1;
            if (link[v].size()<cap[v]) {
                link[v].push_back(u);
                return 1;
            }

            for (int i=0; i<cap[v]; i++) if (DFS(link[v][i])) {
                 link[v][i] = u;
                 return 1;
            }
         }
    }
    return 0;
}

bool judge(int mid){
   for (s=1; s<=m-mid+1; s++) {
       e = s+mid-1;
       for (int i=1; i<=m; i++) link[i].clear();

       int ans = 0;
       for (int i=1; i<=n; i++) {
           memset(vis,0,sizeof(vis));
           ans += DFS(i);
       }
       if (ans==n) return 1;
   }
   return 0;
}

int main(){
    while (scanf("%d%d",&n,&m)==2){
        int carn;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                scanf("%d",&carn);
                r[i][carn] = j;
            }
        }
        for (int i=1; i<=m; i++) scanf("%d",&cap[i]);

        int left = 1, right = m;
        int ans = 0, mid;
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
