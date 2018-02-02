#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
int n,q;
int a[maxn][maxn];
int fa[maxn];
struct Edge{
   int u,v,w;
   bool operator <(const Edge &rhs) const {
       return w<rhs.w;
   }
}e[maxn*maxn];
int tot;

void init(){
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++) scanf("%d",&a[i][j]);

    for (int i=2; i<=n; i++) {
        for (int j=1; j<i; j++) {
            e[tot].u = i;
            e[tot].v = j;
            e[tot].w = a[i][j];
            tot++;
        }
    }

    memset(fa,-1,sizeof(fa));
    sort(e,e+tot);
}

int Find(int x){
    if (fa[x] == -1) return x;
    return fa[x] = Find(fa[x]);
}

void kruskal(){
    int ans = 0;
    int x,y;
    for (int i=0; i<tot; i++) {
        x = Find(e[i].u);
        y = Find(e[i].v);
        if (x!=y) {
            ans += e[i].w;
            fa[x] = y;
        }
    }
    printf("%d\n",ans);
}

int main(){
    while (scanf("%d",&n)==1){
        init();
        scanf("%d",&q);

        int x,y;
        while (q--) {
            scanf("%d %d",&x,&y);
            x = Find(x);
            y = Find(y);
            if (x != y) fa[x] = y;
        }

        kruskal();
    }
    return 0;
}
