#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int fa[maxn*3],r[maxn*3];
int n,k,ans;
int d,x,y;

int Find(int x) {
   if (fa[x] == x) return x;
   return fa[x] = Find(fa[x]);
}

bool same(int x, int y) {
   return Find(x) == Find(y);
}

void Merge(int x, int y) {
   x = Find(x); y = Find(y);
   if (r[x]>r[y]) fa[y] = x;
   else {
       fa[x] = y;
       if (r[x]==r[y]) r[y]++;
   }
}

int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<=n*3; i++) fa[i] = i,r[i] = 0;
    ans = 0;
    while (k--) {
         scanf("%d %d %d",&d,&x,&y);
         if (x>n || y>n || (d == 2 && x == y)) { ans++; continue; }
         if (d == 1) {
            if (same(x,y+n) || same(x,y+2*n)) ans++;
            else {
                Merge(x,y);
                Merge(x+n,y+n);
                Merge(x+2*n,y+2*n);
            }
         }
         else {
            if (same(x,y) || same(x,y+2*n)) ans++;
            else {
                Merge(x,y+n);
                Merge(x+n,y+2*n);
                Merge(x+2*n,y);
            }
         }
    }
    printf("%d\n",ans);
    return 0;
}
