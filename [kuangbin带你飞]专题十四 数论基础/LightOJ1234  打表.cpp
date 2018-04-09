#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 1e6+123;
double sum[maxn];
int n;

void init(){
    double ans = 0;
    for (int i=1; i<=100000000; i++) {
         ans += 1.0/(i*1.0);
         if (i%100==0) sum[i/100] = ans;
    }
}

int main(){
    init();
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase<=T; kase++) {
         scanf("%d",&n);
         int t = n/100;
         double ans = sum[t];
         for (int k=t*100+1; k<=n; k++) {
             ans += 1.0/(1.0*k);
         }
         printf("Case %d: %.10f\n",kase,ans);
    }
    return 0;
}
