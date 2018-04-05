#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1e7+10;
int n,tot;
vector<int>prime;
bool vis[maxn];

void get_prime(int n) {
   prime.clear();
   memset(vis,1,sizeof(vis));
   tot = 0;
   for (int i=2; i<n; i++) if (vis[i]) {
       prime.push_back(i);
       tot++;
       for (int j=i+i; j<n; j+=i) vis[j] = 0;
   }
}

int main(){
    get_prime(maxn);
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase<=T; kase++) {
        scanf("%d",&n);
        int ans = 0;
        for (int i=0; prime[i]*2<=n; i++) {
             if (vis[n-prime[i]]) ans++;
        }
        printf("Case %d: %d\n",kase,ans);
    }
    return 0;
}
