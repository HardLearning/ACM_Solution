#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn= 100+5;
struct Edge{
   int u,v,w;
   bool operator <(const Edge &rhs) const {
      return w<rhs.w;
   }
}e[maxn*maxn/2];
int n,tot;
int fa[maxn];
int ans;

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
    int u,v;
    ans = 0;
    for (int i=1; i<=tot; i++) {
         u = Find(e[i].u);
         v = Find(e[i].v);
         if (u!=v){
            ans += e[i].w;
            fa[u] = v;
         }
    }
}

int main(){
    while(scanf("%d",&n)==1 && n){
        tot = n*(n-1)/2;
        memset(fa,-1,sizeof(fa));
        for (int i=1; i<=tot; i++) scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
        sort(e+1,e+tot+1);
        kruskal();

        int cnt = 0;
        for (int i=1; i<=n; i++) if (fa[i]==-1) cnt++;
        if (cnt!=1) ans = 0;
        printf("%d\n",ans);
    }
    return 0;
}
