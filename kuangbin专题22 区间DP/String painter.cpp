#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100+5;
int dp[maxn][maxn];
char a[maxn],b[maxn];
int ans[maxn];
int n;

inline int Min(int x, int y) { return x<y?x:y; }

int main(){
    while (scanf("%s%s",a+1,b+1)==2){
        n = strlen(a+1);
        memset(dp,0,sizeof(dp));
        for (int j=1; j<=n; j++) {
            for (int i=j; i>=1; i--) {
                dp[i][j] = dp[i+1][j]+1;
                for (int k=i+1; k<=j; k++)
                    if (b[i] == b[k])
                       dp[i][j] = Min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
            }
        }

        for (int i=1; i<=n; i++) ans[i] = dp[1][i];
        for (int i=1; i<=n; i++) {
            if (a[i] == b[i]) ans[i] = ans[i-1];
            else {
                for (int j=1; j<i; j++)
                    ans[i] = Min(ans[i],ans[j]+dp[j+1][i]);
            }
        }
        printf("%d\n",ans[n]);
    }
    return 0;
}
