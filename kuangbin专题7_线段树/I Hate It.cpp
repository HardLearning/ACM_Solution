#include <cstdio>
using namespace std;

const int maxn = 2e5+5;
struct node{
   int left,right;
   int mx;
};
int score[maxn];
int n,m;

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   inline int Max(int x, int y) {return x>y?x:y; }
   void push_up(int u){
      tr[u].mx = Max(tr[lch(u)].mx,tr[rch(u)].mx);
   }

   void build(int u, int l, int r){
       tr[u].left = l; tr[u].right = r;
       if (l == r) {
           tr[u].mx = score[l];
           return;
       }

       int mid = Mid;
       build(lch(u),l,mid);
       build(rch(u),mid+1,r);
       push_up(u);
   }

   void update(int u, int pos, int val){
       if (tr[u].left == tr[u].right && tr[u].left == pos) {
           tr[u].mx = val;
           return;
       }

       int mid = Mid;
       if (pos<=mid) update(lch(u),pos,val);
       else update(rch(u),pos,val);
       push_up(u);
   }

   int query(int u, int l, int r) {
       if (l<=tr[u].left && tr[u].right<=r) return tr[u].mx;
       int ans = -1;
       int mid = Mid;
       if (r<=mid) ans = Max(ans,query(lch(u),l,r));
       else if (l>mid) ans = Max(ans,query(rch(u),l,r));
       else {
           ans = Max(ans,query(lch(u),l,r));
           ans = Max(ans,query(rch(u),l,r));
       }
       return ans;
   }
}T;

inline void Swap(int &a, int &b) { int c=a; a=b; b=c;}

int main(){
    while (scanf("%d %d",&n,&m)==2){
        for (int i=1; i<=n; i++) scanf("%d",&score[i]);
        T.build(1,1,n);

        int a,b;
        char str[5];
        for (int i=1; i<=m; i++) {
            scanf("%s %d %d",str,&a,&b);
            if (str[0] == 'Q') {
                if (a>b) Swap(a,b);
                printf("%d\n", T.query(1,a,b));
            }
            else T.update(1,a,b);
        }
    }
    return 0;
}
