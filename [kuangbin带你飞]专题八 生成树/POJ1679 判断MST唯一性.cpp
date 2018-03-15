#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100+10;
const int maxm = 20000+10;
int n,m,idx;
int fa[maxn];
int MST;

struct Edge{
   int x,y,val;
   bool operator <(const Edge& rhs) const { return val<rhs.val; }
}e[maxm];
bool vis[maxm];
bool mark[maxm];

int Find(int x) {
  if (fa[x]==x) return x;
  return fa[x] = Find(fa[x]);
}

void first_kruskal(){
    int num = 0;
    int tx,ty;

    MST = 0;
    for (int i=0; i<m; i++) {
        tx = Find(e[i].x); ty = Find(e[i].y);
        if (tx!=ty) {
            num++;
            MST += e[i].val;
            fa[tx] = ty;
            mark[i] = 1;
        }
        if (num>=n-1) break;
    }
}

int kruskal(){
   int num = 0;
   int tree = 0;

   int tx,ty;
   for (int i=0; i<m; i++) {
      if (i==idx) continue;
      tx = Find(e[i].x); ty = Find(e[i].y);
      if (tx!=ty) {
         num++;
         tree += e[i].val;
         fa[tx] = ty;
      }
      if (num>=n-1) break;
   }
   if (num<n-1) return -1;
   return tree;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d%d",&n,&m);
       for (int i=0; i<m; i++) {
          mark[i] = 0;
          scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].val);
       }
       sort(e,e+m);
       for (int i=1; i<=n; i++) fa[i] = i;
       first_kruskal();

       bool flag = 0;
       int tmp;
       for (int i=0; i<m; i++) if (mark[i]==1) {
            for (int k=1; k<=n; k++) fa[k] = k;
            idx = i;
            tmp = kruskal();
            if (tmp == MST) {
                flag = 1;
                break;
            }
            if (flag) break;
       }
       if (flag) printf("Not Unique!\n"); else printf("%d\n",MST);
    }
    return 0;
}
