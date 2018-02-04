#include <cstdio>
using namespace std;

const int maxn = 1000+5;
int dp[maxn],a[maxn];
int n;

inline int Max(int x, int y) { return x>y?x:y; }
int main(){
    while (scanf("%d",&n)==1 && n){
        for (int i=1; i<=n; i++) scanf("%d",&a[i]),dp[i] = a[i];
        int mx = -1,tmp;
        for (int i=1; i<=n; i++) {
            tmp = dp[i];
            for (int j=1; j<i; j++) if (a[j]<a[i]) tmp = Max(tmp,dp[j]+a[i]);
            dp[i] = tmp;
            mx = Max(mx,tmp);
        }
        printf("%d\n",mx);
    }
    return 0;
}
