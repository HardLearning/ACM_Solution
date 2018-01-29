#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000+10;
int fa[maxn],r[maxn];
int n,m;

void init(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) fa[i] = i,r[i] = 0;
}

int Find(int x) {
   if (fa[x] == x) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y) {
   x = Find(x); y = Find(y);
   if (x == y) return;
   if (r[x]>r[y]) fa[y] = x;
   else {
       fa[x] = y;
       if (r[x] == r[y]) r[y]++;
   }
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        init();
        int x,y;
        for (int i=1; i<=m; i++) {
             scanf("%d %d",&x,&y);
             Merge(x,y);
        }
        int table = 0;
        for (int i=1; i<=n; i++) if (fa[i]==i) table++;
        printf("%d\n",table);
    }
    return 0;
}
