#include <cstdio>
#include <cmath>
using namespace std;

typedef long long LL;
LL n,i;

int main(){
    int T;
    scanf("%d",&T);
    for (int kase=1; kase<=T; kase++) {
        scanf("%lld",&n);
        LL sum = 0;
        LL sq = (LL)sqrt(n*1.0);
        for (i=1; i<=sq; i++) {
            sum += n/i;
            sum += (n/i-n/(i+1))*i;
        }
        if (sq==n/sq) sum-=sq;
        printf("Case %d: %lld\n",kase,sum);
    }
    return 0;
}
