#include <cstdio>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

typedef long long LL;
const int maxn = 5e5+10;
LL a[maxn],sum[maxn];
int tot;

double cal(int cnt){
   return a[tot]*1.0-(sum[cnt]+a[tot])*1.0/(cnt+1);
}

double ternary_search(int left, int right) {
   double ans = 0;
   int midl,midr;
   double xl,xr;
   while (right>left+1){
       midl = (right+left)>>1;
       midr = (right+midl)>>1;
       xl = cal(midl);
       xr = cal(midr);
       if (dcmp(xl-xr)<0) left = midl; else right = midr;
   }
   xl = cal(left);
   xr = cal(right);
   if (dcmp(xl-xr)>0) return xl; else return xr;
}

int main(){
    int Q;
    scanf("%d",&Q);

    int query;
    tot = 0; sum[0] = 0;
    while(Q--){
        scanf("%d",&query);
        if (query == 1) {
             tot++;
             scanf("%I64d",&a[tot]);
             sum[tot] = a[tot] + sum[tot-1];
        }
        else {
             printf("%.10f\n",ternary_search(1,tot-1));
        }
    }
    return 0;
}
