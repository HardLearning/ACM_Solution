#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
const int maxn = 600+10;
int fa[maxn],val[maxn];
int n,m,p1,p2;

bool vis[maxn];
int c[maxn][2],tot;
vector<int>a[maxn][2];

inline void init(){
    m = p1+p2;
    memset(vis,0,sizeof(vis));
    memset(fa,-1,sizeof(fa));
    memset(val,0,sizeof(val));
    memset(c,0,sizeof(c));
    for (int i=0 ;i<=m; i++) a[i][1].clear(),a[i][0].clear();
    tot = 1;
}

int Find(int x){
   if (fa[x] == -1) return x;
   int tmp = Find(fa[x]);
   val[x] = (val[x]+val[fa[x]])%2;
   return fa[x] = tmp;
}

int dp[maxn][maxn];
int pre[maxn][maxn];
vector<int>ans;

void DP(){
    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    for (int i=1; i<tot; i++) {
        for (int j=p1; j>=0; j--) {
            if (j-c[i][0]>=0 && dp[i-1][j-c[i][0]]) {
                dp[i][j] += dp[i-1][j-c[i][0]];
                pre[i][j] = j-c[i][0];
            }
            if (j-c[i][1]>=0 && dp[i-1][j-c[i][1]]) {
                dp[i][j] += dp[i-1][j-c[i][1]];
                pre[i][j] = j-c[i][1];
            }
        }
    }
}

void solve(){
    if (dp[tot-1][p1]!=1) { printf("no\n"); return; }
    ans.clear();

    int p = p1;
    int idx,tmp;
    for (int i=tot-1; i>=1; i--) {
        tmp = p-pre[i][p];
        if (tmp == c[i][0]) idx = 0; else idx = 1;
        for (int j=0; j<a[i][idx].size(); j++) ans.pb(a[i][idx][j]);
        p = pre[i][p];
    }
    sort(ans.begin(),ans.end());
    for (int i=0; i<p1; i++) printf("%d\n",ans[i]);
    printf("end\n");
}

int main(){
    while (scanf("%d %d %d",&n,&p1,&p2)==3) {
        if (n==0 && p1 == 0 && p2 == 0) break;
        init();

        int rx,ry;
        int x,y,flag;
        char str[10];
        while (n--) {
            scanf("%d %d %s",&x,&y,str);
            if (str[0]=='y') flag = 0; else flag = 1;
            rx = Find(x); ry = Find(y);
            if (rx!=ry) {
                fa[ry] = rx;
                val[ry] = (val[x]-val[y]+flag+2)%2;
            }
        }

        for (int i=1; i<=m; i++) if (!vis[i]) {
            vis[i] = 1;
            rx = Find(i);
            for (int j=1; j<=m; j++) if (Find(j) == rx){
                    vis[j] = 1;
                    a[tot][val[j]].pb(j);
                    c[tot][val[j]]++;
            }
            tot++;
        }

        DP();
        solve();
    }
    return 0;
}
