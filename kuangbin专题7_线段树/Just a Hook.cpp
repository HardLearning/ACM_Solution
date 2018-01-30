#include <cstdio>
using namespace std;

const int maxn = 100000+5;
struct node{
   int left,right;
   int lazy,sum;
};

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   inline void push_up(int u){ tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum; }

   void build( int u, int a, int b){
      tr[u].left = a; tr[u].right = b; tr[u].lazy = 0;
      if (a == b) {
         tr[u].sum = 1;
         return;
      }
      int mid = Mid;
      build(lch(u),a,mid);
      build(rch(u),mid+1,b);
      push_up(u);
   }

   void push_down(int u){
       if (tr[u].lazy == 0) return;
       tr[lch(u)].lazy = tr[rch(u)].lazy = tr[u].lazy;
       int mid  = Mid;
       tr[lch(u)].sum = (mid-tr[u].left+1)*tr[u].lazy;
       tr[rch(u)].sum = (tr[u].right-mid)*tr[u].lazy;
       tr[u].lazy = 0;
   }

   void update(int u, int a, int b, int val) {
       if (tr[u].left == a && tr[u].right == b) {
           tr[u].lazy = val;
           tr[u].sum = (b-a+1)*val;
           return;
       }

       push_down(u);

       int mid = Mid;
       if (b<=mid) update(lch(u),a,b,val);
       else if (a>mid) update(rch(u),a,b,val);
       else {
           update(lch(u),a,mid,val);
           update(rch(u),mid+1,b,val);
       }
       push_up(u);
   }


}T;
int n,q;
int x,y,z;

int main(){
    int t;
    scanf("%d",&t);

    int kase = 0;
    while (t--){
        scanf("%d %d",&n,&q);
        T.build(1,1,n);
        while (q--){
            scanf("%d %d %d",&x,&y,&z);
            T.update(1,x,y,z);
        }
        printf("Case %d: The total value of the hook is %d.\n",++kase,T.tr[1].sum);
    }
    return 0;
}
