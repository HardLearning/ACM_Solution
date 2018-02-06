#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 100+5;
int n;
int dp[maxn][maxn];
int sum[maxn],d[maxn];

inline int Min(int x, int y) { return x<y?x:y; }

int main(){
    int t;
    scanf("%d",&t);

    int kase = 0;
    while(t--){
       scanf("%d",&n);
       memset(sum,0,sizeof(sum));
       for (int i=1; i<=n; i++) {
          scanf("%d",&d[i]);
          sum[i] = sum[i-1]+d[i];
       }

       memset(dp,0,sizeof(dp));
       for (int i=1; i<=n; i++)
        for (int j=i; j<=n; j++) dp[i][j] = INF;

       for (int i=n; i>=1; i--) {
          for (int j=i; j<=n; j++) {
              for (int k=1; k<=j-i+1; k++)
                dp[i][j] = Min(dp[i][j],dp[i+1][i+k-1]+dp[i+k][j] + (k-1)*d[i] + k*(sum[j]-sum[i+k-1]));
          }
       }

       printf("Case #%d: %d\n",++kase,dp[1][n]);
    }
    return 0;
}
