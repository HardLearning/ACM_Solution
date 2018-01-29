#include <cstdio>
using namespace std;

const int maxn = 1000+5;
int fa[maxn],r[maxn];
bool isgood[maxn];
struct node{
   int x,y;
}a[maxn];
int n,d;

void init(){
   scanf("%d %d",&n,&d);
   d = d*d;
   for (int i=1; i<=n; i++) {
      scanf("%d %d",&a[i].x,&a[i].y);
      fa[i] = i;
      r[i] = 0;
      isgood[i] = 0;
   }
}

int Find(int x){
   if (fa[x] == x) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
   x = Find(x); y = Find(y);
   if (fa[x] == fa[y]) return ;
   if (r[x]>r[y]) fa[y] = x;
   else {
       fa[x] = y;
       if (r[x] == r[y]) r[y]++;
   }
}

inline bool judge(node A, node B) {
   int dis = (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
   return dis<=d;
}

int main(){
    init();

    char s[10];
    int p,q;
    while (~scanf("%s",s)) {
        if (s[0]=='O') {
            scanf("%d",&p);
            isgood[p] = 1;
            for (int i=1; i<=n; i++) if (isgood[i] && judge(a[i],a[p])) Merge(i,p);
        }
        else {
            scanf("%d %d",&p,&q);
            if (isgood[p]==0 || isgood[q]==0) {
                printf("FAIL\n");
                continue;
            }
            int fp = Find(p),fq = Find(q);
            if (fp == fq) printf("SUCCESS\n"); else printf("FAIL\n");
        }
    }
    return 0;
}
