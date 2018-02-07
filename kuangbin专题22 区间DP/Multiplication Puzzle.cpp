#include <cstdio>
using namespace std;

const int INF = 1e9;
const int maxn = 100+5;
int dp[maxn][maxn];
int a[maxn];
int n;

inline int Min(int x, int y) { return x<y?x:y; }
int DP(int l, int r){
   if (dp[l][r]!=INF) return dp[l][r];
   if (l+1==r) return dp[l][r] = 0;
   for (int k=l+1; k<r; k++) {
       dp[l][r] = Min(dp[l][r],a[k]*a[l]*a[r]+DP(l,k)+DP(k,r));
   }
   return dp[l][r];
}

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) dp[i][j] = INF;
        printf("%d\n",DP(1,n));
    }
    return 0;
}
