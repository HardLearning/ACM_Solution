#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
struct Edge{
    int u,v;
    double w;
    bool operator <(const Edge &rhs) const {
       return w<rhs.w;
    }
}e[maxn*maxn/2];
int n,tot;
int x[maxn],y[maxn];
int fa[maxn];
double ans;

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
    ans = 0;
    memset(fa,-1,sizeof(fa));

    int u,v;
    for (int i=0; i<tot; i++) {
        u = Find(e[i].u);
        v = Find(e[i].v);
        if (u!=v) {
            fa[u] = v;
            ans += e[i].w;
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d %d",&x[i],&y[i]);

        tot = 0;
        for (int i=2; i<=n; i++) {
            for (int j=1; j<i; j++) {
                double dis = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                if (dis<10.0 || dis>1000.0) continue;
                e[tot].u = i;
                e[tot].v = j;
                e[tot].w = dis;
                tot++;
            }
        }
        sort(e,e+tot);
        kruskal();

        ans *= 100;
        int cnt = 0;
        for (int i=1; i<=n; i++) if (fa[i]==-1) cnt++;
        if (cnt!=1) printf("oh!\n"); else printf("%.1f\n",ans);
    }
    return 0;
}
