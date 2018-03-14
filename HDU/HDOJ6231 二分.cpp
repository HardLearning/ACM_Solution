#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+10;
int n,k;
long long m;
int a[maxn],b[maxn];

bool judge(int x) {
    int sum = 0, tail=0;
    long long tot = 0;
    for (int head=1; head<=n; head++) {
        while (sum<k && tail<=n) {
            if (a[++tail]>=x) sum++;
        }
        if (tail>n) break;
        tot += n-tail+1;
        if (a[head]>=x) sum--;
    }
    return tot>=m;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
       scanf("%d%d%I64d",&n,&k,&m);
       for (int i=1; i<=n; i++) scanf("%d",&a[i]), b[i] = a[i];
       sort(b+1,b+n+1);

       int left = 1, right = n;
       int mid, ans = -1;
       while (left<=right) {
           mid = (left+right)>>1;
           if (judge(b[mid])) {
               ans = b[mid];
               left = mid+1;
           }
           else right = mid-1;
       }
       printf("%d\n",ans);
    }
    return 0;
}
