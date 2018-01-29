#include <cstdio>
#include <cstring>
using namespace std;

const int maxm = 2000+10;
const int maxn = 500+5;
int fa[maxn],val[maxn];
int n,m;
struct node{
   int x,y;
   int re;
}a[maxm];

void init(){
    char c;
    for (int i=1; i<=m; i++) {
        scanf("%d%c%d",&a[i].x,&c,&a[i].y);
        if (c=='<') a[i].re = 1;
        else if (c=='=') a[i].re = 0;
        else a[i].re = 2;
    }
}

int Find(int x) {
   if (fa[x] == -1) return x;
   int f = Find(fa[x]);
   val[x] = (val[x] + val[fa[x]])%3;
   return fa[x] = f;
}

inline int Max(int x, int y) { return x>y?x:y; }

int main(){
    while (scanf("%d %d",&n,&m)==2) {
          init();
          int tot = 0; // the number of possible judge
          int mx = 0; // the largest position to determine the judge
          int ans = 0;
          for (int i=0; i<n; i++) {
             memset(fa,-1,sizeof(fa));
             memset(val,0,sizeof(val));

             int tmp = -1;
             for (int j=1; j<=m; j++) {
                 if (a[j].x == i || a[j].y == i) continue;
                 int rx = Find(a[j].x), x = a[j].x;
                 int ry = Find(a[j].y), y = a[j].y;
                 int r = a[j].re;
                 if (rx == ry) {
                     if ((val[x]+r)%3!=val[y]) { tmp = j; break; }
                 }
                 else {
                     fa[ry] = rx;
                     val[ry] = (val[x] - val[y] + r + 3)%3;
                 }
             }
             if (tmp==-1) {
                tot++;
                ans = i;
             }
             else mx = Max(mx,tmp);
             if (tot>1) break;
          }
          if (tot>1) printf("Can not determine\n");
          else if (tot == 0) printf("Impossible\n");
          else printf("Player %d can be determined to be the judge after %d lines\n",ans,mx);
    }
    return 0;
}
