#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const LL mod = 1e9+7;
const int maxn = 1000+10;
LL dp[maxn][maxn];
LL md;
int n;

LL quick_pow(LL a, LL b) {
   LL ans = 1;
   while (b) {
      if (b&1) ans *= a, ans %= mod;
      b>>=1;
      a *= a; a%= mod;
   }
   return ans;
}

int main(){
    md = quick_pow(2,mod-2);
    int T;
    scanf("%d",&T);
    int kase = 0;
    while (T--){
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        scanf("%d",&n);
        int dir;

        for (int i=1; i<=n; i++) {
            scanf("%d",&dir);
            if (i==1) dir = 1;
            if (i==n) dir = n;

            if (dir == 1) {
                 for (int j=1; j<=i; j++) dp[i][j] = dp[i-1][j-1];
            }
            else {
                for (int j=i-1; j>=2; j--) dp[i][j] = (dp[i-1][j]*md + dp[i][j+1]*md)%mod;
                dp[i][1] = (dp[i-1][1] + dp[i][2])%mod;
            }
        }

        printf("Case #%d: %lld\n",++kase,dp[n][1]*md%mod);
    }
    return 0;
}
