#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
LL x,y,m,n,p,g;

void extend_gcd(LL a, LL b,LL &d, LL &x, LL &y) {
    if (b == 0) {
        x = 1; y = 0;
        d = a;
    }
    else {
       extend_gcd(b,a%b,d,y,x);
       y -= x*(a/b);
    }
}

int main(){
    scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&p);
    LL c = y-x;
    LL a = m-n;
    LL b = p;
    if (a<0) {
        a = -a;
        c = -c;
    }

    extend_gcd(a,b,g,x,y);
    if (c%g != 0 ) printf("Impossible\n");
    else {
        x = x*c/g;
        LL t = b/g;
        x = (x%t+t)%t;
        printf("%lld\n",x);
    }
    return 0;
}
