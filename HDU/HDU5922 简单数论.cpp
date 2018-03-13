#include <cstdio>
using namespace std;

typedef long long LL;
LL n,x;

int main(){
    int T;
    scanf("%d",&T);
    for (int i=1; i<=T; i++) {
       scanf("%I64d",&n);
       x = n*(n+1)/2;
       x -= 1;
       printf("Case #%d: %I64d\n",i,x);
    }
    return 0;
}
