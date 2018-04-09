#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 1000+10;
typedef long long LL;
LL n,k,mod;
LL num,tot;

LL qpow(LL a, LL b, LL c){
    LL ans = 1LL;
    a%=c;
    while (b){
        if (b&1) ans = ans*a%c;
        a = a*a%c;
        b>>=1;
    }
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    for (int kase=1; kase<=T; kase++) {
        scanf("%lld%lld%lld",&n,&k,&mod);
        tot = 0;
        for (int i=1; i<=n; i++) {
            scanf("%lld",&num);
            tot += num;
        }
        LL sum = qpow(n,k-1,mod);
        sum = sum*k%mod*tot%mod;
        printf("Case %d: %lld\n",kase,sum);
    }
    return 0;
}
