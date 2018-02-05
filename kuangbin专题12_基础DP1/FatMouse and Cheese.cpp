#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100+5;
int n,k;
int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};
int dp[maxn][maxn],a[maxn][maxn];

inline int Max(int x, int y) { return x>y?x:y; }
int DFS(int x, int y){
   if (dp[x][y]>-1) return dp[x][y];

   dp[x][y] = 0;
   int tx,ty;
   for (int i=1; i<=k; i++) {
       for (int j=0; j<4; j++){
          tx = x + dx[j]*i;
          ty = y + dy[j]*i;
          if (tx<0 || ty<0 || tx>=n || ty>=n) continue;
          if (a[tx][ty]<=a[x][y]) continue;
          dp[x][y] = Max(dp[x][y],DFS(tx,ty));
       }
   }
   dp[x][y] += a[x][y];
   return dp[x][y];
}

int main(){
    while (scanf("%d %d",&n,&k)==2){
        if (n==-1 && k==-1) break;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++) scanf("%d",&a[i][j]);
        memset(dp,-1,sizeof(dp));

        printf("%d\n",DFS(0,0));
    }
    return 0;
}
