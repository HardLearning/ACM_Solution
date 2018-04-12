#include <cstdio>
using namespace std;

const int INF = 1e9;
int Q;

int  judge(int x){
   int sum = 0;
   while (x) {
      sum += x/5;
      x /= 5;
   }
   return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    int kase = 0;
    while (T--) {
        scanf("%d",&Q);
        int left = 1, right = INF;
        int mid, ans = -1,sum;
        while (left<=right) {
            mid = (left+right)>>1;
            sum = judge(mid);
            if (sum == Q) {ans = mid; right = mid-1; continue; }
            if (sum > Q) right = mid-1; else left = mid+1;
        }
        if (ans == -1) printf("Case %d: impossible\n",++kase);
        else printf("Case %d: %d\n",++kase,ans);
    }
    return 0;
}
