#include <cstdio>
using namespace std;

typedef long long LL;
LL a,b;

int main(){
    int T;
    scanf("%d",&T);
    for (int i=1; i<=T; i++) {
        scanf("%I64d%I64d",&a,&b);
        printf("Case #%d:\n",i);
        if (a==b)  {
            printf("1\n");
            printf("%I64d %I64d\n",a,b);
        }
        else {
            printf("2\n");
            printf("%I64d %I64d\n",a,b);
            printf("%I64d %I64d\n",b,a);
        }
    }
    return 0;
}
