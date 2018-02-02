#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 500+5;
struct Edge{
    int u,v;
    double w;
    bool operator <(const Edge &rhs) const {
        return w<rhs.w;
    }
}e[maxn*maxn];
int s,n,tot;
int fa[maxn];
int x[maxn],y[maxn];

int Find(int x){
    if (fa[x] == -1) return x;
    return fa[x] = Find(fa[x]);
}

void kruskal(){
    memset(fa,-1,sizeof(fa));
    s = n-s;

    int cnt = 0;
    double ans;
    int u,v;
    for (int i=0; i<tot; i++) {
        u = Find(e[i].u);
        v = Find(e[i].v);
        if (u!=v) {
            cnt++;
            fa[u] = v;
        }
        if (cnt == s) {
            ans = e[i].w;
            break;
        }
    }
    printf("%.2f\n",ans);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d %d",&s,&n);
        for (int i=1; i<=n; i++) scanf("%d %d",&x[i],&y[i]);

        tot = 0;
        for (int i=2; i<=n; i++) {
            for (int j=1; j<i; j++) {
                double dis = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
                e[tot].u = i;
                e[tot].v = j;
                e[tot].w = dis;
                tot++;
            }
        }
        sort(e,e+tot);
        kruskal();
    }
    return 0;
}
