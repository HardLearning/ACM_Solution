#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 2000+5;
typedef long long LL;
const LL INF = 1e17;
LL dp[maxn][maxn];
int a[maxn],b[maxn];
int n;
inline LL Min(LL x, LL y) {return x<y?x:y; }

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) {
            scanf("%I64d",&a[i]);
            b[i] = a[i];
        }
        sort(b+1,b+n+1);
        for (int i=1; i<=n; i++) dp[0][i] = 0;

        LL tmp;
        for (int i=1; i<=n; i++) {
            tmp = INF;
            for (int j=1; j<=n; j++) {
                tmp = Min(tmp,dp[i-1][j]);
                dp[i][j] = abs(a[i]-b[j]) + tmp;
            }
        }

        LL ans = INF;
        for (int i=1; i<=n; i++) ans = Min(ans,dp[n][i]);
        printf("%I64d\n",ans);
    }
    return 0;
}
