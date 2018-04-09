#include <cstdio>
#include <cmath>
using namespace std;

const int mod = 1000;
int n,k;

int qpow(int a, int b, int c) {
   int ans = 1;
   a%=c;
   while (b) {
      if (b&1) ans = ans*a%c;
      a = a*a%c;
      b>>=1;
   }
   return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase<=T; kase++) {
        scanf("%d%d",&n,&k);
        int t2 = qpow(n,k,mod);
        double t1 = k*log10(n) - (int)(k*log10(n));
        t1 = pow(10.0,t1);
        printf("Case %d: %d %03d\n",kase,(int)(t1*100), t2);
    }
    return 0;
}
