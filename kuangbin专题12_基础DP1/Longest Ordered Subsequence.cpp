#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000+5;
int n,len;
int a[maxn];
int dp[maxn];

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        len = 1;
        dp[1] = a[1];

        int left,right,mid;
        for (int i=2; i<=n; i++) {
            left = 1; right = len;
            while (left <= right){
                mid = (left+right)>>1;
                if (dp[mid]>a[i]) right = mid-1;
                else left = mid+1;
            }
            if (left<=len && dp[left]<a[i]) left++;
            if (left>len && dp[len]<a[i]) {len++; dp[len] = a[i]; }
            else dp[left] = a[i];
        }
        printf("%d\n",len);
    }
    return 0;
}
