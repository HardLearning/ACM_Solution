#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2000+5;
int dp[maxn][maxn];
int a[maxn];
int n;

inline int Max(int x, int y) { return x>y?x:y; }

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        memset(dp,0,sizeof(dp));
        for (int i=1; i<=n; i++) dp[i][i] = a[i]*n;
        for (int i=1; i<n; i++) {
            for (int j=1; j+i<=n; j++) {
                int k = j+i;
                dp[j][k] = Max(dp[j+1][k]+(n-i)*a[j],dp[j][k-1]+(n-i)*a[k]);
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}
