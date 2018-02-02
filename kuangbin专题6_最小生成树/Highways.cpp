#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 750+5;
struct Edge{
   int u,v;
   int w;
}e[maxn*maxn];
int n,m,tot;
int x[maxn],y[maxn];
int fa[maxn];
bool cmp(Edge a,Edge b) { return a.w<b.w; }

inline void init(){

}

int Find(int x) {
   if (fa[x] == x) return x;
   return fa[x] = Find(fa[x]);
}

inline void kruskal(){
    int u,v;
    for (int i=0; i<tot; i++) {
         u = Find(e[i].u);
         v = Find(e[i].v);
         if (u!=v) {
            fa[u] = v;
            printf("%d %d\n",e[i].u,e[i].v);
         }
    }
}

int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) scanf("%d %d",&x[i],&y[i]);
    for (int i=0; i<=n; i++) fa[i] = i;
    tot = 0;
    scanf("%d",&m);
    int u,v;
    while (m--){
        scanf("%d %d",&u,&v);
        u = Find(u);
        v = Find(v);
        if (u!=v)  fa[u] = v;
    }

    for (int i=2; i<=n; i++) {
        for (int j=1; j<i; j++) {
            if (Find(i)!=Find(j)) {
                e[tot].u = i;
                e[tot].v = j;
                e[tot].w = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                tot++;
            }
        }
    }
    sort(e,e+tot,cmp);
    kruskal();
    return 0;
}
