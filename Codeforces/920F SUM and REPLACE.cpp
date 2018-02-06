#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int maxn  =1e6+5;
int D[maxn],c[maxn];
int n,m;
struct node{
    int l,r;
    LL sum;
    int mx;
};

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].l+tr[u].r)>>1

   inline int Max(int x, int y) {return x>y?x:y;}
   void push_up(int u){
       tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum;
       tr[u].mx = Max(tr[lch(u)].mx,tr[rch(u)].mx);
   }

   void build(int u, int a, int b){
       tr[u].l = a; tr[u].r = b;
       if (a == b) {
           tr[u].sum = tr[u].mx = c[a];
           return ;
       }
       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid+1,b);
       push_up(u);
   }

   void update(int u, int a, int b){
      if (tr[u].mx <= 2) return;
      if (tr[u].l == tr[u].r) {
         tr[u].sum = tr[u].mx = D[tr[u].mx];
         return ;
      }

      int mid = Mid;
      if (b<=mid) update(lch(u),a,b);
      else if (a>mid) update(rch(u),a,b);
      else {
         update(lch(u),a,mid);
         update(rch(u),mid+1,b);
      }
      push_up(u);
   }

   LL query(int u, int a, int b){
       if (tr[u].l == a && tr[u].r == b) return tr[u].sum;
       LL ans = 0;
       int mid = Mid;
       if (b<=mid) ans += query(lch(u),a,b);
       else if (a>mid) ans += query(rch(u),a,b);
       else {
          ans += query(lch(u),a,mid);
          ans += query(rch(u),mid+1,b);
          return ans;
       }
   }

}T;

inline void init(){
   memset(D,0,sizeof(D));
   for (int i=1; i<maxn; i++) {
       for (int j=i; j<maxn; j+=i) D[j]++;
   }
}

int main(){
    init();
    while (scanf("%d %d",&n,&m)==2){
        for (int i=1; i<=n; i++) scanf("%d",&c[i]);
        T.build(1,1,n);

        int t,l,r;
        while (m--){
            scanf("%d %d %d",&t,&l,&r);
            if (t==1)  T.update(1,l,r);
            else printf("%I64d\n",T.query(1,l,r));
        }
    }
    return 0;
}
