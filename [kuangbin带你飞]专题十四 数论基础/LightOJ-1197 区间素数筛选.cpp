//LightOJ-1197 区间素数筛选
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

typedef long long LL;
const int maxn = 1e5+10;
bool isprime[maxn];
vector<int>prime;

void init(){
    prime.clear();
    for (int i=1; i<=55000; i++) if (i&1) isprime[i] = 1; else isprime[i] = 0;
    isprime[2] = 1;
    for (int i=2; i<=55000; i++) if (isprime[i]) {
        prime.push_back(i);
        for (int j=i+i; j<=55000; j+=i) isprime[j] = 0;
    }
}

int main(){
    init();
    int a,b;
    int T,kase = 0;
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&a,&b);
        memset(isprime,1,sizeof(isprime));
        for (int i=0; i<prime.size(); i++) {
            if (1LL*prime[i]*prime[i]>b) break;
            LL j;
            if (a/prime[i]<2) j = prime[i]*2;
            else j = ((1LL*a-1)/prime[i]+1)*prime[i];
            while (j<=b) {
                isprime[j-a] = 0;
                j += prime[i];
            }
        }

        int num = b-a;
        int ans = 0;
        for (int i=0; i<=num; i++) if (isprime[i]) ans++;
        if (a == 1) ans--;
        printf("Case %d: %d\n",++kase,ans);
    }
    return 0;
}
