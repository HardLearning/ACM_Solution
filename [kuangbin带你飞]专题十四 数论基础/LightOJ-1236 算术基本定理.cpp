#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1e7+10;
typedef long long LL;
LL n;
LL prime[maxn/10];
int tot;
bool vis[maxn];

void get_prime(int n) {
    memset(vis,1,sizeof(vis));
    tot = 0;
    for (int i=2; i<n; i++) if (vis[i]) {
        prime[tot++] = (LL)i;
        for (int j=i+i; j<n; j+=i) vis[j] = 0;
    }
}

int main(){
    get_prime(maxn);
    int T;
    scanf("%d",&T);

    for (int kase = 1; kase<=T; kase++) {
        scanf("%lld",&n);
        LL sum = 1LL;

        for (int i=0; prime[i]*prime[i]<=n && i<tot; i++) if(n%prime[i]==0){
              LL t = 0;
              while (n%prime[i]==0) t++,n/=prime[i];
              sum = sum*(2*t+1LL);
        }
        if (n>1) sum *= 3LL;
        sum = sum/2 + 1LL;
        printf("Case %d: %lld\n",kase,sum);
    }
    return 0;
}
