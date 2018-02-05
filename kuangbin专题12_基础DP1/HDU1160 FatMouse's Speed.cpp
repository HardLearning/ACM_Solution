#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1000+5;
int n;
struct node{
   int idx,w,s;
   bool operator <(const node &rhs) const {
       return s>rhs.s || (s==rhs.s && w<rhs.w);
   }
}a[maxn];
int pre[maxn],dp[maxn];

void Print(int x){
   if (x == -1) return;
   Print(pre[x]);
   printf("%d\n",a[x].idx+1);
}

int main(){
    n = 0;
    while (scanf("%d %d",&a[n].w,&a[n].s)==2){
        a[n].idx = n;
        n++;
    }
    sort(a,a+n);
    memset(pre,-1,sizeof(pre));
    memset(dp,0,sizeof(dp));

    int ans ,mx=-1;
    for (int i=0; i<n; i++) {
        dp[i] = 1;
        for (int j=0; j<i; j++) {
            if (dp[j]+1>dp[i] && a[j].w<a[i].w && a[j].s>a[i].s) {
                dp[i] = dp[j]+1;
                pre[i] = j;
            }
        }
        if (mx<dp[i]) {mx = dp[i]; ans = i;}
    }

    printf("%d\n",dp[ans]);
    Print(ans);
    return 0;
}
