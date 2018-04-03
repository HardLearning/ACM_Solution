#include <cstdio>
using namespace std;

const int maxn = 1e6+10;
int n,x;
bool prime[maxn];

void init(int n) {
   for (int i=1; i<n; i++) prime[i] = 1;
   for (int i=2; i<n; i++) if (prime[i]) {
       for (int j=i+i; j<n; j+=i) prime[j] = 0;
   }
}

typedef long long LL;

int main(){
    int T;
    scanf("%d",&T);
    init(maxn);
    for (int kase = 1; kase <= T; kase++) {
       scanf("%d",&n);
       LL ans = 0;
       for (int i=1; i<=n; i++) {
            scanf("%d",&x);
            while (prime[x+1]==0) x++;
            ans += x+1;
       }
       printf("Case %d: %lld Xukha\n",kase,ans);
    }
    return 0;
}
