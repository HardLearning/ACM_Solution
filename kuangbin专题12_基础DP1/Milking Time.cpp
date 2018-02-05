#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1000+5;
int dp[maxn];
struct node{
   int st,et,val;
   bool operator <(const node &rhs) const {
       return st<rhs.st ;
   }
}a[maxn];
int n,m,r;

inline int Max( int x, int y ) { return x>y?x:y; }

int main(){
    while (scanf("%d %d %d",&n,&m,&r)==3){
        for (int i=1; i<=m; i++) scanf("%d %d %d",&a[i].st,&a[i].et,&a[i].val);
        sort(a+1,a+m+1);

        int ans = -1;
        for (int i=1; i<=m; i++) {
            dp[i] = a[i].val;
            for (int j=1; j<i; j++) if (a[j].et+r<=a[i].st) dp[i] = Max(dp[i],dp[j]+a[i].val);
            ans = Max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
