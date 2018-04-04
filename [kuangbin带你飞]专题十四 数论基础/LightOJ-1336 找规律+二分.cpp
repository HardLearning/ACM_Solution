#include <cstdio>
using namespace std;

typedef long long LL;
LL n,ans;

LL Find1(LL n) {
   LL left = 1LL, right = 1000000LL;
   LL mid,ans;
   while (left<=right) {
      mid = (left+right)>>1;
      if (mid*mid<=n) {
         ans = mid;
         left = mid+1;
      }
      else right = mid-1;
   }
   return ans;
}

LL Find2(LL n) {
   LL left = 1LL, right = 1000000LL;
   LL mid,ans;
   while (left<=right) {
      mid = (left+right)>>1;
      if (2*mid*mid<=n) {
         ans = mid;
         left = mid+1;
      }
      else right = mid-1;
   }
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    int kase = 0;

    while (T--) {
        scanf("%lld",&n);
        LL ans = Find1(n) + Find2(n);
        printf("Case %d: %lld\n",++kase,n-ans);
    }
    return 0;
}
