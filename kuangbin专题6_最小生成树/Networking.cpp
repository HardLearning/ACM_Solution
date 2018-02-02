#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 50+5;
const int maxe = 100000+5;
struct Edge{
    int u,v,w;
    bool operator <(const Edge &rhs) const {
       return w<rhs.w;
    }
}e[maxe];
int n,m,tot;
int fa[maxn];

inline void init(){
    scanf("%d",&m);
    for (int i=1; i<=m; i++) scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
    sort(e+1,e+m+1);
}

int Find(int x){
   if (fa[x]==-1) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
   x = Find(x); y = Find(y);
   if (x!=y) fa[x] = y;
}

int main(){
    while (scanf("%d",&n)==1 && n) {
        init();
        memset(fa,-1,sizeof(fa));

        int u,v;
        int ans = 0;
        for (int i=1; i<=m; i++) {
            u = e[i].u;
            v = e[i].v;
            if (Find(u) != Find(v)) {
                Merge(u,v);
                ans += e[i].w;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
