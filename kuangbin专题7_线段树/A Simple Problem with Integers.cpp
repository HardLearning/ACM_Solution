#include <cstdio>
using namespace std;

typedef long long LL;
const int maxn = 100000+10;
LL a[maxn];
int n,q;
struct node{
   int left,right;
   LL sum,lazy;
};

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1;

   inline void push_up(int u) {
      tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum;
   }

   void build(int u, int l, int r){
       tr[u].left = l;
       tr[u].right =r;
       tr[u].lazy = 0;
       if (l == r) {
           tr[u].sum = a[l];
           return;
       }
       int mid = Mid;
       build(lch(u),l,mid);
       build(rch(u),mid+1,r);
       push_up(u);
   }

   void update(int u, int a, int b, LL val){
       if (tr[u].left == a && tr[u].right == b) {
           tr[u].lazy += val;
           return;
       }
       tr[u].sum += (LL)(b-a+1)*val;
       int mid = Mid;
       if (b<=mid) update(lch(u),a,b,val);
       else if (a>mid) update(rch(u),a,b,val);
       else {
           update(lch(u),a,mid,val);
           update(rch(u),mid+1,b,val);
       }
   }

   inline void push_down(int u){
        if (tr[u].lazy == 0) return;
        tr[lch(u)].lazy += tr[u].lazy;
        tr[rch(u)].lazy += tr[u].lazy;
        tr[u].sum += tr[u].lazy*(tr[u].right-tr[u].left+1);
        tr[u].lazy = 0;
   }

   LL query(int u, int a, int b){
       if (a==tr[u].left && tr[u].right==b) return tr[u].lazy*(b-a+1) + tr[u].sum;
       push_down(u);
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

int main(){
    while (scanf("%d %d",&n,&q)==2){
        for (int i=1; i<=n; i++) scanf("%I64d",&a[i]);
        T.build(1,1,n);

        char str[5];
        int a,b;
        LL val;
        while (q--){
            scanf("%s",str);
            if (str[0] == 'Q') {
                scanf("%d %d",&a,&b);
                printf("%I64d\n",T.query(1,a,b));
            }
            else {
                scanf("%d %d %I64d",&a,&b,&val);
                T.update(1,a,b,val);
            }
        }
    }
    return 0;
}
