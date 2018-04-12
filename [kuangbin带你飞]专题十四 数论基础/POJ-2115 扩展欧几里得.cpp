#include <cstdio>
using namespace std;

typedef  long long LL;
LL A,B,C,k;
LL gcd,a,b,x,y;
LL c;

void extend_gcd(LL a, LL b, LL &d , LL &x, LL &y) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        extend_gcd(b,a%b,d,y,x);
        y -= x*(a/b);
    }
}

int main() {
    while (scanf("%lld%lld%lld%lld",&A,&B,&C,&k)==4) {
        if (A == 0 && B == 0 && C == 0 && k==0) break;
        a = C;
        b = (LL)1<<k;
        c = B-A;
        extend_gcd(a,b,gcd,x,y);
        if (c % gcd != 0) printf("FOREVER\n");
        else {
            x = x*c/gcd;
            LL t = b/gcd;
            x = (x%t+t)%t;
            printf("%lld\n",x);
        }
    }
    return 0;
}
