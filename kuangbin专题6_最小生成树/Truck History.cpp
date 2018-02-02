#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2000+5;
struct Edge{
   int u,v,w;
   bool operator <(const Edge &rhs) const {
      return w < rhs.w;
   }
}e[maxn*maxn];
int n,tot;
int fa[maxn];
char s[maxn][10];

inline int differ(int a, int b){
   int sum = 0;
   for (int i=0; i<7; i++) if (s[a][i]!=s[b][i]) sum++;
   return sum;
}

void init(){
    tot = 0;
    for (int i=1; i<=n; i++) scanf("%s",s[i]);
    for (int i=2; i<=n; i++) {
        for (int j=1; j<i; j++) {
            e[tot].u = i;
            e[tot].v = j;
            e[tot].w = differ(i,j);
            tot++;
        }
    }
    sort(e,e+tot);
}

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
    memset(fa,-1,sizeof(fa));
    int x,y;
    int ans = 0;

    for (int i=0; i<tot; i++) {
        x = Find(e[i].u);
        y = Find(e[i].v);
        if (x!=y){
            ans += e[i].w;
            fa[x] = y;
        }
    }
    printf("The highest possible quality is 1/%d.\n",ans);
}

int main(){
    while (scanf("%d",&n)==1 && n){
        init();
        kruskal();
    }
    return 0;
}
