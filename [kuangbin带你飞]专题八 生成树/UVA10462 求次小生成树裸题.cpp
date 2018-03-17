#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 100+10;
const int maxe = 210;
struct Edge{
   int x,y,w;
   bool operator <(const Edge& rhs) const {
      return w<rhs.w;
   }
}e[maxe];

int n,m;
int fa[maxn];
bool used[maxe];

int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

int kruskal(){
    for (int i=1; i<=n; i++) fa[i] = i;
    for (int i=1; i<=m; i++) used[i] = 0;
    sort(e+1,e+m+1);
    int ans = 0, num = 0;
    int tx,ty;
    for (int i=1; i<=m; i++) {
        tx = Find(e[i].x);
        ty = Find(e[i].y);
        if (tx!=ty) {
            fa[tx] = ty;
            ans += e[i].w;
            num++;
            used[i] = 1;
        }
        if (num>=n-1) break;
    }
    if (num>=n-1) return ans;
    return -1;
}

int kruskal2(int idx){
     for (int i=1; i<=n; i++) fa[i] = i;
     int ans = 0, num = 0;
     int tx,ty;
     for (int i=1; i<=m; i++) if (i!=idx) {
        tx = Find(e[i].x);
        ty = Find(e[i].y);
        if (tx!=ty) {
            fa[tx] = ty;
            ans += e[i].w;
            num++;
        }
        if (num>=n-1) break;
     }
     if (num>=n-1) return ans;
     return INF;
}

inline int Min(int x, int y) {return x<y?x:y; }

int main(){
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase<=T; kase++) {
         scanf("%d%d",&n,&m);
         for (int i=1; i<=m; i++) scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
         if (n==1) {
             printf("Case #%d : No second way\n",kase);
             continue;
         }

         if (n>1 && m==0) {
             printf("Case #%d : No way\n",kase);
             continue;
         }

         int MST = kruskal();
         if (MST==-1) {
            printf("Case #%d : No way\n",kase);
            continue;
         }

         int second = INF;
         for (int i=1; i<=m; i++) if (used[i]) second = Min(second,kruskal2(i));
         if (second==INF) printf("Case #%d : No second way\n",kase);
         else printf("Case #%d : %d\n",kase,second);
    }
    return 0;
}
