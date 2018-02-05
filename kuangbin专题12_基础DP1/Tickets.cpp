#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 2000+10;
int s[maxn],d[maxn];
int dp[maxn];
int n;
int  hh,mm,ss;

inline int Min(int x, int y) { return x<y?x:y; }

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
       scanf("%d",&n);
       for (int i=1; i<=n; i++) scanf("%d",&s[i]);
       for (int i=1; i<n; i++) scanf("%d",&d[i]);

       dp[1] = s[1]; dp[0] = 0;
       for (int i=2; i<=n; i++) dp[i] = Min(dp[i-1]+s[i],dp[i-2]+d[i-1]);
       int tmp = dp[n];
       hh = 8; mm = ss = 0;
       hh += tmp/3600; tmp%=3600;
       mm += tmp/60; tmp%=60;
       ss += tmp;
       printf("%02d:%02d:%02d",hh,mm,ss);
       if (hh<=12) printf(" am\n"); else printf(" pm\n");
    }
    return 0;
};
