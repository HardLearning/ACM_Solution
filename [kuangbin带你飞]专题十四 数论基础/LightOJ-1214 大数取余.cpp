#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;
const int maxn = 200+10;
char s[maxn];
LL n;

int main(){
    int T;
    scanf("%d",&T);

    for (int kase = 1; kase<=T; kase++) {
        scanf("%s",s);
        scanf("%lld",&n);
        LL t = 0;
        int len = strlen(s),start;
        if (s[0]=='-') start = 1; else start = 0;

        for (int i=start; i<len; i++) {
            t = t*10 + s[i]-'0';
            t%=n;
        }
        if (t==0) printf("Case %d: divisible\n",kase);
        else printf("Case %d: not divisible\n",kase);
    }
    return 0;
}
