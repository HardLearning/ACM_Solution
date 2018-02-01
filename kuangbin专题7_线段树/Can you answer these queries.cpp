#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 100000+5;
typedef long long LL;
LL ship[maxn];
struct node{
   int l,r;
   LL sum;
};
struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].l+tr[u].r)>>1

   inline void push_up(int u){
       tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum;
   }

   void build(int u, int a, int b){
       tr[u].l = a; tr[u].r = b;
       if (a == b) {
          tr[u].sum = ship[a];
          return;
       }
       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid+1,b);
       push_up(u);
   }

   void update(int u, int a, int b){
         if (tr[u].l == tr[u].r) {
            tr[u].sum = (LL)sqrt(tr[u].sum);
            return;
         }
         if (tr[u].sum == tr[u].r-tr[u].l+1) return;

         int mid = Mid;
         if (b<=mid) update(lch(u),a,b);
         else if (a>mid) update(rch(u),a,b);
         else {
            update(lch(u),a,mid);
            update(rch(u),mid+1,b);
         }
         push_up(u);
   }

   LL query(int u,int a, int b){
      if (a <= tr[u].l && tr[u].r <= b) return tr[u].sum;
      int mid = Mid;
      LL ans = 0;

      if (b<=mid) ans = query(lch(u),a,b);
      else if (a>mid) ans = query(rch(u),a,b);
      else {
        ans += query(lch(u),a,mid);
        ans += query(rch(u),mid+1,b);
      }
      return ans;
   }
}T;
int n,m;

inline void Swap(int &a, int &b) {int c=a; a=b; b=c; }

int main(){
     int kase = 0;
     int t,x,y;
     while (scanf("%d",&n)!=EOF){
          for (int i=1; i<=n; i++) scanf("%I64d",&ship[i]);
          T.build(1,1,n);
          printf("Case #%d:\n",++kase);

          scanf("%d",&m);
          while (m--){
             scanf("%d %d %d",&t,&x,&y);
             if (x>y) Swap(x,y);
             if (t == 0) T.update(1,x,y);
             else printf("%I64d\n",T.query(1,x,y));
          }
          printf("\n");
     }
     return 0;
}
