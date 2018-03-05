#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
LL n,k,A,B;
LL tot;

int main(){
    while (scanf("%I64d%I64d%I64d%I64d",&n,&k,&A,&B)==4){
        tot = 0;
        while (n>1) {
            LL tmp = (n/k)*k;
            tmp = max(tmp,1LL);
            tot += A*(n-tmp);
            n = tmp;
            if (n==1) break;
            tmp = n/k;
            if (tmp == 0) continue;
            if ((n-tmp)*A<=B) {tot += (n-1)*A; break; }
            else {tot += B; n = tmp; }
        }
        printf("%I64d\n",tot);
    }
    return 0;
}
