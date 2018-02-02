#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
struct Edge{
   int u,v,w;
   bool operator <(const Edge &rhs) const {
       return w<rhs.w;
   }
}e[maxn*maxn];
int n,tot;
int a[maxn][maxn];
int fa[maxn];

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
   int u,v;
   int ans = 0;
   for (int i=0; i<tot; i++) {
       u = Find(e[i].u);
       v = Find(e[i].v);
       if (u!=v) {
          ans += e[i].w;
          fa[u] = v;
       }
   }
   printf("%d\n",ans);
}

int main(){
    while (scanf("%d",&n)==1){
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) scanf("%d",&a[i][j]);

        tot = 0;
        for (int i=2; i<=n; i++)
          for (int j=1; j<i; j++) {
             e[tot].u = i;
             e[tot].v = j;
             e[tot].w = a[i][j];
             tot++;
        }
        sort(e,e+tot);
        memset(fa,-1,sizeof(fa));

        kruskal();
    }
    return 0;
}
