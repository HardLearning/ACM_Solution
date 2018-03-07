#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1<<25;
const int maxn = 500+10;
char s[maxn][maxn];
int n,m,K;
int cnt[maxn],pos[maxn][maxn];
int dp[maxn],v[maxn][maxn];

int main(){
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1; i<=n; i++) scanf("%s",s[i]+1);
    memset(cnt,0,sizeof(cnt));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) if (s[i][j]=='1') pos[i][++cnt[i]] = j;
    }

    for (int i=1; i<=n; i++) {
        for (int k=0; k<=min(cnt[i]-1,K); k++) {
            int res = INF;
            for (int p=0; p<=k; p++) {
                int q = k-p;
                res = min(res,pos[i][cnt[i]-q]-pos[i][p+1]+1);
            }
            v[i][k] = m-res;
        }
        v[i][cnt[i]] = m;
    }

    memset(dp,0,sizeof(dp));
    for (int i=1; i<=n; i++) {
        for (int j=K; j>=0; j--) {
            for (int k=0; k<=min(j,m); k++)
                dp[j] = max(dp[j],dp[j-k]+v[i][k]);
        }
    }
    printf("%d\n",n*m-dp[K]);
    return 0;
}
