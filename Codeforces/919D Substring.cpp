#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define pb push_back
const int maxn = 300000+5;
int in[maxn];
int n,m;
char s[maxn];
vector<int>g[maxn];
vector<int>a;
int dp[maxn];

bool Topu(){
    a.clear();
    queue<int>que;
    while (!que.empty()) que.pop();
    for (int i=1; i<=n; i++) if (in[i] == 0) que.push(i);

    int u,v;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        a.pb(u);

        for (int i=0; i<g[u].size(); i++) {
            v = g[u][i];
            in[v]--;
            if (in[v] == 0) que.push(v);
        }
    }
    return a.size() == n;
}

inline int Max(int x, int y) { return x>y?x:y; }

int DP(int x){
   char c = x+'a';
   memset(dp,0,sizeof(dp));

   int u,v;
   int mx = 0;
   for (int k=a.size()-1; k>=0; k--) {
        u = a[k];
        for (int i=0; i<g[u].size(); i++) dp[u] = Max(dp[u],dp[g[u][i]]);
        if (s[u]==c) dp[u]++;
        mx = Max(mx,dp[u]);
   }
   return mx;
}


int main(){
    while (scanf("%d %d",&n,&m)==2){
        scanf("%s",s+1);
        for (int i=1; i<=n; i++) g[i].clear();
        memset(in,0,sizeof(in));

        int u,v;
        for (int i=1; i<=m; i++) {
            scanf("%d %d",&u,&v);
            g[u].pb(v);
            in[v]++;
        }

        if (!Topu()) {
            printf("-1\n");
            continue;
        }

        int ans = -1;
        for (int i=0; i<26; i++) ans = Max(ans,DP(i));
        printf("%d\n",ans);
    }
    return 0;
}
