#include <cstdio>
using namespace std;

typedef long long LL;
LL n;
LL a,tmp,num,ans;
int k,idx;

int main(){
    num = 0;
    idx = 1;
    scanf("%I64d%d",&n,&k);
    for (int i=1; i<=k; i++) {
        scanf("%I64d",&a);
        tmp = n/a*a;
        if (tmp>num) {
            idx = i;
            ans = n/a;
            num = tmp;
        }
    }
    printf("%d %I64d\n",idx,ans);
    return 0;
}
