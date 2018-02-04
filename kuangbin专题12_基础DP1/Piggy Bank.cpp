#include <cstdio>
using namespace std;

const int INF = 1e9;
const int maxn = 500+5;
const int maxv = 10000+5;
int vol,n;
int dp[maxv];
struct node{
   int p,w;
}a[maxn];

inline int Min(int x, int y) { return x<y?x:y; }
int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        int e,f;
        scanf("%d %d",&e,&f);
        vol = f-e;
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d %d",&a[i].p,&a[i].w);
        for (int i=0; i<=vol; i++) dp[i] = INF;
        dp[0] = 0;

        for (int i=1; i<=n; i++) {
            for (int j=a[i].w; j<=vol; j++) dp[j] = Min(dp[j-a[i].w]+a[i].p,dp[j]);
        }

        if (dp[vol] == INF) printf("This is impossible.\n");
        else printf("The minimum amount of money in the piggy-bank is %d.\n",dp[vol]);
    }
    return 0;
}
