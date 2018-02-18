#include <cstdio>
using namespace std;

typedef long long LL;
LL x,n,m;

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%I64d",&x);
       if (x==0) { printf("1 1\n"); continue; }
       if (x==1) { printf("-1\n"); continue; }

       bool flag = 0;
       for (LL i=1; i*i<=x; i++) if (x%i==0) {
           LL tmp = x/i;
           if ((i&1) != (tmp&1)) continue;
           n = (tmp+i)/2;
           LL s = tmp-n;
           if (s==0) continue;
           m = n/s;
           if(n>=m && (n+n/m)*(n-n/m)==x) {
              printf("%I64d %I64d\n",n,m);
              flag = 1;
              break;
           }
       }
       if (!flag) printf("-1\n");
    }
    return 0;
}
