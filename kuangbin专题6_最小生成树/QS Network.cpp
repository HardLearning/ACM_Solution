#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1000+10;
int n,tot;
int b[maxn],a[maxn][maxn];
struct Edge{
   int u,v,w;
   bool operator <(const Edge &rhs) const {
       return w < rhs.w;
   }
}e[maxn*maxn];
int fa[maxn];

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
   memset(fa,-1,sizeof(fa));

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
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d",&b[i]);
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) scanf("%d",&a[i][j]);

        tot = 0;
        for (int i=2; i<=n; i++) {
            for (int j=1; j<i; j++) {
                e[tot].u = i;
                e[tot].v = j;
                e[tot].w = a[i][j] + b[i] + b[j];
                tot++;
            }
        }
        sort(e,e+tot);

        kruskal();
    }
    return 0;
}
