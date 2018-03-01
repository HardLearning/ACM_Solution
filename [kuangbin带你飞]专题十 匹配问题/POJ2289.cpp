#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char name[20];
const int maxn = 1000+5;
const int maxm = 500+5;
int up[maxm];
vector<int>G[maxn];
vector<int>linker[maxm];
bool vis[maxm];
int n,m;

int DFS(int u){
    int v;
    for (int i=0; i<G[u].size(); i++) {
        v = G[u][i];
        if (vis[v]) continue;
        vis[v] = 1;
        if (linker[v].size()<up[v]) {
            linker[v].push_back(u);
            return 1;
        }
        for (int k=0; k<linker[v].size(); k++)
          if (DFS(linker[v][k])) {
              linker[v][k] = u;
              return 1;
          }
    }
    return 0;
}

int KM(){
    int ans = 0;
    for (int i=0; i<m; i++) linker[i].clear();
    for (int i=0; i<n; i++) {
        memset(vis,0,sizeof(vis));
        ans += DFS(i);
    }
    return ans;
}

bool judge(int mid){
    for (int i=0; i<m; i++) up[i] = mid;
    if (KM()==n) return 1;
    return 0;
}

int main(){
    while (scanf("%d%d",&n,&m)==2 && n+m){
        for (int i=0; i<n; i++) G[i].clear();

        for (int i=0; i<n; i++) {
            scanf("%s",name);
            int x;
            while (getchar()!='\n') {
                scanf("%d",&x);
                G[i].push_back(x);
            }
        }

        int left = 0, right = n;
        int mid,ans;

        while (left<=right){
            mid = (left+right)>>1;
            if (judge(mid)) {right = mid-1; ans = mid;}
            else left = mid+1;
        }
        printf("%d\n",ans);

    }
    return 0;
}
