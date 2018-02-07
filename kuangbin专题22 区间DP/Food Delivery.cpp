#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 1000+10;
int n,v,sx;
struct node{
   int x,b;
   bool operator <(const node &rhs) const {
      return x<rhs.x;
   }
}a[maxn];
int s;
int dp[maxn][maxn][2],sum[maxn];

inline int Min(int x, int y) { return x<y?x:y; }
int main(){
    while (scanf("%d %d %d",&n,&v,&sx)==3){
        for (int i=1; i<=n; i++) scanf("%d %d",&a[i].x,&a[i].b);
        n++;
        a[n].x = sx; a[n].b = 0;
        sort(a+1,a+n+1);

        for (int i=1; i<=n; i++) if (a[i].x == sx) s = i;
        sum[0] = 0;
        for (int i=1; i<=n; i++) sum[i] = sum[i-1] + a[i].b;

        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                for (int k=0; k<=1; k++)
                  dp[i][j][k] = INF;
        dp[s][s][0] = 0; dp[s][s][1] = 0;

        for (int i=s; i>=1; i--) {
            for (int j=s; j<=n; j++) {
                if (i==j) continue;
                int tmp = sum[n]-sum[j]+sum[i];
                dp[i][j][0] = Min(dp[i][j][0],dp[i+1][j][0] + tmp*(a[i+1].x-a[i].x));
                dp[i][j][0] = Min(dp[i][j][0],dp[i+1][j][1] + tmp*(a[j].x-a[i].x));

                tmp = sum[n]-sum[j-1]+sum[i-1];
                dp[i][j][1] = Min(dp[i][j][1],dp[i][j-1][0] + tmp*(a[j].x-a[i].x));
                dp[i][j][1] = Min(dp[i][j][1],dp[i][j-1][1] + tmp*(a[j].x-a[j-1].x));
            }
        }

        printf("%d\n",v*Min(dp[1][n][0],dp[1][n][1]));
    }
    return 0;
}
