#include <cstdio>
using namespace std;

const int maxn = 200000+10;
int fa[maxn],sum[maxn];
int n,m;

void init(){
    for (int i=0; i<=n; i++) fa[i] = -1,sum[i] = 0;
}

int Find(int x) {
   if (fa[x] == -1) return x;
   int f = Find(fa[x]);
   sum[x] += sum[fa[x]];
   return fa[x] = f;
}

int main(){
    while (scanf("%d %d",&n,&m)==2) {
        init();
        int ans = 0;
        int a,b,val;
        for (int i=1; i<=m; i++) {
            scanf("%d %d %d",&a,&b,&val);
            a--;
            int ra = Find(a), rb = Find(b);
            if (ra == rb) {
                if (sum[b]-sum[a]!=val) ans++;
            }
            else {
                fa[rb] = ra;
                sum[rb] = sum[a] - sum[b] + val;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
