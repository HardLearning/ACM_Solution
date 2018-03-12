#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long LL;
LL n,m;
LL x,y,z;

LL gcd(LL a,LL b) {
   if (b==0) return a;
   return gcd(b,a%b);
}

int main(){
    while (scanf("%I64d%I64d",&n,&m)==2 && n+m) {
       x = n*(m-1);
       y = m*m;
       z = gcd(x,y);
       x /= z;
       y /= z;
       printf("%I64d/%I64d\n",x,y);
    }
    return 0;
}
