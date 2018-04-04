#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 1e6+5;
typedef long long LL;
bool vis[maxn];
LL prime[maxn];
int tot;

void get_prime(int n){
   memset(vis,1,sizeof(vis));
   for (int i=2; i<n; i++) if (vis[i]) {
       for (int j=i+i; j<n; j+=i) vis[j] = 0;
   }
   tot = 0;
   for (int i=2; i<n; i++) if (vis[i]) prime[tot++] = (LL)i;
}


LL func(LL x) {
    LL sum = 1;
    for (int i=0; prime[i]*prime[i]<=x; i++) if (x%prime[i]==0) {
        LL cnt = 0;
        while (x%prime[i]==0) cnt++, x/=prime[i];
        sum *= cnt+1;
    }
    if (x>1) sum *= 2LL;
    return sum;
}

LL a,b;
int main(){
    get_prime(maxn);
    int T;
    scanf("%d",&T);

    for (int kase = 1; kase <= T; kase++) {
        scanf("%lld%lld",&a,&b);
        LL ans = 0;
        if (b < sqrt(a)) {
            ans = func(a)/2;
            b--;
            while (b>0) {
                if (a%b==0) ans--;
                b--;
            }
        }
        printf("Case %d: %lld\n",kase,ans);
    }
    return 0;
}
