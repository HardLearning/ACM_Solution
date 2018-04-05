#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int maxn = 1e5+5;
bool vis[maxn];
LL prime[maxn],tot;

void get_prime(int n) {
    tot = 0;
    memset(vis,1,sizeof(vis));
    for (int i=2; i<n; i++) if (vis[i]) {
        prime[tot++] = (LL)i;
        for (int j=i+i; j<n; j+=i) vis[j] = 0;
    }
}

int cnt;
int a[maxn];
bool flag;

int gcd(int x, int y) { return y==0?x:gcd(y,x%y); }

int main(){
    get_prime(maxn);
    int T;
    scanf("%d",&T);

    LL n;
    for (int kase = 1; kase<=T; kase++) {
        scanf("%lld",&n);
        if (n<0) {
            n = -n;
            flag = 1;
        }
        else flag = 0;

        cnt = 0;
        for (int i=0; prime[i]*prime[i]<=n && i<tot; i++) if (n%prime[i]==0) {
            a[cnt] = 0;
            while (n%prime[i]==0) a[cnt]++, n/=prime[i];
            cnt++;
        }
        if (n>1) a[cnt++] = 1;

        int ans = a[0];
        for (int i=2; i<cnt; i++) ans = gcd(ans,a[i]);

        if (flag == 1) {
            while (ans%2==0) ans/=2;
        }
        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}
